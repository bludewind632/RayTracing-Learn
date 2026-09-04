#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class material 
{
public:
    virtual ~material() =default;
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const { return false; }
};

// diffuse reflection(lambertian reflection) 
class lambertian: public material 
{
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
class metal: public material 
{
public:
    metal(const color& _labedo, double _fuzz): labedo(_labedo), fuzz(_fuzz < 1 ? _fuzz : 1) {}
    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        reflected = unit_vector(reflected) + fuzz * random_unit_vector();
        scattered = ray(rec.p, reflected);
        attenuation = labedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
private:
    color labedo;
    double fuzz;
};

// dielectric material
class dielectric: public material 
{
public:
    dielectric(double refract_idx) : refraction_index(refract_idx) {}
    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        attenuation = color(1.0, 1.0, 1.0);
        double etai_over_etat = rec.front_face ? (1.0 / refraction_index) : refraction_index;
        auto r_in_unit_direction = unit_vector(r_in.direction());
        auto refracted = refract(r_in_unit_direction, rec.normal, etai_over_etat);
        scattered = ray(rec.p, refracted);
        return true;
    }
private:
    double refraction_index;
};
#endif // MATERIAL_H