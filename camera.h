#ifndef CAMERA_H_
#define CAMERA_H_

#include "sphere.h"
#include "sphere_list.h"
#include "vec3.h"
#include "weekend.h"

#define ASPECT_RATIO (16.0 / 9.0)
#define IMG_WIDTH 400
#define SAMPLES_PER_PIXEL 100

typedef struct {
    float aspect_ratio;
    int image_width;

    int _image_height;
    float pixel_samples_scale;
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

    cam.pixel_samples_scale = 1.0 / SAMPLES_PER_PIXEL;

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

static inline vec3 sample_square() {
    return (vec3){random_float() - 0.5, random_float() - 0.5, 0};
}

static inline ray get_ray(camera *c, int i, int j) {
    point3 offset = sample_square();
    point3 pixel_sample =
        vec3_add(c->_pixel00_loc,
                 vec3_add(vec3_scale(c->_pixel_delta_u, (i + offset.x)),
                          vec3_scale(c->_pixel_delta_v, (j + offset.y))));
    point3 ray_origin = c->center;

    point3 ray_dir = vec3_subtract(pixel_sample, ray_origin);

    return (ray){ray_origin, ray_dir};
}

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
            colour pixel_colour = (colour){0, 0, 0};
            for (int sample = 0; sample < SAMPLES_PER_PIXEL; sample++) {
                ray r = get_ray(&cam, i, j);
                pixel_colour = vec3_add(pixel_colour, ray_colour(r, &world));
            }
            write_colour(vec3_scale(pixel_colour, cam.pixel_samples_scale));
        }
    }
    fprintf(stderr, "DONE\n");
};

#endif // CAMERA_H_
