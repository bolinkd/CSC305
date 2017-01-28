#include "light.h"

light::light()
{

}

light::light(vec3 _p, vec3 _c){
    this->color = _c;
    this->point = _p;
}

bool light::hit(hitrecord &orec, hitrecord &lrec, hitable *world) const{
    ray r(orec.p, unit_vector(this->point - orec.p));
    float t = dot(orec.normal, r.direction());
    //std::cerr << t << std::endl;
    if(!world->lighthit(r, 0.01f, t, lrec)){
        lrec.p = this->color;
        lrec.t = t;
        return true;
    }
    return false;
}
