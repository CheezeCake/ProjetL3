#include <QtWidgets/QFormLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include "inputPage.hpp"

#include <cstdio>

InputPage::InputPage(QWidget *parent) : QWidget(parent)
{
	form = new InputForm(this);
	createInputChoicesPage();

	mainLayout = new QStackedLayout;
	mainLayout->addWidget(inputChoices);
	mainLayout->addWidget(form);

	setLayout(mainLayout);
}

void InputPage::createInputChoicesPage()
{
	QPushButton *file = new QPushButton("Chargement via fichier");

	QLabel *label = new QLabel("Nombre de villes:");
	nbCities = new QDoubleSpinBox;
	nbCities->setDecimals(0);
    nbCities->setMinimum(3);
	QPushButton *confirmManualInput = new QPushButton("Valider");

	QHBoxLayout *formManualInput = new QHBoxLayout;
	formManualInput->addWidget(label);
	formManualInput->addWidget(nbCities);
	formManualInput->addWidget(confirmManualInput);

	QFormLayout *layout = new QFormLayout;
	layout->addRow(file);
	layout->addRow(formManualInput);

	inputChoices = new QWidget(this);
	inputChoices->setLayout(layout);

	QObject::connect(confirmManualInput, SIGNAL(clicked()), this, SLOT(switchToForm()));
	QObject::connect(form, SIGNAL(cancel()), this, SLOT(switchToChoice()));
	QObject::connect(file, SIGNAL(clicked()), this, SLOT(selectFile()));
}

void InputPage::switchPage()
{
	int index = mainLayout->currentIndex();
	mainLayout->setCurrentIndex((index == InputPage::PAGE_CHOICE)
												? InputPage::PAGE_FORM
												: InputPage::PAGE_CHOICE);
}

void InputPage::switchToForm()
{
	int n = nbCities->value();
	if(n == 0)
        QMessageBox::critical(this, "Erreur", "Entrez au moins 3 villes");
	else
	{
		form->createForm(n);
		mainLayout->setCurrentIndex(InputPage::PAGE_FORM);
	}
}

void InputPage::switchToChoice()
{
	form->deleteForm();
	mainLayout->setCurrentIndex(InputPage::PAGE_CHOICE);
}

bool InputPage::empty()
{
	return (mainLayout->currentIndex() == PAGE_CHOICE);
}

void InputPage::selectFile()
{
	    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "*.txt");

		printf("fichier: %s\n", fichier.toStdString().c_str());
}
