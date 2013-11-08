#include <QtWidgets/QApplication>
#include "fenetre.hpp"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	Fenetre f;
	f.show();

	return app.exec();
}
