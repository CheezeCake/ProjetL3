#include <QtWidgets/QTabWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSizePolicy>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QFileDialog>
#include "fenetre.hpp"

//pour debug
#include <cstdio>

Fenetre::Fenetre(QWidget *parent) : QWidget(parent)
{
	//allocation onglets
	createPageConfig();
	pageDist = new InputDist;
	pageName = new InputName;

	QTabWidget *tab = new QTabWidget(this);
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
	resize(sizeTab.width()*8, sizeTab.height()*15);
}

void Fenetre::createPageConfig()
{
	//options chargement des données
	QPushButton *fileInputButton = new QPushButton("Chargement par fichier");
	QObject::connect(fileInputButton, SIGNAL(clicked()), this, SLOT(fileInput()));

	nbCities = new QDoubleSpinBox;
	nbCities->setDecimals(0);
	nbCities->setMinimum(3);
	QPushButton *validateInput = new QPushButton("Valider");
	QObject::connect(validateInput, SIGNAL(clicked()), this, SLOT(manualInput()));

	QFormLayout *layoutBoxInput = new QFormLayout;
	layoutBoxInput->addRow(fileInputButton);
	layoutBoxInput->addRow("Nombre de villes:", nbCities);
	layoutBoxInput->addRow(validateInput);

	QGroupBox *boxInput = new QGroupBox("Options entrée des données");
	boxInput->setLayout(layoutBoxInput);
	boxInput->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed));

	//options du solver
	QComboBox *selectionChoice = new QComboBox;
	QDoubleSpinBox *sizePI = new QDoubleSpinBox;
	sizePI->setDecimals(0);
	sizePI->setMinimum(0);

	QFormLayout *layoutConfig = new QFormLayout;
	layoutConfig->addRow("Taille PI:", sizePI);
	layoutConfig->addRow("Methode selection:", selectionChoice);

	//layout global
	QVBoxLayout *layoutPage = new QVBoxLayout;
	layoutPage->addWidget(boxInput);
	layoutPage->addLayout(layoutConfig);

	pageConfig = new QWidget;
	pageConfig->setLayout(layoutPage);
}

void Fenetre::launchSolver()
{
	if(!pageDist->full())
	   QMessageBox::critical(this, "Erreur", "Pas de données entrées");
}

void Fenetre::fileInput()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Selectionnez un fichier", "", "*.txt");
	printf("fichier selectionné: '%s'\n", fileName.toStdString().c_str());
}

void Fenetre::manualInput()
{
	if(!pageDist->empty())
		pageDist->deleteForm();

	if(!pageName->empty())
		pageName->deleteForm();

	int n = nbCities->value();

	pageDist->createForm(n);
	pageName->createForm(n);
}
