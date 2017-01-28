TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -fopenmp
LIBS += -fopenmp

SOURCES += main.cpp \
    vec3.cpp \
    ray.cpp \
    sphere.cpp \
    camera.cpp \
    lambertian.cpp \
    metal.cpp \
    dielectric.cpp \
    plane.cpp \
    light.cpp

HEADERS += \
    vec3.h \
    ray.h \
    sphere.h \
    hitable.h \
    hitable_list.h \
    camera.h \
    material.h \
    lambertian.h \
    metal.h \
    dielectric.h \
    plane.h \
    light.h \
    light_list.h

