#include <iostream>
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "lambertian.h"
#include "dielectric.h"
#include "metal.h"

hitable *random_scene() {
    int n = 500;
    hitable **list = new hitable*[n+1];
    list[0] =  new sphere(vec3(0,-1000,0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float choose_mat = drand48();
            vec3 center(a+0.9*drand48(),0.2,b+0.9*drand48());
            if ((center-vec3(4,0.2,0)).length() > 0.9) {
                if (choose_mat < 0.8) {  // diffuse
                    list[i++] = new sphere(center, 0.2, new lambertian(vec3(drand48()*drand48(), drand48()*drand48(), drand48()*drand48())));
                }
                else if (choose_mat < 0.95) { // metal
                    list[i++] = new sphere(center, 0.2,
                            new metal(vec3(0.5*(1 + drand48()), 0.5*(1 + drand48()), 0.5*(1 + drand48())),  0.5*drand48()));
                }
                else {  // glass
                    list[i++] = new sphere(center, 0.2, new dielectric(1.5));
                }
            }
        }
    }

    list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
    list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
    list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

    return new hitable_list(list,i);
}

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

    vec3 picture[ny][nx];

    //Set Up Objects
    hitable *list[5];

    //float R = cos(M_PI/4);
    //list[0] = new sphere(vec3(-R, 0, -1), R, new lambertian(vec3(0, 0, 1)));
    //list[1] = new sphere(vec3(R, 0, -1), R, new lambertian(vec3(1, 0, 0)));


    list[0] = new sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.1,0.2,0.5)));
    list[1] = new sphere(vec3(0,-100.5,-1), 100, new lambertian(vec3(0.8,0.8,0.0)));
    list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8,0.6,0.2), 1.0));
    list[3] = new sphere(vec3(-1,0,-1), 0.5, new dielectric(1.5));
    list[4] = new sphere(vec3(-1,0,-1), -0.45, new dielectric(1.5));

    //Set Up Camera
    vec3 lookfrom(13,2,3);
    vec3 lookat(0,0,0);
    float dist_to_focus = 10.0;
    float aperture = 0.1;

    camera cam(lookfrom, lookat, vec3(0,1,0), 20, float(nx)/float(ny), aperture, dist_to_focus);

    /*
    vec3 lookfrom = vec3(3, 3, 2);
    vec3 lookat = vec3(0, 0, -1);
    float dist_focus = (lookfrom - lookat).length();
    //camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, float(nx)/float(ny), 2.0, dist_focus);
    camera cam;
*/
    hitable *world = new hitable_list(list, 5);
    world = random_scene();

    //Iterate over pixels
    #pragma omp parallel for
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
            picture[j][i] = vec3( sqrt(col.x), sqrt(col.y), sqrt(col.z));
        }
    }

    //Set Up File
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    // print colors
    for(int j= ny-1; j >= 0; j--){
        for(int i= 0; i<nx; i++ ){
            vec3 col = picture[j][i];
            int ir = int(255.99*col.x);
            int ig = int(255.99*col.y);
            int ib = int(255.99*col.z);
            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }
}

