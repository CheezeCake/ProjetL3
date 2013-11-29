#ifndef FENETRE_HPP
#define FENETRE_HPP

#include <vector>
#include <pair>
#include <QtWidgets/QWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include "inputDist.hpp"
#include "inputName.hpp"
#include "solver.hpp"

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
		QDoubleSpinBox *nbCitiesGen;

		//solver
		QDoubleSpinBox *sizePI;
		QComboBox *selectSelection;
		QComboBox *selectCroisement;
		QComboBox *selectRemplacement;

		QGraphicsView *gView;
		QGraphicsScene *gScene;

		Solver *sol;
		std::vector<pair<int> > coord;

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
