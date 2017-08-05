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
    lcore/lmemorystream.cpp \
    lcore/lvariant.cpp \
    lcore/lfunction.cpp \
    los/windows/lwindowapplication.cpp \
    los/linput.cpp \
    los/lapplication.cpp \
    lgfx/lgfxdevice.cpp \
    lgfx/lgfxindexbuffer.cpp \
    lgfx/lgfxshader.cpp \
    lgfx/lgfxvertexbuffer.cpp \
    lgfx/lgfxtexture.cpp \
    lgfx/limage.cpp \
    lgfx/D3D9/ld3d9device.cpp \
    lgfx/D3D9/ld3d9indexbuffer.cpp \
    lgfx/D3D9/ld3d9vertexbuffer.cpp \
    lgfx/D3D9/ld3d9texture.cpp \
    lgfx/D3D9/ld3d9shader.cpp


HEADERS +=\
    Lightning \
    lconfig.h \
    lcore.h \
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
    lcore/lmemorystream.h \
    lcore/lvariant.h \
    lcore/lfunction.h \
    los.h \
    los/windows/lwindowapplication.h \
    los/lapplication.h \
    los/linput.h\
    lgfx.h \
    lgfx/lgfxdevice.h \
    lgfx/lgfxindexbuffer.h \
    lgfx/lgfxshader.h \
    lgfx/lgfxvertexbuffer.h \
    lgfx/lgfxtexture.h \
    lgfx/limage.h \
    lgfx/D3D9/ld3d9.h \
    lgfx/D3D9/ld3d9device.h \
    lgfx/D3D9/ld3d9indexbuffer.h \
    lgfx/D3D9/ld3d9vertexbuffer.h \
    lgfx/D3D9/ld3d9texture.h \
    lgfx/D3D9/ld3d9shader.h

DISTFILES += \
    .gitignore


# D3D9

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/dependencies/Directx9/Lib/x86/ -ld3d9 -ld3dx9
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/dependencies/Directx9/Lib/x86/ -ld3d9 -ld3dx9d

INCLUDEPATH += $$PWD/lgfx/D3D9/Directx/Include
DEPENDPATH += $$PWD/lgfx/D3D9/Directx/Include

QMAKE_CXXFLAGS += -isystem $$PWD/dependencies/Directx9/Include #prevent form warnings


# D3D9 End


#zlib
win32: LIBS += -L$$PWD/dependencies/zlib/buildMinGW/ -llibzlib.dll

INCLUDEPATH += $$PWD/dependencies/zlib
DEPENDPATH += $$PWD/dependencies/zlib


#lib PNG
win32: LIBS += -L$$PWD/dependencies/libpng/buildMinGW/ -lpng

INCLUDEPATH += $$PWD/dependencies/libpng
DEPENDPATH += $$PWD/dependencies/libpng
