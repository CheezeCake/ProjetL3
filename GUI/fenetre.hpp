#ifndef FENETRE_HPP
#define FENETRE_HPP

#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include "inputPage.hpp"

class Fenetre : public QWidget
{
	Q_OBJECT

	private:
		QWidget *pageConfig;
		InputPage *pageInput;

		QGraphicsView *gView;
		QGraphicsScene *gScene;

		void createPageConfig();

	public:
		Fenetre(QWidget* = 0);
	
	public slots:
		void launchSolver();
};

#endif
