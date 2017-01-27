#ifndef HITABLE_H
#define HITABLE_H

#include "ray.h"

class material;

struct hitrecord {
    float t;
    vec3 p;
    vec3 normal;
    material *mat_ptr;
};

class hitable {
    public:
        virtual bool hit(const ray& r, float t_min, float t_max, hitrecord& rec) const = 0;
        virtual bool lightHit(const ray& r, float t_min, float t_max, hitrecord& rec) const = 0;
};


#endif // HITABLE_H

