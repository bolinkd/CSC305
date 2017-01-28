#ifndef LIGHT_H
#define LIGHT_H

#include "hitable.h"

class light
{
public:
    vec3 color;
    vec3 point;

    light();
    light(vec3 _p, vec3 _c);

    virtual bool hit(hitrecord &orec, hitrecord &lrec, hitable *world) const;
};

#endif // LIGHT_H
