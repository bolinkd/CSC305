#include <iostream>
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "lambertian.h"
#include "dielectric.h"
#include "metal.h"
#include "plane.h"
#include "light.h"


int num_lights;
vec3 red(1.0f, 0.0f, 0.0f);
vec3 green(0.0f, 1.0f, 0.0f);
vec3 blue(0.0f, 0.0f, 1.0f);
vec3 black(0.0f, 0.0f, 0.0f);
vec3 white(1.0f, 1.0f, 1.0f);

vec3 background(0.5,0.7,1.0);


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

vec3 color(const ray& r, hitable *world, light **lights, int depth) {
    hitrecord rec;
    light *closestLight = NULL;
    float closestDistance = 0;
    if(world->hit(r, 0.01f, FLT_MAX, rec)) {
        for(int i=0; i<num_lights;i++){
            // Check if hit record can see light
            light *tmpLight = lights[i];
            hitrecord tmpRec;
            ray lightray(rec.p + 0.001f, tmpLight->point - rec.p);
            if(!world->lightHit(lightray, 0.001, lightray.d.length(), tmpRec)){
                if( closestLight == NULL or lightray.d.length() < closestDistance){
                    closestLight = tmpLight;
                    closestDistance = lightray.d.length();
                }
            }
        }
        if(closestLight != NULL){
            ray scattered;
            vec3 attenuation;
            if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)){
                return attenuation * ((0.9 * color(scattered, world, lights, depth+1)) + (0.1 * closestLight->color));
            }
        }else{
            return black;
        }
    }
    return background;
}

int main()
{
    int nx = 200;
    int ny = 100;
    int ns = 100;

    vec3 picture[ny][nx];

    //Set Up Objects
    hitable *objects[5];
    light *lights[1];

    lights[0] = new light(vec3(0.0f, 10.0f, 0.0f), white);
    num_lights = sizeof(lights) / sizeof(lights[0]);

    objects[0] = new sphere(vec3(0,0,0), 0.5, new lambertian(red));
    objects[1] = new plane(vec3(0.0,-0.5,0.0), vec3(0.0,1.0,0), new lambertian(blue));
    objects[2] = new sphere(vec3(1,0,-1), 0.5, new metal(green, 1.0));
    objects[3] = new sphere(vec3(-1,0,-1), 0.5, new dielectric(1.5));
    objects[4] = new sphere(vec3(-1,0,-1), -0.45, new dielectric(1.5));

    //Set Up Camera
    vec3 lookfrom(0.0f,2.0f,10.0f);
    vec3 lookat(0.0f,0.0f,0.0f);
    float dist_to_focus = 10.0f;
    float aperture = 0.1f;

    camera cam(lookfrom, lookat, vec3(0,1,0), 20, float(nx)/float(ny), aperture, dist_to_focus);

    hitable *world = new hitable_list(objects, 5);
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
                col += color(r,world,lights,0);
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

