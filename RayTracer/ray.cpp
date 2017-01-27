#include "ray.h"

ray::ray()
{

}

ray::ray(const vec3 &_o, const vec3 &_d){
    this->o = _o;
    this->d = _d;
}
