TARGET = Lightning
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt



#QMAKE_CXXFLAGS+= -pedantic
#QMAKE_LFLAGS += -static

SOURCES +=\
    main.cpp\
    lcore/lboundingbox.cpp \
    lcore/lboundingsphere.cpp \
    lcore/lfile.cpp \
    lcore/llist.cpp \
    lcore/llog.cpp \
    lcore/lmap.cpp \
    lcore/lmathutility.cpp \
    lcore/lmatrix.cpp \
    lcore/lmemory.cpp \
    lcore/lmemorylog.cpp \
    lcore/lmemorymanager.cpp \
    lcore/lpair.cpp \
    lcore/lplane.cpp \
    lcore/lquaternion.cpp \
    lcore/lray.cpp \
    lcore/lstring.cpp \
    lcore/ltriangle.cpp \
    lcore/lutility.cpp \
    lcore/lvector.cpp \
    lcore/lvector2.cpp \
    lcore/lvector3.cpp \
    lcore/lvector4.cpp \
    lgfx/D3D9/ld3d9device.cpp \
    lgfx/D3D9/ld3d9indexbuffer.cpp \
    lgfx/D3D9/ld3d9vertexbuffer.cpp \
    los/windows/lwindowapplication.cpp \
    los/lapplication.cpp \
    lgfx/lgfxdevice.cpp \
    lgfx/lgfxindexbuffer.cpp \
    lgfx/lgfxshader.cpp \
    lgfx/lgfxvertexbuffer.cpp \
    lgfx/D3D9/ld3d9shader.cpp


HEADERS +=\
    lcore/lboundingbox.h \
    lcore/lboundingsphere.h \
    lcore/ldefines.h \
    lcore/lfile.h \
    lcore/llist.h \
    lcore/llog.h \
    lcore/lmap.h \
    lcore/lmath.h \
    lcore/lmathutility.h \
    lcore/lmatrix.h \
    lcore/lmemory.h \
    lcore/lmemorylog.h \
    lcore/lmemorymanager.h \
    lcore/lpair.h \
    lcore/lplane.h \
    lcore/lquaternion.h \
    lcore/lray.h \
    lcore/lstring.h \
    lcore/ltriangle.h \
    lcore/lutility.h \
    lcore/lvector.h \
    lcore/lvector2.h \
    lcore/lvector3.h \
    lcore/lvector4.h \
    lgfx/D3D9/ld3d9.h \
    lgfx/D3D9/ld3d9device.h \
    lgfx/D3D9/ld3d9indexbuffer.h \
    lgfx/D3D9/ld3d9vertexbuffer.h \
    los/windows/lwindowapplication.h \
    los/lapplication.h \
    lconfig.h \
    lcore.h \
    lgfx.h \
    Lightning \
    los.h \
    lgfx/lgfxdevice.h \
    lgfx/lgfxindexbuffer.h \
    lgfx/lgfxshader.h \
    lgfx/lgfxvertexbuffer.h \
    lgfx/D3D9/ld3d9shader.h



# D3D9

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lgfx/D3D9/Directx/Lib/x86/ -ld3d9 -ld3dx9
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lgfx/D3D9/Directx/Lib/x86/ -ld3d9 -ld3dx9d

INCLUDEPATH += $$PWD/lgfx/D3D9/Directx/Include
DEPENDPATH += $$PWD/lgfx/D3D9/Directx/Include

QMAKE_CXXFLAGS += -isystem $$PWD/lgfx/D3D9/Directx/Include #prevent form warnings


# D3D9 End

DISTFILES += \
    .gitignore

