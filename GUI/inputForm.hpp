#ifndef INPUTFORM_HPP
#define INPUTFORM_HPP

#include <QtWidgets/QScrollArea>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

class InputForm : public QScrollArea
{
	Q_OBJECT

	private:
		QFormLayout *layout;
		QWidget *widget;
		QPushButton *cancelButton;

	public:
		InputForm(QWidget* = 0);

		void createForm(int);
		void deleteForm();

	signals:
		void cancel();
};

#endif
