QT += core
QT += gui
QT += widgets

CONFIG += c++11

QMAKE_CXXFLAGS += -std=c++11

TARGET = sandbox
CONFIG -= console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    sauvegarde.cpp \
    file.cpp \
    pointGPS.cpp \
    track.cpp \
    point.cpp \
    road.cpp \
    solver.cpp \
    grid.cpp \
    pointroad.cpp \
    loading.cpp \
    KDTreeAlgos/box.cpp \
    KDTreeAlgos/boxnode.cpp \
    KDTreeAlgos/kdtree.cpp \
    emissionprobability.cpp \
    KDTreeAlgos/kdtreeviewer.cpp \
<<<<<<< HEAD
    journalprocess.cpp
=======
    GUI/qmapviewer.cpp \
    GUI/controller.cpp
>>>>>>> b4a1f1dabf01dd8776f5a335202a67bf50cef185


HEADERS += \
    sauvegarde.h \
    file.h \
    track.h \
    pointGPS.h \
    myexception.h \
    point.h \
    road.h \
    myexception.h \
    solver.h \
    grid.h \
    pointroad.h \
    loading.h \
    KDTreeAlgos/box.h \
    KDTreeAlgos/boxnode.h \
    KDTreeAlgos/kdtree.h \
    emissionprobability.h \
    KDTreeAlgos/kdtreeviewer.h \
<<<<<<< HEAD
    journalprocess.h \
    qdebugstream.h

FORMS +=
=======
    GUI/qmapviewer.h \
    GUI/controller.h
>>>>>>> b4a1f1dabf01dd8776f5a335202a67bf50cef185

