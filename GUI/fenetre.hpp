#ifndef FENETRE_HPP
#define FENETRE_HPP

#include <vector>
#include <QtWidgets/QWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include "inputCoord.hpp"
#include "inputName.hpp"
#include "solver.hpp"

class Fenetre : public QWidget
{
	Q_OBJECT

	private:
		QTabWidget *tab;

		QWidget *pageConfig;
		InputCoord *pageCoord;
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
		std::vector<std::pair<double, double> > coord;
		std::vector<std::string> villes;

		void createPageConfig();
		void getDistances(std::vector<std::vector<double> >&);

		void renderScene();
		void renderCities(int, int);
		void renderPath(std::vector<int>&);

		QLabel *score;
		void updateScore(double);

		void copyFinalPath();
		QString finalPath;
		double finalPathCost;

	private slots:
		void launchSolver();
		void manualInput();
		void fileInput();
		void generate();

		void nextIt();
		void goToEnd();

	public:
		Fenetre(QWidget* = 0);

	public slots:
		void handleTabChanges(int);
};

#endif
