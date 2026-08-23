#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{
    point3 center;
    double radius;
public:
    sphere(const point3& c, double r) : center(c), radius(std::fmax(0, r)) {}
    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
        auto oc = center - r.origin();
        double a = r.direction() * r.direction();
        double h = r.direction() * oc;
        double c = oc.length_square() - radius * radius;
        double discriminant = h * h - a * c;
        if (discriminant < 0) return false;
        double sqrtd = std::sqrt(discriminant);
        double root = (h - sqrtd) / a;
        if (root < ray_tmin && root > ray_tmax) {
            root = (h + sqrtd) / a;
            if (root < ray_tmin && root > ray_tmax)
                return false;
        }
        rec.t = root;
        rec.p = r.at(rec.t);
        rec.normal = (rec.p - center) / radius;
    }
};
#endif // SPHERE_H