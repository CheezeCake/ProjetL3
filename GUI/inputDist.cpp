#include <QtWidgets/QLineEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <cstdio>
#include "inputDist.hpp"

InputDist::InputDist(QWidget *parent) : InputForm(parent)
{}

void InputDist::resizeForm(int cities)
{
	createForm(cities);
}

void InputDist::createForm(int cities)
{
	char nameV1[30];
	char nameV2[30];
	QDoubleSpinBox *dist;

	deleteForm();

	layout = new QFormLayout;

	for(int i = 0; i < cities; i++)
	{
		for(int j = i+1; j < cities; j++)
		{
			sprintf(nameV1, "Ville %d", i+1);
			sprintf(nameV2, "Ville %d", j+1);

			QLabel *V1 = new QLabel(nameV1);
			QLabel *V2 = new QLabel(nameV2);
			dist = new QDoubleSpinBox();

			QHBoxLayout *ligne = new QHBoxLayout;
			ligne->addWidget(V1);
			ligne->addWidget(dist);
			ligne->addWidget(V2);
			layout->addRow(ligne);
		}
	}

	global = new QWidget;
	global->setLayout(layout);
	setWidget(global);
}

bool InputDist::full()
{
	if(empty())
		return false;

	QDoubleSpinBox *spinbox = NULL;
	int n = count();

	for(int i = 0; i < n; i++)
	{
		spinbox = static_cast<QDoubleSpinBox*>(layout->itemAt(i)->layout()->itemAt(1)->widget());

		if(spinbox->value() == 0.0)
			return false;
	}

	return true;
}
