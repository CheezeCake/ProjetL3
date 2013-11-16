#ifndef INPUTFORM_HPP
#define INPUTFORM_HPP

#include <QtWidgets/QScrollArea>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

/*
 * Classe abstraite servant de base
 * aux formulaires des distances et noms
 */

class InputForm : public QScrollArea
{
	protected:
		QFormLayout *layout;
		QWidget *global;

	public:
		InputForm(QWidget* = 0);

		virtual void createForm(int) = 0;
		virtual void resizeForm(int) = 0;

		void deleteForm();
		int count();
		bool empty();
};

#endif
