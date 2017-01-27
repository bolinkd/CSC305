#ifndef LIGHT_H
#define LIGHT_H

#include "ray.h"

class light
{
public:
    vec3 color;
    vec3 point;

    light();
    light(vec3 _p, vec3 _c);
};

#endif // LIGHT_H
