#include "camera.h"

camera::camera()
{
    //camera()
}

camera::camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist){
    this->lens_radius = aperture / 2;
    float theta = vfov * M_PI/180;
    float half_height = tan(theta/2);
    float half_width = aspect * half_height;
    this->origin = lookfrom;
    this->w = unit_vector(lookfrom - lookat);
    this->u = unit_vector(cross(vup, this->w));
    this->v = cross(this->w, this->u);
    this->lower_left_corner = origin - half_width*focus_dist*u - half_height*focus_dist*v - focus_dist*w;
    this->horizontal = 2*focus_dist*half_width*u;
    this->vertical = 2*focus_dist*half_height*v;
}

vec3 random_in_unit_disk(){
    vec3 p;
    do{
        p = 2.0*vec3(drand48(),drand48(),0) - vec3(1,1,0);
    }while(dot(p,p) >= 1.0);
    return p;
}

ray camera::get_ray(float s, float t){
    vec3 rd = lens_radius*random_in_unit_disk();
    vec3 offset = this->u * rd.x + this->v * rd.y;
    return ray(this->origin + offset, this->lower_left_corner + s*this->horizontal+ t*this->vertical - this->origin - offset);
}


