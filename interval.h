#ifndef INTERVAL_H_
#define INTERVAL_H_

#include "weekend.h"

typedef struct {
    float min;
    float max;
} interval;

static interval interval_init(float min, float max) {
    return (interval){min = +INFINITY, max = -INFINITY};
};

static float interval_size(interval *i) { return i->max - i->min; }

static int interval_contains(interval *i, float x) {
    return i->min <= x && x <= i->max;
}

static int interval_surrounds(interval *i, float x) {
    return i->min < x && x < i->max;
}

#endif // INTERVAL_H_
