#ifndef WEEKEND_H_
#define WEEKEND_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const float infinity = INFINITY;
const float pi = 3.1415926535897932385;

static inline float degrees_to_radians(float degrees) {
    return degrees * pi / 180.0;
}

#include "colour.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif // WEEKEND_H_
