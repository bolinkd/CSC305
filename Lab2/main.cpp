#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <iostream>
#include "stb_image_write.h"

struct rgba8 {
    unsigned char r, g, b, a;
    rgba8() { }
    rgba8(unsigned char rr, unsigned char gg, unsigned char bb, unsigned char aa)
    : r(rr),g(gg),b(bb),a(aa) { }
};
struct vec3 {
    float x, y, z;
    vec3() { }
    vec3(float xx, float yy, float zz)
    : x(xx), y(yy), z(zz) { }
};
struct ray {
    vec3 o, d;
    ray() { }
    ray(vec3 oo, vec3 dd)
    : o(oo), d(dd) { }
};
struct triangle {
    vec3 a, b, c;
    triangle() { }
    triangle(vec3 aa, vec3 bb, vec3 cc)
    : a(aa), b(bb), c(cc) { }
};

rgba8 hdr_to_ldr(vec3 hdr) { return rgba8((unsigned char)(255 * powf(hdr.x, 1.0f / 2.2f)), (unsigned char)(255 * powf(hdr.y, 1.0f / 2.2f)), (unsigned char)(255 * powf(hdr.z, 1.0f / 2.2f)), 255); }
vec3 cross(vec3 a, vec3 b) { return vec3(a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y); }
float dot(vec3 a, vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
float length(vec3 v) { return sqrtf(dot(v, v)); }
vec3 operator+(vec3 a, vec3 b) { return vec3(a.x + b.x, a.y + b.y, a.z + b.z); }
vec3 operator-(vec3 a, vec3 b) { return vec3(a.x - b.x, a.y - b.y, a.z - b.z); }
vec3 operator-(vec3 v) { return vec3(-v.x, -v.y, -v.z); }
vec3 operator*(float u, vec3 v) { return vec3(u * v.x, u * v.y, u * v.z); }
vec3 operator*(vec3 v, float u) { return u * v; }
vec3 operator/(vec3 v, float u) { return vec3(v.x / u, v.y / u, v.z / u); }

float double_triangle_area(triangle tr){
    return length(cross(tr.b - tr.a, tr.c - tr.a));
}

bool intersect(ray r, triangle tr, vec3* bary)
{
    // TODO: Compute normal of triangle (see slide 3 of ray3.pdf.)
    vec3 n;
    n = cross(tr.b-tr.a, tr.b-tr.c);


    // TODO: Compute distance of ray origin to triangle (see slide 3 of ray3.pdf.)
    float t;
    t = dot(n,tr.b-r.o)/dot(n,r.d);

    // TODO: Compute point of intersection (see slide 3 of ray3.pdf.)
    vec3 p;
    p = r.o + r.d*t;


    // TODO: Compute the 3 equations in the green square on the right side of slide 3 of ray3.pdf.
    //       If the signs of the three equations differ, then return false.

    bool s1 = dot(cross(tr.b-tr.a, p-tr.a), n) > 0;
    bool s2 = dot(cross(tr.c-tr.b, p-tr.b), n) > 0;
    bool s3 = dot(cross(tr.a-tr.c, p-tr.c), n) > 0;
    bool rtn = false;

    if ((s1 && s2 && s3) || (!s1 && !s2 && !s3)){
        rtn = true;
        // TODO: Compute barycentric coordinates at point p.
        // See slide 12 of ray3.pdf.
        // Hint: area(A,B,C) == length(cross(B - A, C - A)) / 2
        bary->x = length(cross(tr.a-p, tr.b-p)) / length(n); // Area(PAB)/Area(ABC)
        bary->y = length(cross(tr.b-p, tr.c-p)) / length(n); // Area(PBC)/Area(ABC)
        bary->z = length(cross(tr.c-p, tr.a-p)) / length(n); // Area(PCA)/Area(ABC)

    }

    return rtn;
}

void raytrace()
{
    // allocate image
    int width = 640;
    int height = 480;
    rgba8* pixels = new rgba8[width * height];

    // clear to black
    memset(pixels, 0, width * height * sizeof(*pixels));

    // the triangle to intersect
    triangle tr = triangle(vec3(-1.0f, -1.0f, 0.0f), vec3(1.0f, -1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f));

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // construct ray for this pixel (orthographic projection)
            ray r;
            r.o = vec3(x / (width / 2.0f) - 1.0f, (height - y - 1) / (height / 2.0f) - 1.0f, 0.0f);
            r.d = vec3(0.0f, 0.0f, 1.0f);

            // test ray intersection with the triangle
            vec3 bary;
            if (intersect(r, tr, &bary))
            {
                // if the triangle intersected, output the barycentric coordinate as color.
                pixels[y * width + x] = hdr_to_ldr(bary);
            }
        }
    }

    // write image to file
    stbi_write_png("raytrace.png", width, height, 4, pixels, width * 4);

