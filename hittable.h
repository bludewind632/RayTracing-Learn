#ifndef HITTABLE_H
#define HITTABLE_H

#include "rtweekend.h"

class hit_record
{
public:
    point3 p; // intersection point
    vec3 normal; // unit_normal_vector
    double t;
    bool front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0.0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable
{
public:
    virtual ~hittable() =default;
    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif //HITTABLE_H