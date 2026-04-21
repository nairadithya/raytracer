#ifndef COLOUR_H_
#define COLOUR_H_

#include "interval.h"
#include "vec3.h"

typedef vec3 colour;

static inline colour make_colour(float r, float g, float b) {
    return (colour){r, g, b};
}

static inline void write_colour(colour pixel_colour) {
    float r = pixel_colour.x;
    float g = pixel_colour.y;
    float b = pixel_colour.z;

    interval intensity = (interval){0.0, 0.999};

    int rbyte = (int)(255.999 * interval_clamp(intensity, r));
    int gbyte = (int)(255.999 * interval_clamp(intensity, g));
    int bbyte = (int)(255.999 * interval_clamp(intensity, b));

    printf("%d %d %d\n", rbyte, gbyte, bbyte);
}

#endif // COLOUR_H_
