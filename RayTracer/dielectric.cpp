#include "dielectric.h"

dielectric::dielectric(float _ri)
{
    this->ref_idx = _ri;
    this->light_hits = false;
}

bool dielectric::scatter(const ray &r_in, const hitrecord &rec, vec3 &attenuation, ray &scattered) const {
    vec3 outward_normal;
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    float ni_over_nt;
    attenuation = vec3(1.0,1.0,1.0);
    vec3 refracted;
    float reflect_prob;
    float cosine;
    if (dot(r_in.direction(), rec.normal) > 0) {
        outward_normal = -rec.normal;
        ni_over_nt = ref_idx;
        cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
    }else{
        outward_normal = rec.normal;
        ni_over_nt = 1.0 / ref_idx;
        cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
    }
    if(refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
        reflect_prob = schlick(cosine, ref_idx);
    }else{
        scattered = ray(rec.p, reflected);
        reflect_prob = 1.0;
    }
    if(drand48() < reflect_prob) {
        scattered = ray(rec.p, reflected);
    }else{
        scattered = ray(rec.p, refracted);
    }
    return true;
}
