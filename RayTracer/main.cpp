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
#include "light_list.h"

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

vec3 color(const ray& r, hitable *world, light_list *lights, int depth) {
    hitrecord rec;
    vec3 spec;
    float specWeight = 0.0;
    vec3 shading;
    float shadeWeight = 0.1;
    if(world->hit(r, 0.01f, FLT_MAX, rec)) {
        ray scattered;
        vec3 attenuation;
        hitrecord lrec;
        if(lights->hit(rec, 0.01f, rec.t, lrec, world)){
            if(lrec.mat_ptr->lighthit()){
                if(lrec.t < 1 && lrec.t > 0){
                    spec = lrec.p;
                    if(lrec.t > 0.99f){
                        specWeight = lrec.t;
                    }
                    shading = lrec.p*(lrec.t) + black*(1-lrec.t);
                }else{
                    shading = black;
                }
            }else{
                shading = green;
                shadeWeight = 0.0;
            }
        }else{
            shading = black;
        }

        if(depth < 50 && rec.mat_ptr->scatter(r,rec,attenuation,scattered)) {
            return specWeight*(spec*attenuation) + (1.0-specWeight)*attenuation*((1.0-shadeWeight)*color(scattered, world, lights, depth+1)+(shadeWeight*shading));
        }else{
            return black;
        }
    }else{
        return background;
    }
}

int main()
{
    int nx = 500;
    int ny = 500;
    int ns = 100;

    vec3 picture[ny][nx];

    //Set Up Objects
    hitable *olist[5];
    light *llist[1];


    olist[0] = new sphere(vec3(0,0,0), 0.5, new lambertian(red));
    olist[1] = new sphere(vec3(1,0,-1), 0.5, new metal(blue, 0.0));
    olist[2] = new sphere(vec3(-1,0,-1), 0.5, new dielectric(1.5));
    olist[3] = new sphere(vec3(-1,0,-1), -0.45, new dielectric(1.5));
    olist[4] = new plane(vec3(0.0,-0.5,0.0), vec3(0.0,1.0,0.0), new lambertian(green));

    llist[0] = new light(vec3(0.0f, 3.0f, 10.0f), white);

    //Set Up Camera
    vec3 lookfrom(4.0f,2.0f,3.0f);
    vec3 lookat(0.0f,0.0f,0.0f);
    float dist_to_focus = 5.0f;
    float aperture = 0.1f;

    camera cam(lookfrom, lookat, vec3(0,1,0), 45, float(nx)/float(ny), aperture, dist_to_focus);

    hitable *world = new hitable_list(olist, 5);
    //world = random_scene();
    light_list *lights = new light_list(llist, 1);

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

