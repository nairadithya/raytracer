#ifndef SPHERE_H_
#define SPHERE_H_

#include "weekend.h"

typedef struct {
    point3 center;
    double radius;
} sphere;

typedef struct {
    point3 p;
    vec3 normal;
    float t;
    int front_face;
} hit_record;

static void set_face_normal(hit_record *hr, ray r, vec3 outward_normal) {
    hr->front_face = vec3_dot(r.dir, outward_normal) < 0;
    hr->normal =
        hr->front_face ? outward_normal : vec3_scale(outward_normal, -1);
}

static int sphere_hit(sphere *s, ray *r, interval ray_t, hit_record *rec) {
    vec3 oc = vec3_subtract(s->center, r->orig);
    float a = vec3_len_squared(r->dir);
    float h = vec3_dot(r->dir, oc);
    float c = vec3_len_squared(oc) - s->radius * s->radius;

    float discriminant = h * h - a * c;
    if (discriminant < 0)
        return 0;

    float sqrtd = sqrt(discriminant);

    float root = (h - sqrtd) / a;
    if (root <= ray_t.min || ray_t.min <= root) {
        root = (h + sqrtd) / a;
        if (root <= ray_t.min || ray_t.max <= root)
            return 0;
    }

    rec->t = root;
    rec->p = ray_at(r, rec->t);
    vec3 outward_normal = vec3_div(vec3_subtract(rec->p, s->center), s->radius);
    set_face_normal(rec, *r, outward_normal);
    rec->normal = vec3_div(vec3_subtract(rec->p, s->center), s->radius);

    return 1;
}

#endif // SPHERE_H_
