#include <QtWidgets/QPushButton>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSizePolicy>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QLabel>
#include <QGraphicsSimpleTextItem>
#include <iostream>
#include <fstream>
#include <limits>
#include <cmath>
#include <cstdio>
#include "fenetre.hpp"
#include "rand.hpp"
#include "configGui.hpp"

using namespace std;

Fenetre::Fenetre(QWidget *parent) : QWidget(parent)
{
	sol = NULL;

	//allocation onglets
	createPageConfig();
	pageCoord = new InputCoord;
	pageName = new InputName;

	tab = new QTabWidget(this);
	tab->addTab(pageConfig, "Config solver");
	tab->addTab(pageCoord, "Coordonnées");
	tab->addTab(pageName, "Noms");

	tab->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding));

	//graphe
	gScene = new QGraphicsScene;

	gView = new QGraphicsView(gScene);

	QPushButton *nextStep = new QPushButton(">>");
	nextStep->setToolTip("itération suivante");
	QObject::connect(nextStep, SIGNAL(clicked()), this, SLOT(nextIt()));
	QPushButton *reachEnd = new QPushButton(">|");
	reachEnd->setToolTip("aller directement à la dernière itération");
	QObject::connect(reachEnd, SIGNAL(clicked()), this, SLOT(goToEnd()));
	score = new QLabel("score: ");

	//affichage central
	QGridLayout *layoutGV = new QGridLayout;
	layoutGV->addWidget(gView, 0, 0);
	layoutGV->addWidget(score, 1, 0, Qt::AlignHCenter);
	layoutGV->addWidget(nextStep, 2, 0, Qt::AlignRight);
	layoutGV->addWidget(reachEnd, 3, 0, Qt::AlignRight);


	QPushButton *validate = new QPushButton("Lancer solveur");
	QObject::connect(validate, SIGNAL(clicked()), this, SLOT(launchSolver()));

	//partie gauche
	QVBoxLayout *gauche = new QVBoxLayout;
	gauche->addWidget(tab);
	gauche->addWidget(validate);

	//affichage général
	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addLayout(gauche);
	mainLayout->addLayout(layoutGV);

	setLayout(mainLayout);

	QSize sizeTab = tab->size();
	resize(sizeTab.width()*10, sizeTab.height()*15);

	QObject::connect(tab, SIGNAL(currentChanged(int)), this, SLOT(handleTabChanges(int)));
}

