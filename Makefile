QMAKE=qmake-qt5
LIBSOLVER_FLAGS="LIBS+=-L../Core/lib/ -lsolver"

all:
	@(cd ./Core && $(MAKE))
	@(cd ./GUI && $(QMAKE) $(LIBSOLVER_FLAGS) && $(MAKE))

.PHONY: clean_core clean_gui clean mrproper rebuild

clean: clean_core clean_gui

clean_core:
	@(cd ./Core && $(MAKE) clean)

clean_gui:
	@(cd ./GUI && $(MAKE) clean)

mrproper:
	@(cd ./Core && $(MAKE) $@)
	@(cd ./GUI && $(MAKE) distclean)

rebuild: clean all
