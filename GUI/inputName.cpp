#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include "inputName.hpp"

InputName::InputName(QWidget *parent) : InputForm(parent)
{}

void InputName::resizeForm(int cities)
{
	int n = count();

	if(cities > n)
	{
		for(int i = n; i <= cities; i++)
			addRow(i);
	}
	else
	{
		for(int i = n-1; i > cities; i--)
			layout->removeItem(layout->itemAt(i));
	}
}

void InputName::createForm(int cities)
{
	deleteForm();
	layout = new QFormLayout;

	for(int i = 0; i < cities; i++)
		addRow(i+1);

	global->setLayout(layout);
	setWidget(global);
}

void InputName::addRow(int i)
{
	char label[30];
	QLabel *nameLabel = NULL;
	QLineEdit *name = NULL;

	sprintf(label, "Ville %d", i);
	nameLabel = new QLabel(label);
	name = new QLineEdit();

	layout->addRow(nameLabel, name);
}
