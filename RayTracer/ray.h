#ifndef RAY_H
#define RAY_H

#include "vec3.h"


class ray
{
public:
    vec3 o;
    vec3 d;

    ray();
    ray(const vec3& _o, const vec3& _d);
    vec3 origin() const { return o; }
    vec3 direction() const { return d; }
    vec3 point_at_parameter(float t) const { return o + t*d; }
};

#endif // RAY_H
