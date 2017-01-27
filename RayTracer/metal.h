#ifndef METAL_H
#define METAL_H

#include "material.h"

class metal : public material
{
public:
    vec3 albedo;
    float fuzz;
    bool light_hits;

    metal(const vec3& _a, float _f);

    virtual bool scatter(const ray &r_in, const hitrecord &rec, vec3 &attenuation, ray &scattered) const;
};

#endif // METAL_H
