QT += core gui
TARGET = galaxy
TEMPLATE = app

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

shaders.path = $$OUT_PWD
shaders.files += \
    compute1.glsl \
    compute2.glsl \
    fragment.glsl \
    geometry.glsl \
    vertex.glsl

INSTALLS += shaders
