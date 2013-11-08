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


	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addWidget(tab);
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

	QPushButton *validate = new QPushButton("Lancer solveur");
	layoutConfig->addRow(validate);

	pageConfig = new QWidget;
	pageConfig->setLayout(layoutConfig);

	QObject::connect(validate, SIGNAL(clicked()), this, SLOT(launchSolver()));
}

void Fenetre::launchSolver()
{
	if(pageInput->empty())
		QMessageBox::critical(this, "STOP FUTING !!!", "Entre des donnees futeur de merde");
	/*
	 * else
	 *	lancer le bordel
	 */
}
