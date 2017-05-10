TARGET = Lightning
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

#QMAKE_CXXFLAGS+= -pedantic

SOURCES += main.cpp \
    lmatrix.cpp \
    lmathutility.cpp \
    lutility.cpp \
    lvector3.cpp \
    lplane.cpp \
    lquaternion.cpp \
    ltriangle.cpp \
    lvector4.cpp \
    lboundingbox.cpp \
    lboundingsphere.cpp \
    lray.cpp \
    lstring.cpp \
    lmemory.cpp \
    lfile.cpp \
    llog.cpp \
    lvector.cpp \
    lmemorylog.cpp \
    lpair.cpp \
    llist.cpp \
    lmap.cpp


HEADERS += \
    .gitignore\
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
    lboundingbox.h \
    lboundingsphere.h \
    lray.h \
    lconfig.h \
    lstring.h \
    lmemory.h \
    lfile.h \
    Lightning \
    llog.h \
    lvector.h \
    lmemorylog.h \
    lpair.h \
    llist.h \
    lmap.h

