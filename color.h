#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"


using color = vec3;

void write_color(std::ostream& out, const color& pixel_color) {
    // Normalization
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    int rByte = int(255.999 * r);
    int gByte = int(255.999 * g);
    int bByte = int(255.999 * b);

    out << rByte << " " << gByte << " " << bByte << "\n";
}

#endif // COLOR_H