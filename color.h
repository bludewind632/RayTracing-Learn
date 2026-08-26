#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "interval.h"

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color) {
    // Normalization
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    interval intensity(0.000, 0.999);
    int rByte = int(256 * intensity.clamp(r));
    int gByte = int(256 * intensity.clamp(g));
    int bByte = int(256 * intensity.clamp(b));

    out << rByte << " " << gByte << " " << bByte << "\n";
}

#endif // COLOR_H