#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class material {
public:
    virtual ~material() =default;
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const { return false; }
};

// diffuse reflection(lambertian reflection) 
class lambertian: public material {
public:
    lambertian(const color& clr): labedo(clr) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        vec3 scatter_direction = rec.normal + random_unit_vector();
        if (scatter_direction.near_zero()) scatter_direction = rec.normal;
        scattered = ray(rec.p, scatter_direction);
        attenuation = labedo;
        return true;
    }

private:
    color labedo;
};

// mirror reflection(metal)
class metal: public material {
public:
    metal(const color& clr): labedo(clr) {}
    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        scattered = ray(rec.p, reflected);
        attenuation = labedo;
        return true;
    }
private:
    color labedo;
};

#endif // MATERIAL_H