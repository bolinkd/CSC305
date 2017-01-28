#ifndef PLANE_H
#define PLANE_H

#include "hitable.h"
#include "dielectric.h"

class plane : public hitable
{
public:
    vec3 normal;
    vec3 p0;
    material *mat_ptr;

    virtual bool hit(const ray &r, float t_min, float t_max, hitrecord &rec) const;
    virtual bool lighthit(const ray &r, float t_min, float t_max, hitrecord &rec) const;

    plane();
    plane(vec3 _p, vec3 _n, material *_m);
};

#endif // PLANE_H
