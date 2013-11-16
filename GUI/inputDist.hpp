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

		void createForm(int);
		void resizeForm(int);
};

#endif
