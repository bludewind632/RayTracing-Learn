#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <iostream>
#include <fstream>
#include <cmath>
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

// Common Headers
#include "vec3.h"
#include "ray.h"
#include "color.h"
#include "interval.h"

#endif // RTWEEKEND_H