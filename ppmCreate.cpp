#include "rtweekend.h"

#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

#define FILENAME "color.ppm"
// #define IMG_WIDTH 256
// #define IMG_HEIGHT 256

// Shading with surface normals
const color ray_color(ray& r, hittable& world) {
    auto camera_center = point3(0, 0, -1);
    hit_record rec;
    if (world.hit(r, interval(0, infinity), rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
        std::cout << 1 << "\n";
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
    
    // Image
    double aspect_ratio = 16.0 / 9.0;
    int img_width = 400;
    int img_height = int(img_width / aspect_ratio);

    // Viewport
    double viewport_height = 2.0;
    double viewport_width = viewport_height * ((double)img_width / img_height);

    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);
    auto viewport_delta_u = viewport_u / img_width;
    auto viewport_delta_v = viewport_v / img_height;

    // Hittable_list
    hittable_list world;
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    // world.add(make_shared<sphere>(point3(0,-100.5,-1), 1000));

    // Camera
    double focal_length = 1.0;
    auto camera_center = point3(0, 0, 0);
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (viewport_delta_u + viewport_delta_v);

    // P3: Magic Number->an ASCII-based image format 
    fout << "P3\n" << img_width << " " << img_height << "\n255\n";
    for (int y = 0; y < img_height; y++) {
        // \r Enter
        std::clog << "\rScanlines Remaining: " << std::setw(3) << img_height - y << std::flush;
        for (int x = 0; x < img_width; x++) {
            auto cur_pixel_loc = pixel00_loc + x * viewport_delta_u + y * viewport_delta_v;
            auto cur_direction = cur_pixel_loc - camera_center;
            ray r(camera_center, cur_direction);
            // color pixel_color = color((double)x / img_width, (double)y / img_height, 0);
            color pixel_color = ray_color(r, world);
            write_color(fout, pixel_color);
        }
        // std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    std::clog << "\rDone!                   \n";
    fout.close();
    return 0;
}