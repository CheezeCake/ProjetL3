#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include "inputName.hpp"

InputName::InputName(QWidget *parent) : InputForm(parent)
{}

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
	return !(empty());
}

void InputName::fillEmptyNames()
{
	if(empty())
		return;

	QLineEdit *name = NULL;
	char nameStr[30];
	int n = count();

	for(int i = 1; i < n; i += 2)
	{
		name = static_cast<QLineEdit*>(layout->itemAt(i)->widget());

		if(name->text().isEmpty())
		{
			sprintf(nameStr, "Ville %d", (i/2)+1);
			name->setText(nameStr);
		}
	}
}
