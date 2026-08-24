#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"
#include "hittable.h"

class camera 
{
public:
    double aspect_ratio = 16.0 / 9.0;
    double img_width = 400;

    void render(const hittable& world) {
        initialize();

        std::ofstream fout(FILENAME, std::ios::out);
        if (!fout.is_open()) {
            std::cerr << "failed to open the " << FILENAME << std::endl;
        }
        fout << "P3\n" << img_width << " " << img_height << "\n255\n";
        for (int y = 0; y < img_height; y++) {
            // \r Enter
            std::clog << "\rScanlines Remaining: " << std::setw(3) << img_height - y << std::flush;
            for (int x = 0; x < img_width; x++) {
                auto cur_pixel_loc = pixel00_loc + x * pixel_delta_u + y * pixel_delta_v;
                auto cur_direction = cur_pixel_loc - center;
                ray r(center, cur_direction);
                // color pixel_color = color((double)x / img_width, (double)y / img_height, 0);
                color pixel_color = ray_color(r, world);
                write_color(fout, pixel_color);
            }
            // std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        std::clog << "\rDone!                   \n";
        fout.close();
    }

private:
    double img_height;
    point3 center;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    point3 pixel00_loc;
    point3 viewport_upper_left;

    void initialize() {
        img_height = int(img_width / aspect_ratio);

        center = point3(0, 0, 0);
        double focal_length = 1.0;

        double viewport_height = 2.0;
        double viewport_width = viewport_height * ((double)img_width / img_height);
        
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);
        
        pixel_delta_u = viewport_u / img_width;
        pixel_delta_v = viewport_v / img_height;

        viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    color ray_color(const ray& r, const hittable& world) const {
        hit_record rec;
        if (world.hit(r, interval(0, infinity), rec)) {
            return 0.5 * (rec.normal + color(1, 1, 1));
        }
        vec3 unit_direction = unit_vector(r.direction());
        double a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1, 1, 1) + a * color(0.3, 0.6, 0.8);
    }
};
#endif // CAMERA_H