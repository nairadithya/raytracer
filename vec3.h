#ifndef VEC3_H_
#define VEC3_H_

#include <math.h>
#include <stdio.h>

typedef struct {
    float x, y, z;
} vec3;

static inline vec3 make_vec3(float x, float y, float z) {
    return (vec3){x, y, z};
}

static inline float vec3_len(vec3 a) {
    return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}

static inline float vec3_len_squared(vec3 a) {
    return a.x * a.x + a.y * a.y + a.z * a.z;
}

static inline vec3 vec3_increment(vec3 a) {
    return (vec3){a.x + 1, a.y + 1, a.z + 1};
}

static inline vec3 vec3_decrement(vec3 a) {
    return (vec3){a.x - 1, a.y - 1, a.z - 1};
}

static inline vec3 vec3_add(vec3 a, vec3 b) {
    return (vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

static inline vec3 vec3_subtract(vec3 a, vec3 b) {
    return (vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

static inline vec3 vec3_mult(vec3 a, vec3 b) {
    return (vec3){a.x * b.x, a.y * b.y, a.z * b.z};
}

static inline vec3 vec3_scale(vec3 a, float b) {
    return (vec3){a.x * b, a.y * b, a.z * b};
}

static inline float vec3_dot(vec3 a, vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

static inline vec3 vec3_div(vec3 a, float b) {
    return (vec3){a.x / b, a.y / b, a.z / b};
}

static inline vec3 vec3_unit(vec3 a) { return vec3_div(a, vec3_len(a)); }

static inline void vec3_print(vec3 a) {
    printf("%.4f ", a.x);
    printf("%.4f ", a.y);
    printf("%.4f ", a.z);
}

static inline vec3 vec3_cross(vec3 a, vec3 b) {
    return (vec3){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
                  a.x * b.y - a.y * b.x};
}

typedef vec3 point3;

#endif // VEC3_H_
