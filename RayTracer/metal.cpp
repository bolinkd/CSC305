#include "metal.h"

metal::metal(const vec3& _a, float _f)
{
    this->albedo = _a;
    this->fuzz = _f;
}

bool metal::scatter(const ray &r_in, const hitrecord &rec, vec3 &attenuation, ray &scattered) const {
    vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
    attenuation = this->albedo;
    return (dot(scattered.direction(),rec.normal) > 0);
}
