#ifndef RTWEEKEND_H
#define RTWEEKEND_H

// macro
#define FILENAME "color.ppm"

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <memory>
#include <numeric>
#include <iomanip>

// Std Usings
using std::shared_ptr;
using std::make_shared;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385; 

// Utility Function
inline double degrees_to_radians(const double& degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
    // get random real in [0,1)
}

inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
    // get random real in [min, max)
}

// Common Headers
#include "vec3.h"
#include "ray.h"
#include "color.h"
#include "interval.h"
#include "camera.h"

#endif // RTWEEKEND_H