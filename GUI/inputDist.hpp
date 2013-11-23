#ifndef INPUTDIST_HPP
#define INPUTDIST_HPP

#include <QtWidgets/QScrollArea>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "inputForm.hpp"

class InputDist : public InputForm
{
	public:
		InputDist(QWidget* = 0);

		virtual void createForm(int);
		virtual void resizeForm(int);
		virtual bool full();
};

#endif
