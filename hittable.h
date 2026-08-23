#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class hit_record
{
public:
    point3 p; // intersection point
    vec3 normal; // unit_normal_vector
    double t;
};

class hittable
{
public:
    virtual ~hittable() =default;
    virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
};

#endif //HITTABLE_H