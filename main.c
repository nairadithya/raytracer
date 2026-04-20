#include "sphere.h"
#include "sphere_list.h"
#include "weekend.h"
#include <math.h>

colour ray_colour(ray r, sphere_list *world) {
    hit_record rec;
    if (sphere_list_hit(world, &r, (interval){0, INFINITY}, &rec)) {
        return vec3_scale(vec3_add(rec.normal, (colour){1, 1, 1}), 0.5);
    }

    vec3 unit_direction = vec3_unit(r.dir);
    float a = 0.5 * (unit_direction.y + 1);
    return vec3_add(vec3_scale((colour){1.0, 1.0, 1.0}, (1.0 - a)),
                    vec3_scale((colour){0.5, 0.9, 1.0}, a));
}

int main() {
    float aspect_ratio = 16.0 / 9.0;
    int image_width = 512;
    // Image Height Calculation based on Aspect Ratio
    int image_height = (int)(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;
    sphere_list world;

    sphere_list_init(&world);
    sphere_list_add(&world, (sphere){(point3){0, 0, -1}, 0.5});
    sphere_list_add(&world, (sphere){(point3){0, -100.5, -1}, 100});

    // Camera stuff
    float focal_length = 1.0;
    float viewport_height = 2.0;
    float viewport_width =
        viewport_height * (float)(image_width) / image_height;
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
            colour pixel_val = ray_colour(r, &world);
            write_colour(pixel_val);
        }
    }
    fprintf(stderr, "DONE\n");
}
