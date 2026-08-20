#pragma once

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray
{
    point3 orig;
    vec3 dir;
public:
    Ray() =default;
    Ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}
    const point3& origin() const { return orig; }
    const vec3& direction() const { return dir; }
    point3 at(double t) {
        return orig + t * dir;
    }
};
#endif // RAY_H