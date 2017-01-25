#include "camera.h"

camera::camera()
{
    this->lower_left_corner = vec3(-2.0,-1.0,-1.0);
    this->horizontal = vec3(4.0,0.0,0.0);
    this->vertical = vec3(0.0,2.0,0.0);
    this->origin = vec3(0.0,0.0,0.0);
}

camera::camera(vec3 _origin, vec3 _lower_left_corner, vec3 _horizontal, vec3 _vertical){
    this->origin = _origin;
    this->lower_left_corner = _lower_left_corner;
    this->horizontal = _horizontal;
    this->vertical = _vertical;
}

ray camera::get_ray(float u, float v){
    return ray(this->origin, this->lower_left_corner + u*this->horizontal+ v*this->vertical - this->origin);
}


