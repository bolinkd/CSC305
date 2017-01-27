#include "plane.h"
#include <float.h>

plane::plane()
{

}

plane::plane(vec3 _p, vec3 _n, material *_m){
    this->p0 = _p;
    this->normal = unit_vector(_n);
    this->mat_ptr = _m;
}

bool plane::hit(const ray &r, float t_min, float t_max, hitrecord &rec) const{
    float denom = dot(this->normal, r.direction());
    if(denom != 0 ) {
        float temp = dot(this->normal, this->p0 - r.origin()) / denom;
        if(temp < t_max && temp > t_min){
            rec.normal = this->normal;
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.mat_ptr = this->mat_ptr;

            return true;
        }
    }
    return false;
}

bool plane::lightHit(const ray& r, float t_min, float t_max, hitrecord& rec) const{
    if(dynamic_cast<dielectric*>(this->mat_ptr) == NULL){
        return true;
    }
    return false;
}
