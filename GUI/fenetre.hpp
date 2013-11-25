#ifndef FENETRE_HPP
#define FENETRE_HPP

#include <QtWidgets/QWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include "inputDist.hpp"
#include "inputName.hpp"

class Fenetre : public QWidget
{
	Q_OBJECT

	private:
		QTabWidget *tab;

		QWidget *pageConfig;
		InputDist *pageDist;
		InputName *pageName;

		//input
		QDoubleSpinBox *nbCities;

		//solver
		QDoubleSpinBox *sizePI;
		QComboBox *selectSelection;
		QComboBox *selectCroisement;
		QComboBox *selectRemplacement;

		QGraphicsView *gView;
		QGraphicsScene *gScene;

		void createPageConfig();

	private slots:
		void launchSolver();
		void manualInput();
		void fileInput();

	public:
		Fenetre(QWidget* = 0);

	public slots:
		void handleTabChanges(int);
};

#endif
