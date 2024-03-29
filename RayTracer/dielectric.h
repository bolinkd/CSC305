#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.h"
#include "ray.h"

class dielectric: public material
{
public:
    float ref_idx;
    bool light_hits;

    dielectric(float _ri);

    virtual bool scatter(const ray &r_in, const hitrecord &rec, vec3 &attenuation, ray &scattered) const;
    virtual bool lighthit() { return false;}

};

#endif // DIELECTRIC_H
