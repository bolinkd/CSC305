#include <iostream>
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "lambertian.h"
#include "dielectric.h"
#include "metal.h"

vec3 color(const ray& r, hitable *world, int depth) {
    hitrecord rec;
    if(world->hit(r, 0.001, FLT_MAX, rec)) {
        ray scattered;
        vec3 attenuation;
        if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)){
            return attenuation*color(scattered, world, depth+1);
        }else{
            return vec3(0,0,0);
        }
    }else{
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y + 1.0);
        return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0);
    }
}

int main()
{
    int nx = 200;
    int ny = 100;
    int ns = 100;

    //Set Up File
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    //Set Up Objects
    hitable *list[4];
    list[0] = new sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.1,0.2,0.5)));
    list[1] = new sphere(vec3(0,-100.5,-1), 100, new lambertian(vec3(0.8,0.8,0.0)));
    list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8,0.6,0.2), 1.0));
    list[3] = new sphere(vec3(-1,0,-1), 0.5, new dielectric(1.5));
    list[4] = new sphere(vec3(-1,0,-1), -0.45, new dielectric(1.5));

    //Set Up Camera
    camera cam;

    hitable *world = new hitable_list(list, 5);

    //Iterate over pixels
    for(int j= ny-1; j >= 0; j--){
        for(int i= 0; i<nx; i++ ){
            vec3 col(0,0,0);
            for(int s=0; s<ns; s++){
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                ray r = cam.get_ray(u,v);
                col += color(r,world,0);
            }
            col /= float(ns);
            col = vec3( sqrt(col.x), sqrt(col.y), sqrt(col.z));
            int ir = int(255.99*col.x);
            int ig = int(255.99*col.y);
            int ib = int(255.99*col.z);
            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }
}

