cache()

QT += widgets

SOURCES += main.cpp fenetre.cpp inputForm.cpp \
	inputCoord.cpp inputName.cpp

HEADERS += fenetre.hpp inputForm.hpp \
	inputCoord.hpp inputName.hpp

INCLUDEPATH += ../Core/
LIBS += -L../Core/lib -lsolver
