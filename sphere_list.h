#ifndef SPHERE_LIST_H_
#define SPHERE_LIST_H_

#include "sphere.h"
#include "weekend.h"
#include <stdlib.h>

typedef struct {
    sphere *objects;
    int count;
    int capacity;
} sphere_list;

static void sphere_list_init(sphere_list *list) {
    list->objects = NULL;
    list->count = 0;
    list->capacity = 0;
}

static void sphere_list_add(sphere_list *list, sphere s) {
    if (list->count >= list->capacity) {
        list->capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        list->objects = realloc(list->objects, list->capacity * sizeof(sphere));
    }
    list->objects[list->count++] = s;
}

static void sphere_list_clear(sphere_list *list) {
    free(list->objects);
    list->objects = NULL;
    list->count = 0;
    list->capacity = 0;
}

static int sphere_list_hit(sphere_list *list, ray *r, double tmin, double tmax,
                           hit_record *rec) {
    hit_record temp_rec;
    int hit_anything = 0; // bool
    float closest = tmax;

    for (int i = 0; i < list->count; i++) {
        if (sphere_hit(&list->objects[i], r, tmin, closest, &temp_rec)) {
            hit_anything = 1;
            closest = temp_rec.t;
            *rec = temp_rec;
        }
    }

    return hit_anything;
}

#endif // SPHERE_LIST_H_