#ifdef _WIN32
    // Display the image automatically on Windows
    system("raytrace.png");
#else
    // Display the image automatically on MacOS
    system("xdg-open raytrace.png");
#endif

    delete[] pixels;
}

void rasterize()
{
    // allocate image
    int width = 640;
    int height = 480;
    rgba8* pixels = new rgba8[width * height];

    // clear to black
    memset(pixels, 0, width * height * sizeof(*pixels));

    // the triangle to intersect
    // note: z = 0 since we assume it's already projected onto the screen...
    triangle tr = triangle(vec3(-1.0f, -1.0f, 0.0f), vec3(1.0f, -1.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f));

    // TODO: Compute double the area of the triangle.
    float double_area = length(cross(tr.b-tr.a, tr.c-tr.a));

    // top left of the image (initial evaluation for the barycentric)
    vec3 p = vec3(-1.0f, 1.0f, 0.0f);

    // TODO: compute barycentric coordinates at p. (x = -1, y = 1, the top left corner of image)
    vec3 x = cross(tr.b-tr.a, tr.c-tr.a);
    vec3 bary;
    bary.x = dot((x/length(x)), cross(tr.b-p, tr.c-p))/double_area;
    bary.y = dot((x/length(x)), cross(tr.a-p, tr.b-p))/double_area;
    bary.z = dot((x/length(x)), cross(tr.c-p, tr.a-p))/double_area;

    bary = -bary;

    // TODO: compute barycentric coordinates at p. (x = -1, y = 1, the top left corner of image)
    /*float baryx = -double_triangle_area(triangle(p,tr.b,tr.c)) / double_area; // Area(PBC)/Area(ABC)
    float baryy = -double_triangle_area(triangle(p,tr.c,tr.a)) / double_area; // Area(PCA)/Area(ABC)
    float baryz = -double_triangle_area(triangle(p,tr.a,tr.b)) / double_area; // Area(PAB)/Area(ABC)*/
    //vec3 bary = vec3(baryx, baryy, baryz);

    // TODO: Compute screen-space derivatives of barycentric coordinates
    vec3 dbarydx = vec3((tr.b.y-tr.a.y),(tr.c.y-tr.b.y),(tr.a.y-tr.c.y)) / double_area;
    vec3 dbarydy = vec3(-(tr.b.x-tr.a.x),-(tr.c.x-tr.b.x),-(tr.a.x-tr.c.x)) / double_area;

    // scale the coordinate space of the derivatives to fit the image size
    dbarydx = dbarydx / (width / 2.0f);
    dbarydy = dbarydy / (height / 2.0f);

    for (int y = 0; y < height; y++)
    {
        vec3 row_bary = bary;

        for (int x = 0; x < width; x++)
        {
            // test if all barycentrics are inside the triangle
            if (row_bary.x < 0.0f && row_bary.y < 0.0f && row_bary.z < 0.0f)
            {
                // if the triangle intersected, output the barycentric coordinate as color.
                pixels[y * width + x] = hdr_to_ldr(-row_bary);
            }

            row_bary = row_bary + dbarydx;
        }

        bary = bary - dbarydy;
    }

    // write image to file
    stbi_write_png("rasterize.png", width, height, 4, pixels, width * 4);

#ifdef _WIN32
    // Display the image automatically on Windows
    system("rasterize.png");
#else
    // Display the image automatically on MacOS
    system("xdg-open rasterize.png");
#endif

    delete[] pixels;
}

int main()
{
    // comment out one of these
    //raytrace();
    rasterize();
}
