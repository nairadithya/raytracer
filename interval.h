#ifndef INTERVAL_H_
#define INTERVAL_H_

#include "math.h"

typedef struct {
    float min;
    float max;
} interval;

static inline interval create_interval(float min, float max) {
    return (interval){min, max};
}

float static inline interval_size(interval i) { return i.max - i.min; }

int static inline interval_contains(interval i, float x) {
    return i.max >= x && i.min <= x;
}

int static inline interval_surrounds(interval i, float x) {
    return i.max > x && i.min < x;
}

static inline interval interval_empty(void) {
    return (interval){+INFINITY, -INFINITY};
}
static inline interval interval_universe(void) {
    return (interval){-INFINITY, +INFINITY};
}

static inline float interval_clamp(interval i, float x) {
    if (x < i.min)
        return i.min;
    if (x > i.max)
        return i.max;
    return x;
}

#endif // INTERVAL_H_