void Fenetre::createPageConfig()
{
	//generer un probleme
	QLabel *labelGen = new QLabel("Générer un problème");
	labelGen->setAlignment(Qt::AlignHCenter);
	nbCitiesGen = new QDoubleSpinBox;
	nbCitiesGen->setDecimals(0);
	nbCitiesGen->setMinimum(3);
	nbCitiesGen->setMaximum(numeric_limits<int>::max());
	QPushButton *generationButton = new QPushButton("Générer");
	QObject::connect(generationButton, SIGNAL(clicked()), this, SLOT(generate()));

	//separateur
	QFrame *line = new QFrame;
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);

	//options chargement des données
	QLabel *labelFile = new QLabel("Chargement par fichier");
	labelFile->setAlignment(Qt::AlignHCenter);
	QPushButton *fileInputButton = new QPushButton("Charger");
	QObject::connect(fileInputButton, SIGNAL(clicked()), this, SLOT(fileInput()));

	//separateur
	QFrame *line1 = new QFrame;
	line1->setFrameShape(QFrame::HLine);
	line1->setFrameShadow(QFrame::Sunken);


	QLabel *labelManualInput = new QLabel("Entrée manuelle");
	labelManualInput->setAlignment(Qt::AlignHCenter);
	nbCities = new QDoubleSpinBox;
	nbCities->setDecimals(0);
	nbCities->setMinimum(3);
	nbCities->setMaximum(numeric_limits<int>::max());
	QPushButton *validateInput = new QPushButton("Valider");
	QObject::connect(validateInput, SIGNAL(clicked()), this, SLOT(manualInput()));

	QFormLayout *layoutBoxInput = new QFormLayout;
	layoutBoxInput->addRow(labelGen);
	layoutBoxInput->addRow("Nombre de villes:", nbCitiesGen);
	layoutBoxInput->addRow(generationButton);
	layoutBoxInput->addRow(line1);
	layoutBoxInput->addRow(labelFile);
	layoutBoxInput->addRow(fileInputButton);
	layoutBoxInput->addRow(line);
	layoutBoxInput->addRow(labelManualInput);
	layoutBoxInput->addRow("Nombre de villes:", nbCities);
	layoutBoxInput->addRow(validateInput);

	QGroupBox *boxInput = new QGroupBox("Options entrée des données");
	boxInput->setLayout(layoutBoxInput);
	boxInput->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed));


	//options selection, ajoutés dans l'ordre de
	//l'enum Selection (solver.hpp)
	selectSelection = new QComboBox;
	selectSelection->addItem("Roulette");
	selectSelection->addItem("Rang");
	selectSelection->addItem("Tournoi");
	selectSelection->addItem("Elitisme");

	//options croisement, aoutés dans l'ordre de
	//l'enum Croisement (solver.hpp)
	selectCroisement = new QComboBox;
	selectCroisement->addItem("Slicing crossover");
	selectCroisement->addItem("K-slicing crossover");

	//options remplacement, ajoutés dans l'ordre de
	//l'enum Remplacement (solver.hpp)
	selectRemplacement = new QComboBox;
	selectRemplacement->addItem("Stationnaire");
	selectRemplacement->addItem("Elitiste");

	//selection taille population initiale
	sizePI = new QDoubleSpinBox;
	sizePI->setDecimals(0);
	sizePI->setMinimum(1);
	sizePI->setMaximum(numeric_limits<int>::max());

	QFormLayout *layoutConfig = new QFormLayout;
	layoutConfig->addRow("Taille PI:", sizePI);
	layoutConfig->addRow("Selection:", selectSelection);
	layoutConfig->addRow("Croisement:", selectCroisement);
	layoutConfig->addRow("Remplacement:", selectRemplacement);

	QGroupBox *boxConfig = new QGroupBox("Options solver");
	boxConfig->setLayout(layoutConfig);

	//layout global
	QVBoxLayout *layoutPage = new QVBoxLayout;
	layoutPage->addWidget(boxInput);
	layoutPage->addWidget(boxConfig);

	pageConfig = new QWidget;
	pageConfig->setLayout(layoutPage);
}

void Fenetre::launchSolver()
{
	if(!pageCoord->full())
		QMessageBox::critical(this, "Erreur", "Pas de données entrées");
	else
	{
		pageName->fillEmptyNames();

		if(sol != NULL)
		{
			int choice = QMessageBox::warning(this, "", "Un autre solveur est lancé en ce moment\n"
					"Arreter ce solveur et en lancer un nouveau avec les données présentes dans les onglets ?", QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel);

			if(choice == QMessageBox::Cancel)
				return;

			delete sol;
		}

		//creation du solver
		pageName->getNames(villes);
		pageCoord->getCoord(coord);
		vector<vector<double> > distances;
		getDistances(distances);

		int taillePI = sizePI->value();
		Solver::Selection s = static_cast<Solver::Selection>(selectSelection->currentIndex());
		Solver::Croisement c = static_cast<Solver::Croisement>(selectCroisement->currentIndex());
		Solver::Remplacement r = static_cast<Solver::Remplacement>(selectRemplacement->currentIndex());

		sol = new Solver(distances, taillePI, s, c, r);
		renderScene();
		updateScore(sol->meilleureSol().getScore());
	}
}

void Fenetre::updateScore(double bestScore)
{
	score->setText("Score: "+QString::number(bestScore));
}

void Fenetre::fileInput()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Selectionnez un fichier", "", "*.txt");
	printf("fichier selectionné: '%s'\n", fileName.toStdString().c_str());

	ifstream fichier(fileName.toStdString().c_str());

	if(!fichier)
	{
		QMessageBox::critical(this, "Erreur", "Un problème est survenu durant\n l'ouverture du fichier");
	}

	else
	{
		int nb_villes = 0;
		int noms = 0;

		fichier >> nb_villes;
		fichier >> noms;

		pageName->createForm(nb_villes);
		pageCoord->createForm(nb_villes);

		coord.resize(nb_villes);
		villes.resize(nb_villes);

		if(noms == 0)
		{
			for(int i = 0; i < nb_villes; i++)
			{
				fichier >> coord[i].first;
				fichier >> coord[i].second;
				pageCoord->setCoordVille(i, coord[i].first, coord[i].second);

			}
		}

		else
		{
			for(int i = 0; i < nb_villes; i++)
			{
				fichier >> villes[i];
				fichier >> coord[i].first;
				fichier >> coord[i].second;
				pageCoord->setCoordVille(i, coord[i].first, coord[i].second);
			}
			pageName->setNames(villes);
		}
		tab->setCurrentIndex(1);
	}
}

