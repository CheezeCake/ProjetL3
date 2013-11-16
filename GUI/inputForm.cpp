#include <QtWidgets/QLineEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <cstdio>
#include "inputForm.hpp"

InputForm::InputForm(QWidget *parent) : QScrollArea(parent)
{
	layout = NULL;
	global = NULL;
	setAlignment(Qt::AlignHCenter);
}

void InputForm::deleteForm()
{
	if(global != NULL)
	{
		delete global;
		global = NULL;
	}
}

int InputForm::count()
{
	return (global != NULL) ? layout->count() : 0;
}

bool InputForm::empty()
{
	return (global != NULL) ? layout->isEmpty() : true;
}
