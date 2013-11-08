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
	createPageConfig();
	pageInput = new InputPage;

	QTabWidget *tab = new QTabWidget(this);
	tab->addTab(pageConfig, "Config solver");
	tab->addTab(pageInput, "Donnees");

	QSizePolicy sp(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
	tab->setSizePolicy(sp);

	gScene = new QGraphicsScene;
	//gScene->addText("Arretes de futer !!!");
	gScene->addLine(5, 10, 90, 150, QPen(QBrush(Qt::SolidPattern), 4));
	gView = new QGraphicsView(gScene);
	QPushButton *nextStep = new QPushButton(">>");

	QGridLayout *layoutGV = new QGridLayout;
	layoutGV->addWidget(gView, 0, 0);
	layoutGV->addWidget(nextStep, 1, 0, Qt::AlignRight);

    QPushButton *validate = new QPushButton("Lancer solveur");
    QObject::connect(validate, SIGNAL(clicked()), this, SLOT(launchSolver()));

    QVBoxLayout *gauche = new QVBoxLayout;
    gauche->addWidget(tab);
    gauche->addWidget(validate);

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
