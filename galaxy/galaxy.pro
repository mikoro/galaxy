QT += core gui
TARGET = galaxy
TEMPLATE = app
#CONFIG += console

SOURCES += main.cpp\
        mainwindow.cpp \
    colorgradient.cpp

HEADERS  += mainwindow.h \
    colorgradient.h

DISTFILES += \
    compute1.glsl \
    compute2.glsl \
    fragment.glsl \
    geometry.glsl \
    vertex.glsl

CONFIG(debug, debug|release): DESTDIR = $$OUT_PWD/debug
CONFIG(release, debug|release): DESTDIR = $$OUT_PWD/release

shaders.path = $$DESTDIR
shaders.files += \
    compute1.glsl \
    compute2.glsl \
    fragment.glsl \
    geometry.glsl \
    vertex.glsl

INSTALLS += shaders
