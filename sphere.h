#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "rtweekend.h"

class sphere : public hittable
{
    point3 center;
    double radius;
public:
    sphere(const point3& c, double r) : center(c), radius(std::fmax(0, r)) {}
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        
        auto oc = center - r.origin();
        double a = r.direction() * r.direction();
        double h = r.direction() * oc;
        double c = oc.length_square() - radius * radius;
        double discriminant = h * h - a * c;
        if (discriminant < 0) return false;
        double sqrtd = std::sqrt(discriminant);
        double root = (h - sqrtd) / a;
        
        if (!ray_t.surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root))
                return false;
        }
        
        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);

        return true;
    }
};
#endif // SPHERE_H


// formula calculation
/**
 * point3 C = (x0, y0, z0); 
 * point3 P = (x, y, z);
 * (P - C) * (P - C) = r * r;
 * ray r ; P(t) = Q + tD;
 * discriminant whether the ray intersect with sphere
 * (tD + Q - C) * (tD + Q - C) = r * r;
 * D*D*t*t + 2D(Q - C)t + (Q - C)*(Q - C) - r * r = 0;
 * discriminant = b * b - 4 * a * c;
 * a = D * D;
 * b = -2D(C - Q);
 * c = (C - Q)*(C - Q) - r * r;
 */
//
/**
 * Simplify the intersection judgement code
 * discriminant = b * b - 4 * a * c;
 * root = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
 * root = (2D(C - Q) - sqrt(4D * D * (C - Q) * (C - Q) - 4 * a * c)) / (2 * a);
 * root = (D(C - Q) - sqrt(D * D * (C - Q) * (C - Q) - a * c)) / a;
 * let h = D(C - Q);
 * root = (h - sqrt(h * h - a * c)) / a;
 */