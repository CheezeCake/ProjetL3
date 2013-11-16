#ifndef FENETRE_HPP
#define FENETRE_HPP

#include <QtWidgets/QWidget>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include "inputDist.hpp"
#include "inputName.hpp"

class Fenetre : public QWidget
{
	Q_OBJECT

	private:
		QWidget *pageConfig;
		InputDist *pageDist;
		InputName *pageName;

		QDoubleSpinBox *nbCities;

		QGraphicsView *gView;
		QGraphicsScene *gScene;

		void createPageConfig();

	private slots:
		void launchSolver();
		void manualInput();
		void fileInput();

	public:
		Fenetre(QWidget* = 0);
};

#endif
