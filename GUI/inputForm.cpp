#include <QtWidgets/QLineEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <cstdio>
#include "inputForm.hpp"

InputForm::InputForm(QWidget *parent) : QScrollArea(parent)
{
	layout = NULL;
	global = new QWidget;
	setAlignment(Qt::AlignHCenter);
}

void InputForm::deleteForm()
{
	if(layout != NULL)
	{
		delete layout;
		layout = NULL;
	}
}

int InputForm::count()
{
	return (layout != NULL) ? layout->count() : 0;
}

bool InputForm::empty()
{
	return (layout != NULL) ? layout->isEmpty() : true;
}
