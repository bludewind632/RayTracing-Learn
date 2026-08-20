#pragma once

#ifndef VEC3_H
#define VEC3_H

#include <cmath>

class vec3
{
    double vc[3];
public:
    vec3() : vc{0, 0, 0} {}
    vec3(double e0, double e1, double e2) : vc{e0, e1,e2} {}
    double& x() { return vc[0]; }
    double& y() { return vc[1]; }
    double& z() { return vc[2]; }

    const double& x() const { return vc[0]; }
    const double& y() const { return vc[1]; }
    const double& z() const { return vc[2]; }

    double& operator[] (int i) { return vc[i]; }
    const double& operator[] (int i) const { return vc[i]; }
    
    vec3 operator- () const { return vec3(-vc[0], -vc[1], -vc[2]); }

    vec3& operator+= (const vec3& other) {
        for (int i = 0; i < 3; i++)
            vc[i] += other[i];
        return *this;
    }

    vec3& operator-= (const vec3& other) {
        for (int i = 0; i < 3; i++)
            vc[i] -= other[i];
        return *this;
    }

    vec3& operator*= (double t) {
        for (int i = 0; i < 3; i++) 
            vc[i] *= t;
        return *this;
    }

    vec3& operator/= (double t) {
        for (int i = 0; i < 3; i++) 
            vc[i] /= t;
        return *this;
    }

    double length() const {
        return std::sqrt(length_square());
    }

    double length_square() const {
        return vc[0] * vc[0] + vc[1] * vc[1] + vc[2] * vc[2];
    }

    friend vec3 operator+ (const vec3& a, const vec3& b);
    friend vec3 operator- (const vec3& a, const vec3& b);
    friend double operator* (const vec3& a, const vec3& b);
    friend vec3 operator* (const vec3& a, double t);
    friend vec3 operator* (double t, const vec3& a);
    friend vec3 operator/ (const vec3& a, double t);
    friend vec3 unit_vector(const vec3& a);
    friend double dot(const vec3& a, const vec3& b);
    friend vec3 cross(const vec3& a, const vec3& b);

};

vec3 operator+ (const vec3& a, const vec3& b) {
    return vec3(a.x() + b.x(), a.y() + b.y(), a.z() + b.z());
}
vec3 operator- (const vec3& a, const vec3& b) {
    return vec3(a.x() - b.x(), a.y() - b.y(), a.z() - b.z());
}
double operator* (const vec3& a, const vec3& b) {
    return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
}
vec3 operator* (const vec3& a, double t) {
    return vec3(a.x() * t, a.y() * t, a.z() * t);
}
vec3 operator* (double t, const vec3& a) {
    return vec3(a.x() * t, a.y() * t, a.z() * t);
}
vec3 operator/ (const vec3& a, double t) {
    return a * (1 / t);
}
vec3 unit_vector(const vec3& a) {
    double t = a.length();
    return a / t;
}
double dot(const vec3& a, const vec3& b) {
    return a * b;
}
vec3 cross(const vec3& a, const vec3& b) {
    double e0 = a.y() * b.z() - b.y() * a.z();
    double e1 = b.x() * a.z() - a.x() * b.z();
    double e2 = a.x() * b.y() - b.x() * a.y();
    return vec3(e0, e1, e2);
}

using point3 = vec3;

#endif // VEC3_H