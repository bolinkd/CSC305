#ifndef VEC3_H
#define VEC3_H

#include <stdlib.h>
#include <math.h>
#include <iostream>

class vec3
{
public:
    float x,y,z;

    vec3();
    vec3(float _x, float _y, float _z);

    inline float length() const { return sqrt(x*x + y*y + z*z); }
    inline float squared_length() const { return x*x + y*y + z*z; }
    inline void make_unit_vector();

    inline vec3 operator/=(const float f);
    inline vec3 operator+=(const vec3& v1);

};

inline vec3 vec3::operator+=(const vec3& v1){
    this->x += v1.x;
    this->y += v1.y;
    this->z += v1.z;
    return *this;
}

inline vec3 vec3::operator/=(const float f){
    this->x /= f;
    this->y /= f;
    this->z /= f;
    return *this;
}

inline vec3 operator+(const vec3& v1, const vec3& v2) {
    return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline vec3 operator-(const vec3& v1, const vec3& v2) {
    return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline vec3 operator-(const vec3& v1) {
    return vec3(-v1.x, -v1.y, -v1.z);
}

inline vec3 operator*(const vec3& v1, const vec3& v2) {
    return vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

inline vec3 operator/(const vec3& v1, const vec3& v2) {
    return vec3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

inline vec3 operator/(const vec3& v1, const float f) {
    return vec3(v1.x / f, v1.y / f, v1.z / f);
}

inline vec3 operator*(const vec3& v1, const float f) {
    return vec3(f * v1.x, f * v1.y, f * v1.z);
}

inline vec3 operator*(const float f, const vec3& v1) {
    return vec3(f * v1.x, f * v1.y, f * v1.z);
}

inline float dot(const vec3 &v1, const vec3 &v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

inline vec3 cross(const vec3 &v1, const vec3 &v2) {
    return vec3( (v1.y*v2.z - v1.z*v2.y),
                 (-(v1.x*v2.z - v1.z*v2.x)),
                 (v1.x*v2.y - v1.y*v2.x));
}

inline vec3 unit_vector(vec3 v){
    return v / v.length();
}

#endif // VEC3_H
