#ifndef INPUTPAGE_HPP
#define INPUTPAGE_HPP

#include <QtWidgets/QWidget>
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QDoubleSpinBox>
#include "inputForm.hpp"

class InputPage : public QWidget
{
	Q_OBJECT

	private:
		QWidget *inputChoices;
		QDoubleSpinBox *nbCities;

		InputForm *form;

		QStackedLayout *mainLayout;

		void createInputChoicesPage();
	
	public:
		InputPage(QWidget* = 0);

		bool empty();
		enum PageIndex { PAGE_CHOICE = 0, PAGE_FORM };

	public slots:
		void switchPage();
		void switchToForm();
		void switchToChoice();
		void selectFile();
};

#endif
