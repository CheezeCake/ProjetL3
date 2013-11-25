#include <QtWidgets/QLineEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <cstdio>
#include "inputDist.hpp"

InputDist::InputDist(QWidget *parent) : InputForm(parent)
{}

void InputDist::createForm(int cities)
{
	char nameV1[30];
	QDoubleSpinBox *x = NULL;
	QDoubleSpinBox *y = NULL;

	deleteForm();

	layout = new QFormLayout;

	for(int i = 0; i < cities; i++)
	{
		sprintf(nameV1, "Ville %d", i+1);

		QLabel *V = new QLabel(nameV1);
		x = new QDoubleSpinBox;
		y = new QDoubleSpinBox;

		QHBoxLayout *ligne = new QHBoxLayout;
		ligne->addWidget(V);
		ligne->addWidget(x);
		ligne->addWidget(y);
		layout->addRow(ligne);
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
	QDoubleSpinBox *spinbox1 = NULL;
	int n = count();

	for(int i = 0; i < n; i++)
	{
		spinbox = static_cast<QDoubleSpinBox*>(layout->itemAt(i)->layout()->itemAt(1)->widget());
		spinbox1 = static_cast<QDoubleSpinBox*>(layout->itemAt(i)->layout()->itemAt(2)->widget());

		if(spinbox->value() == 0.0)
			return false;
	}

	return true;
}
