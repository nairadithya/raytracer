#ifndef RAY_H_
#define RAY_H_

#include "vec3.h"

typedef struct {
    point3 orig;
    vec3 dir;
} ray;

static inline point3 ray_at(ray r, double t) {
    vec3 scale = (vec3_scale((r.dir), t));
    return vec3_add(r.orig, scale);
}

#endif // RAY_H_
