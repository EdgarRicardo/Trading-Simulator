QT += widgets
QT += charts
QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11
SOURCES += \
        main.cpp \
    cdevise.cpp \
    menu.cpp \
    ccours.cpp \
    cpaires.cpp \
    modeselection.cpp \
    simulation.cpp \
    simulationauto.cpp \
    simulationmanualc.cpp \
    simulationmanualpap.cpp \
    simulationselection.cpp \
    trading.cpp \
    montrerohlc.cpp \
    evolutionviewer.cpp \
    addindicateur.cpp \
    indicateurs.cpp \
    csvfichier.cpp \
    menucvs.cpp

HEADERS += \
    headerp.h \
    cdevise.h \
    menu.h \
    cpaires.h \
    ccours.h \
    modeselection.h \
    simulation.h \
    simulationauto.h \
    simulationmanualc.h \
    simulationmanualpap.h \
    simulationselection.h \
    trading.h \
    montrerohlc.h \
    evolutionviewer.h \
    addindicateur.h \
    csvfichier.h \
    menucsv.h

FORMS += \
    modeselection.ui \
    simulationauto.ui \
    simulationmanualc.ui \
    simulationmanualpap.ui \
    simulationselection.ui

 RC_ICONS = iconT.ico
