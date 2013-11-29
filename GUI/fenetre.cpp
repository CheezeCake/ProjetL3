#include <QtWidgets/QPushButton>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSizePolicy>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QLabel>
#include "fenetre.hpp"

Fenetre::Fenetre(QWidget *parent) : QWidget(parent)
{
	sol = NULL;

	//allocation onglets
	createPageConfig();
	pageDist = new InputDist;
	pageName = new InputName;

	tab = new QTabWidget(this);
	tab->addTab(pageConfig, "Config solver");
	tab->addTab(pageDist, "Distances");
	tab->addTab(pageName, "Noms");

	tab->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding));

	//graphe
	gScene = new QGraphicsScene;
	gScene->addLine(5, 10, 90, 150, QPen(QBrush(Qt::SolidPattern), 4));
	gView = new QGraphicsView(gScene);
	QPushButton *nextStep = new QPushButton(">>");

	//affichage central
	QGridLayout *layoutGV = new QGridLayout;
	layoutGV->addWidget(gView, 0, 0);
	layoutGV->addWidget(nextStep, 1, 0, Qt::AlignRight);

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
	QPushButton *generationButton = new QPushButton("Générer");

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
	sizePI->setMinimum(0);

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
	if(!pageDist->full())
		QMessageBox::critical(this, "Erreur", "Pas de données entrées");
	else
	{
		pageName->fillEmptyNames();

		if(sol != NULL)
			delete sol;
	}
}

void Fenetre::fileInput()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Selectionnez un fichier", "", "*.txt");
	printf("fichier selectionné: '%s'\n", fileName.toStdString().c_str());
}

void Fenetre::manualInput()
{
	int n = nbCities->value();

	pageDist->createForm(n);
	pageName->createForm(n);
}

void Fenetre::handleTabChanges(int index)
{
	//tentative d'acces aux onglets des distances et
	//nom de villes sans avoir selectionné une methode
	//d'entrée
	if((index == 1 || index == 2) && pageDist->empty())
	{
		tab->setCurrentIndex(0);
		QMessageBox::information(this, "Attention",
				"Pas de methode d'entrée sélectionnée.\n\n"
				"Sélectionnez l'entrée par fichier ou l'entrée manuelle en entrant un nombre de villes dans l'onglet Config solver");
	}
}
