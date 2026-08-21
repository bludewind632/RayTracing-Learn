#include "vec3.h"
#include "color.h"
#include "ray.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <thread>
#include <chrono>

#define FILENAME "color.ppm"
// #define IMG_WIDTH 256
// #define IMG_HEIGHT 256

static int hit_cnt = 0;
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
 * b = 2D(Q - C);
 * c = (Q - C)*(Q - C) - r * r;
 */
bool hit_sphere(const ray& r, const point3& center, double radius) {
    double a = r.direction() * r.direction();
    double b = 2 * r.direction() * (r.origin() - center);
    double c = (r.origin() - center) * (r.origin() - center) - radius * radius;
    double discriminant = b * b - 4 * a * c;
    return discriminant >= 0;
}

const color ray_color(ray& r) {
    if (hit_sphere(r, point3(0, 0, -1), 0.2)) {
        hit_cnt++;
        return color(1, 0, 0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    // blend for white and blue
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.3, 0.6, 0.8);
}

int main() {
    // .ppm: Portable Pixmap
    std::ofstream fout(FILENAME, std::ios::out);
    if (!fout.is_open()) {
        std::cerr << "failed to open the " << FILENAME << std::endl;
    }
    
    double aspect_ratio = 16.0 / 9.0;
    int img_width = 400;
    int img_height = int(img_width / aspect_ratio);

    int viewport_height = 2.0;
    int viewport_width = viewport_height * ((double)img_width / img_height);

    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);
    auto viewport_delta_u = viewport_u / img_width;
    auto viewport_delta_v = viewport_v / img_height;

    double focal_length = 1.0;
    auto camera_center = point3(0, 0, 0);
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (viewport_delta_u + viewport_delta_v);

    // P3: Magic Number->an ASCII-based image format 
    fout << "P3\n" << img_width << " " << img_height << "\n255\n";
    for (int y = 0; y < img_height; y++) {
        // \r Enter
        // std::clog << "\rScanlines Remaining: " << std::setw(3) << img_height - y << std::flush;
        for (int x = 0; x < img_width; x++) {
            auto cur_pixel_loc = pixel00_loc + x * viewport_delta_u + y * viewport_delta_v;
            auto cur_direction = cur_pixel_loc - camera_center;
            ray r(camera_center, cur_direction);
            // color pixel_color = color((double)x / img_width, (double)y / img_height, 0);
            color pixel_color = ray_color(r);
            write_color(fout, pixel_color);
        }
        // std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    // std::clog << "\rDone!                   \n";
    fout.close();

    std::cout << hit_cnt << std::endl;
    return 0;
}