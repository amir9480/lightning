TARGET = Lightning
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    lmatrix.cpp \
    lmathutility.cpp \
    lutility.cpp \
    lvector3.cpp \
    lplane.cpp \
    lquaternion.cpp \
    ltriangle.cpp \
    lvector4.cpp \
    lboundingbox.cpp


HEADERS += \
    .gitignore\
    Lightning\
    lmatrix.h \
    ldefines.h \
    lmath.h \
    lmathutility.h \
    lutility.h \
    lvector3.h \
    lplane.h \
    lcore.h \
    lquaternion.h \
    ltriangle.h \
    lvector4.h \
    lboundingbox.h

