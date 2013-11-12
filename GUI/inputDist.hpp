#ifndef INPUTDIST_HPP
#define INPUTDIST_HPP

#include <QtWidgets/QScrollArea>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

class InputDist : public QScrollArea
{
	Q_OBJECT

	private:
		QFormLayout *layout;
		QWidget *widget;
		QPushButton *cancelButton;

	public:
        InputDist(QWidget* = 0);

		void createForm(int);
		void deleteForm();
	
	signals:
		void cancel();
};

#endif
