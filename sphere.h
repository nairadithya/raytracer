#ifndef SPHERE_H_
#define SPHERE_H_

#include "ray.h"
#include "vec3.h"

struct sphere {
    point3 center;
    double radius;
};

struct hit_record {
    point3 p;
    vec3 normal;
    float t;
};

static int hit(sphere *s, const ray r, float ray_tmin, float ray_tmax,
               hit_record rec) {
    vec3 oc = vec3_subtract(s->center, r.orig);
    float a = vec3_len_squared(r.dir);
    float h = vec3_dot(r.dir, oc);
    float c = vec3_len_squared(oc) - s->radius * s->radius;

    float discriminant = h * h - a * c;
    if (discriminant < 0)
        return false;

    float sqrtd = sqrt(discriminant);

    float root = (h - sqrtd) / a;
    if (root <= ray_tmin || ray_tmax <= root) {
        root = (h + sqrtd) / a;
        if (root <= ray_tmin || ray_tmax <= root)
            return false;
    }

    rec.t = root;
    rec.p = ray_at(r, rec.t);
    rec.normal = vec3_div(vec3_subtract(rec.p, s->center), s->radius);

    return true;
}

#endif // SPHERE_H_
