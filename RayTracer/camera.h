#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class camera
{
public:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;

    camera();
    camera(vec3 _origin, vec3 _lower_left_corner, vec3 _horizontal, vec3 _vertical);
    ray get_ray(float u, float v);
};

#endif // CAMERA_H
