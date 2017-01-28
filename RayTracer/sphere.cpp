#include "sphere.h"

bool sphere::hit(const ray& r, float t_min, float t_max, hitrecord &rec) const{
    vec3 oc = r.origin() - this->center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - (this->radius*this->radius);

    float discriminante  = b*b - a*c;
    if (discriminante > 0) {
        float temp = (-b - sqrt(b*b-a*c))/a;
        if(temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - this->center) / this->radius;
            rec.mat_ptr = this->mat_ptr;
            return true;
        }
        temp = (-b + sqrt(b*b-a*c))/a;
        if(temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - this->center) / this->radius;
            rec.mat_ptr = this->mat_ptr;
            return true;
        }
    }
    return false;
}


bool sphere::lighthit(const ray &r, float t_min, float t_max, hitrecord &rec) const{
    rec.mat_ptr = this->mat_ptr;
    if(this->mat_ptr->lighthit()){
        float temp;
        vec3 oc = r.origin() - this->center;
        float a = dot(r.direction(), r.direction());
        float b = dot(oc, r.direction());
        float c = dot(oc, oc) - (this->radius*this->radius);

        float discriminante  = b*b - a*c;
        if (discriminante > 0) {
            temp = (-b - sqrt(b*b-a*c))/a;
            if(temp < t_max && temp > t_min) {
                return true;
            }
            temp = (-b + sqrt(b*b-a*c))/a;
            if(temp < t_max && temp > t_min) {
                return true;
            }
        }
    }
    return false;
}
