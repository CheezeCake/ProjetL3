#include <QtWidgets/QLineEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <algorithm>
#include <limits>
#include <cstdio>
#include <cmath>
#include "inputCoord.hpp"

using namespace std;

InputCoord::InputCoord(QWidget *parent) : InputForm(parent)
{}

void InputCoord::createForm(int cities)
{
	char nameV1[30];
	QDoubleSpinBox *x = NULL;
	QDoubleSpinBox *y = NULL;

	deleteForm();

	layout = new QFormLayout;

	for(int i = 0; i < cities; i++)
	{
		sprintf(nameV1, "Ville %d", i+1);

		QLabel *V = new QLabel(nameV1);
		x = new QDoubleSpinBox;
		y = new QDoubleSpinBox;

		x->setMaximum(numeric_limits<int>::max());
		y->setMaximum(numeric_limits<int>::max());

		x->setMinimum(numeric_limits<int>::min());
		y->setMinimum(numeric_limits<int>::min());

		QHBoxLayout *ligne = new QHBoxLayout;
		ligne->addWidget(V);
		ligne->addWidget(x);
		ligne->addWidget(y);
		layout->addRow(ligne);
	}

	global = new QWidget;
	global->setLayout(layout);
	setWidget(global);
}

bool InputCoord::full()
{
	if(empty())
		return false;

	int n = count();

	for(int i = 0; i < n; i++)
	{
		if(getSpinboxX(n)->value() == 0.0)
			return false;
	}

	return true;
}

QDoubleSpinBox* InputCoord::getSpinboxY(int n)
{
	if(n > count())
		return NULL;

	return static_cast<QDoubleSpinBox*>(layout->itemAt(n)->layout()->itemAt(2)->widget());
}

QDoubleSpinBox* InputCoord::getSpinboxX(int n)
{
	if(n > count())
		return NULL;

	return static_cast<QDoubleSpinBox*>(layout->itemAt(n)->layout()->itemAt(1)->widget());
}

void InputCoord::setCoordVille(int n, double x, double y)
{
	getSpinboxX(n)->setValue(x);
	getSpinboxY(n)->setValue(y);
}

void InputCoord::setCoord(vector<pair<double, double> > &c)
{
	int n = min(static_cast<int>(c.size()), count());

	for(int i = 0; i < n; i++)
		setCoordVille(i, c[i].first, c[i].second);
}

void InputCoord::getDistances(vector<vector<double> > &d)
{
	int n = count();
	d.resize(n);

	for(int i = 0; i < n; i++)
	{
		d[i].resize(n);
		for(int j = 0; j < n; j++)
		{
			double xi = getSpinboxX(i)->value();
			double yi = getSpinboxY(i)->value();

			double xj = getSpinboxX(j)->value();
			double yj = getSpinboxY(j)->value();

			double x = (xj-xi)*(xj-xi);
			double y = (yj-yi)*(yj-yi);
			d[i][j] = d[j][i] = sqrt(x-y);
		}
	}
}

void InputCoord::getCoord(std::vector<std::pair<double, double> > &c)
{
	int n = count();
	c.resize(n);

	for(int i = 0; i < n; i++)
	{
		c[i].first = getSpinboxX(i)->value();
		c[i].second = getSpinboxY(i)->value();
	}
}
