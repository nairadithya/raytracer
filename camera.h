#ifndef CAMERA_H_
#define CAMERA_H_

#include "sphere.h"
#include "sphere_list.h"

const float ASPECT_RATIO = 16.0 / 9.0;
const int IMG_WIDTH = 400;

typedef struct {
    float aspect_ratio;
    int image_width;

    int _image_height;
    point3 center;
    point3 _pixel00_loc;
    vec3 _pixel_delta_u;
    vec3 _pixel_delta_v;
} camera;

static inline camera _camera_initialize() {
    camera cam;
    // Camera stuff
    cam.image_width = IMG_WIDTH;
    cam.aspect_ratio = ASPECT_RATIO;
    cam._image_height = (int)(cam.image_width / cam.aspect_ratio);
    cam._image_height = (cam._image_height < 1) ? 1 : cam._image_height;

    float focal_length = 1.0;
    float viewport_height = 2.0;
    float viewport_width =
        viewport_height * (float)(cam.image_width) / cam._image_height;
    cam.center = (point3){0, 0, 0};

    vec3 viewport_u = (vec3){viewport_width, 0, 0};
    vec3 viewport_v = (vec3){0, -viewport_height, 0};

    cam._pixel_delta_u = vec3_div(viewport_u, cam.image_width);
    cam._pixel_delta_v = vec3_div(viewport_v, cam._image_height);

    vec3 viewport_upper_left = vec3_subtract(
        vec3_subtract(vec3_subtract(cam.center, (vec3){0, 0, focal_length}),
                      vec3_scale(viewport_u, 0.5)),
        vec3_scale(viewport_v, 0.5));

    cam._pixel00_loc = vec3_add(
        viewport_upper_left,
        vec3_scale(vec3_add(cam._pixel_delta_u, cam._pixel_delta_v), 0.5));

    return cam;
};

static inline colour ray_colour(ray r, sphere_list *world) {
    hit_record rec;
    if (sphere_list_hit(world, &r, (interval){0, INFINITY}, &rec)) {
        return vec3_scale(vec3_add(rec.normal, (colour){1, 1, 1}), 0.5);
    }

    vec3 unit_direction = vec3_unit(r.dir);
    float a = 0.5 * (unit_direction.y + 1);
    return vec3_add(vec3_scale((colour){1.0, 1.0, 1.0}, (1.0 - a)),
                    vec3_scale((colour){0.5, 0.9, 1.0}, a));
}

void static inline render(sphere_list world) {
    camera cam = _camera_initialize();

    printf("P3\n %d %d\n255\n", cam.image_width, cam._image_height);
    for (int j = 0; j < cam._image_height; j++) {
        fprintf(stderr, "Scanlines Remaining: %d\n", cam._image_height - j);
        for (int i = 0; i < cam.image_width; i++) {
            vec3 pixel_center = vec3_add(
                vec3_add(cam._pixel00_loc, vec3_scale(cam._pixel_delta_u, i)),
                vec3_scale(cam._pixel_delta_v, j));
            vec3 ray_direction = vec3_subtract(pixel_center, cam.center);
            ray r = (ray){cam.center, ray_direction};
            colour pixel_val = ray_colour(r, &world);
            write_colour(pixel_val);
        }
    }
    fprintf(stderr, "DONE\n");
};

#endif // CAMERA_H_
