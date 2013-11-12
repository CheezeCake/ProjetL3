#include <QtWidgets/QLineEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <cstdio>
#include "inputForm.hpp"

InputForm::InputForm(QWidget *parent) : QScrollArea(parent)
{
	layout = NULL;
	cancelButton = new QPushButton("Annuler");
	widget = new QWidget;
	setAlignment(Qt::AlignHCenter);

	QObject::connect(cancelButton, SIGNAL(clicked()), this, SIGNAL(cancel()));
}

void InputForm::deleteForm()
{
	if(layout != NULL)
	{
		delete layout;
		layout = NULL;
	}
}

void InputForm::createForm(int cities)
{
	char nameStr[30];
	QLineEdit *name = NULL;

    deleteForm();
	layout = new QFormLayout;
	layout->addRow(cancelButton);

	for(int i = 0; i < cities; i++)
	{
		sprintf(nameStr, "Ville %d:", i+1);
		name = new QLineEdit();
		layout->addRow(nameStr, name);
	}

	widget->setLayout(layout);
	setWidget(widget);
}
