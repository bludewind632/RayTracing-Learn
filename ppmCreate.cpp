#include "vec3.h"
#include "color.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <thread>
#include <chrono>

#define FILENAME "color.ppm"
#define IMG_WIDTH 256
#define IMG_HEIGHT 256

int main() {
    // .ppm: Portable Pixmap
    std::ofstream fout(FILENAME, std::ios::app);
    if (!fout.is_open()) {
        std::cerr << "failed to open the " << FILENAME << std::endl;
    }
    int img_width = IMG_WIDTH;
    int img_height = IMG_HEIGHT;
    // P3: Magic Number->an ASCII-based image format 
    fout << "P3\n" << img_width << " " << img_height << "\n255\n";
    for (int y = 0; y < img_height; y++) {
        // \r Enter
        std::clog << "\rScanlines Remaining: " << std::setw(3) << img_height - y << std::flush;
        for (int x = 0; x < img_width; x++) {
            auto pixel_color = color((double)x / img_width, (double)y / img_height, 0);
            write_color(fout, pixel_color);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    std::clog << "\rDone!                   \n";
    fout.close();
    return 0;
}