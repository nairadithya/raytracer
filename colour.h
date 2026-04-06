#ifndef COLOUR_H_
#define COLOUR_H_

#include "vec3.h"

typedef vec3 colour;

static inline colour make_colour(float r, float g, float b) {
    return (colour){r, g, b};
}

static inline void write_colour(colour pixel_colour) {
    float r = pixel_colour.x;
    float g = pixel_colour.y;
    float b = pixel_colour.z;

    int rbyte = (int)(255.999 * r);
    int gbyte = (int)(255.999 * g);
    int bbyte = (int)(255.999 * b);

    printf("%d %d %d\n", rbyte, gbyte, bbyte);
}

#endif // COLOUR_H_