void Fenetre::manualInput()
{
	int n = nbCities->value();

	pageCoord->createForm(n);
	pageName->createForm(n);

	tab->setCurrentIndex(1);
}

void Fenetre::generate()
{
	int n = nbCitiesGen->value();

	pageCoord->createForm(n);
	pageName->createForm(n);

	for(int i = 0; i < n; i++)
	{
		double x = Rand::randi()%700;
		double y = Rand::randi()%700;

		pageCoord->setCoordVille(i, x, y);
	}
}

void Fenetre::getDistances(vector<vector<double> > &dist)
{
	int n = coord.size();
	dist.resize(n);

	for(int i = 0; i < n; i++)
	{
		dist[i].resize(n);
		double xi = coord[i].first;
		double yi = coord[i].second;

		for(int j = 0; j < n; j++)
		{
			double xj = coord[j].first;
			double yj = coord[j].second;

			//double x = (xj-xi)*(xj-xi);
			//double y = (yj-yi)*(yj-yi);
			dist[i][j] = sqrt((xj-xi)*(xj-xi)+(yj-yi)*(yj-yi));
			//cout << i << " " << j  << " " << dist[i][j] << endl;
		}
	}
}

void Fenetre::handleTabChanges(int index)
{
	//tentative d'acces aux onglets des coordonnées et
	//nom de villes sans avoir selectionné une methode
	//d'entrée
	if((index == 1 || index == 2) && pageCoord->empty())
	{
		tab->setCurrentIndex(0);
		QMessageBox::information(this, "Attention",
				"Pas de methode d'entrée sélectionnée.\n\n"
				"Sélectionnez l'entrée par fichier ou l'entrée manuelle en entrant un nombre de villes dans l'onglet Config solver");
	}
}

void Fenetre::nextIt()
{
	if(sol == NULL)
		return;

	if(sol->fin())
	{
			copyFinalPath();
			QMessageBox::information(this, "Fin du solver", "Le solver a trouve le chemin optimal suivant:\n"+finalPath+"\nDe poid: "+QString::number(finalPathCost));
	}
	else
	{
		sol->iteration();
		//sol->afficher();
		renderScene();
		updateScore(sol->meilleureSol().getScore());
	}
}

void Fenetre::goToEnd()
{
	if(sol == NULL)
		return;

	while(!sol->fin())
		nextIt();
	nextIt();
}

void Fenetre::renderCities(int begin, int end)
{
	int n = coord.size();

	for(int i = 0; i < n; i++)
	{
		gScene->addEllipse(QRectF(coord[i].first-CITY_SIZE/2, coord[i].second-CITY_SIZE/2, CITY_SIZE, CITY_SIZE),
				QPen(), QBrush(Qt::SolidPattern));

		QString name(villes[i].c_str());
		if(i == begin)
			name += "(DEPART)";
		else if(i == end)
			name += "(FIN)";

		QGraphicsSimpleTextItem * text = gScene->addSimpleText(name);
		QRectF rect = text->boundingRect();
		text->setPos(coord[i].first-rect.width()/2, coord[i].second-rect.height());
	}
}

void Fenetre::renderPath(vector<int> &path)
{
	int n = path.size();

	for(int i = 0; i < n-1; i++)
	{
		int  a = path[i];
		int b = path[i+1];

		gScene->addLine(coord[a].first, coord[a].second, coord[b].first, coord[b].second);
	}
}

void Fenetre::renderScene()
{
	Solution best(sol->meilleureSol());
	vector<int> path;
	best.getParcours(path);

	gScene->clear();
	renderCities(0, path.back());
	renderPath(path);
}

void Fenetre::copyFinalPath()
{
	if(sol == NULL)
		return;

	//Solution bestOverall(sol->getBestSol());
	Solution bestOverall(sol->meilleureSol());
	vector<int> final_p;

	bestOverall.getParcours(final_p);
	finalPath.clear();
	for(unsigned int i = 0; i < final_p.size()-1; i++)
		finalPath += QString::number(final_p[i])+"->";
	finalPath += QString::number(final_p[final_p.size()-1]);

	finalPathCost = bestOverall.getScore();
}
