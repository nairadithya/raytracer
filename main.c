#include "colour.h"
#include "ray.h"
#include "vec3.h"
#include <stdbool.h>
#include <stdio.h>

int hit_sphere(const point3 center, float radius, const ray r) {
    vec3 oc = vec3_subtract(center, r.orig);
    float a = vec3_dot(r.dir, r.dir);
    float b = -2.0 * vec3_dot(r.dir, oc);
    float c = vec3_dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    return (discriminant >= 0);
}

colour ray_colour(const ray r) {
    vec3 unit_direction = vec3_unit(r.dir);
    float a = 0.5 * (unit_direction.y + 1);
    if (hit_sphere((point3){0, 0, -1}, 0.5, r))
        return (colour){1, 0, 0};
    return vec3_add(vec3_scale((colour){1.0, 1.0, 1.0}, (1.0 - a)),
                    vec3_scale((colour){0.5, 0.9, 1.0}, a));
}

int main() {
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 1024;
    // Image Height Calculation based on Aspect Ratio
    int image_height = (int)(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera stuff
    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width =
        viewport_height * (double)(image_width) / image_height;
    point3 camera_center = (point3){0, 0, 0};

    vec3 viewport_u = (vec3){viewport_width, 0, 0};
    vec3 viewport_v = (vec3){0, -viewport_height, 0};

    vec3 pixel_delta_u = vec3_div(viewport_u, image_width);
    vec3 pixel_delta_v = vec3_div(viewport_v, image_height);

    vec3 viewport_upper_left = vec3_subtract(
					     vec3_subtract(vec3_subtract(camera_center, (vec3){0, 0, focal_length}),
							   vec3_scale(viewport_u, 0.5)),
					     vec3_scale(viewport_v, 0.5));

    vec3 pixel100_loc =
        vec3_add(viewport_upper_left,
                 vec3_scale(vec3_add(pixel_delta_u, pixel_delta_v), 0.5));

    printf("P3\n %d %d\n255\n", image_width, image_height);
    for (int j = 0; j < image_height; j++) {
        fprintf(stderr, "Scanlines Remaining: %d\n", image_height - j);
        for (int i = 0; i < image_width; i++) {
            vec3 pixel_center =
                vec3_add(vec3_add(pixel100_loc, vec3_scale(pixel_delta_u, i)),
                         vec3_scale(pixel_delta_v, j));
            vec3 ray_direction = vec3_subtract(pixel_center, camera_center);
            ray r = (ray){camera_center, ray_direction};
            colour pixel_val = ray_colour(r);
            write_colour(pixel_val);
        }
    }
    fprintf(stderr, "DONE");
}
