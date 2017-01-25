TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    vec3.cpp \
    ray.cpp \
    sphere.cpp \
    camera.cpp \
    lambertian.cpp \
    metal.cpp \
    dielectric.cpp

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
    dielectric.h
