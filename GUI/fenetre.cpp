#include <QtWidgets/QTabWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSizePolicy>
#include <QtWidgets/QMessageBox>
#include "fenetre.hpp"

//pour debug
#include <cstdio>

Fenetre::Fenetre(QWidget *parent) : QWidget(parent)
{
    //allocation onglets
    createPageConfig();
	pageInput = new InputPage;
    pageDist = new InputDist;

	QTabWidget *tab = new QTabWidget(this);
	tab->addTab(pageConfig, "Config solver");
	tab->addTab(pageInput, "Donnees");
    tab->addTab(pageDist, "Distances");

	QSizePolicy sp(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
	tab->setSizePolicy(sp);

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
	QComboBox *selectionChoice = new QComboBox;
	QDoubleSpinBox *sizePI = new QDoubleSpinBox;
	sizePI->setDecimals(0);
	sizePI->setMinimum(0);
	
	QFormLayout *layoutConfig = new QFormLayout;
	layoutConfig->addRow("Taille PI:", sizePI);
	layoutConfig->addRow("Methode selection:", selectionChoice);

	pageConfig = new QWidget;
	pageConfig->setLayout(layoutConfig);

}

void Fenetre::launchSolver()
{
	if(pageInput->empty())
        QMessageBox::critical(this, "Erreur", "Pas de données entrées");
	/*
	 * else
	 *	lancer le bordel
	 */
}
