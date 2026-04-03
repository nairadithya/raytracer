#ifndef COLOUR_H_
#define COLOUR_H_

#include "stdio.h"
#include "vec3.h"

typedef vec3 colour;

static inline void write_colour(colour *pixel_colour) {
    double r = pixel_colour->x;
    double g = pixel_colour->y;
    double b = pixel_colour->z;

    int rbyte = (int)(255.999 * r);
    int gbyte = (int)(255.999 * g);
    int bbyte = (int)(255.999 * b);

    printf("%d %d %d\n", rbyte, gbyte, bbyte);
}

#endif // COLOUR_H_
