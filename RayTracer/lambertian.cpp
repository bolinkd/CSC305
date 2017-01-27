#include "lambertian.h"

lambertian::lambertian(const vec3& a)
{
    this->albedo = a;
    this->light_hits = true;
}

bool lambertian::scatter(const ray &r_in, const hitrecord &rec, vec3 &attenuation, ray &scattered) const{
    vec3 target = rec.p + rec.normal + random_in_unit_sphere();
    scattered = ray(rec.p, target-rec.p);
    attenuation = albedo;
    return true;
}

