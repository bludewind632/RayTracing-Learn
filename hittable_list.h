#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include "rtweekend.h"
#include <vector>

/**
 * The function of shared_ptr:
 * allows multiple geometries to share a common instance
 */

class hittable_list : public hittable
{
public:
    std::vector<shared_ptr<hittable>> objects;
    
    hittable_list() =default;
    hittable_list(const shared_ptr<hittable>& object) {
        add(object);
    }
    ~hittable_list() { objects.clear(); }
    
    void add(const shared_ptr<hittable>& object) {
        objects.push_back(object);
    }

    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const {
        hit_record tmp_rec;
        bool hit_anything = true;
        double closest_so_far = ray_tmax;
        for (auto& object : objects) {
            if (hit(r, ray_tmin, closest_so_far, tmp_rec)) {
                hit_anything = true;
                closest_so_far = tmp_rec.t;
                rec = tmp_rec;
            }
        }
        return hit_anything;
    }
};
// polymorphic behavior

#endif // HITTABLE_LIST_H