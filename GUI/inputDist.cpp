#include <QtWidgets/QLineEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <cstdio>
#include "inputDist.hpp"

InputDist::InputDist(QWidget *parent) : QScrollArea(parent)
{
	layout = NULL;
	cancelButton = new QPushButton("Annuler");
	widget = new QWidget;
	setAlignment(Qt::AlignHCenter);

	QObject::connect(cancelButton, SIGNAL(clicked()), this, SIGNAL(cancel()));
}

void InputDist::deleteForm()
{
	if(layout != NULL)
	{
		delete layout;
		layout = NULL;
	}
}

void InputDist::createForm(int cities)
{
	char nameV1[30];
	char nameV2[30];
	QDoubleSpinBox *dist;

	deleteForm();
	layout = new QFormLayout;
	layout->addRow(cancelButton);

	for(int i = 0; i < cities; i++)
	{
		for(int j = 0; j < cities; j++)
		{
			if(i != j)
			{
				sprintf(nameV1, "Ville %d", i+1);
				sprintf(nameV2, "Ville %d", j+1);
				QLabel *V1 = new QLabel(nameV1);
				dist = new QDoubleSpinBox();
				QLabel *V2 = new QLabel(nameV2);
				QHBoxLayout *ligne = new QHBoxLayout;
				ligne->addWidget(V1);
				ligne->addWidget(dist);
				ligne->addWidget(V2);
				layout->addRow(ligne);
			}
		}
	}

	widget->setLayout(layout);
	setWidget(widget);
}
