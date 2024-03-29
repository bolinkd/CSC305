#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"
#include "ray.h"

class lambertian : public material
{
public:
    vec3 albedo;
    bool light_hits;

    lambertian(const vec3& a);

    virtual bool scatter(const ray &r_in, const hitrecord &rec, vec3 &attenuation, ray &scattered) const;
    virtual bool lighthit() { return true;}
};

#endif // LAMBERTIAN_H
