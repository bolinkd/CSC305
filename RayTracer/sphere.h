#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"

class sphere : public hitable
{
public:
    sphere() {}
    sphere(vec3 _center, float _r, material *_m) : center(_center), radius(_r), mat_ptr(_m) {}
    virtual bool hit(const ray& r, float t_min, float t_max, hitrecord& rec) const;
    vec3 center;
    float radius;
    material *mat_ptr;
};


#endif // SPHERE_H
