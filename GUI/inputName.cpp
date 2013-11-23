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
		// *2 car il faut delete label+lineEdit
		for(int i = n-1; i > cities*2; i--)
			layout->removeItem(layout->itemAt(i));
	}
}

void InputName::createForm(int cities)
{
	deleteForm();
	layout = new QFormLayout;

	for(int i = 0; i < cities; i++)
		addRow(i+1);

	global = new QWidget;
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
	name->setObjectName("champs");

	layout->addRow(nameLabel, name);
}

bool InputName::full()
{
	if(empty())
		return false;

	QLineEdit *name = NULL;
	int n = count();

	for(int i = 1; i < n; i += 2)
	{
		name = static_cast<QLineEdit*>(layout->itemAt(i)->widget());

		if(name->text().isEmpty())
			return true;
	}

	return false;
}
