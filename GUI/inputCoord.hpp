#ifndef INPUTCOORD_HPP
#define INPUTCOORD_HPP

#include <QtWidgets/QScrollArea>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <vector>
#include "inputForm.hpp"

class InputCoord : public InputForm
{
	private:
		QDoubleSpinBox* getSpinboxX(int n);
		QDoubleSpinBox* getSpinboxY(int n);

	public:
		InputCoord(QWidget* = 0);

		virtual void createForm(int);
		virtual bool full();

		void setCoord(std::vector<std::pair<double, double> >&);
		void getCoord(std::vector<std::pair<double, double> >&);

		void getDistances(std::vector<std::vector<double> >&);

		void setCoordVille(int n, double x, double y);
};

#endif
