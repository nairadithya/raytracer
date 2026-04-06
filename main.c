#include "colour.h"
#include "ray.h"
#include <stdio.h>

colour ray_colour(const ray r) { return make_colour(0.0, 0.0, 0.0); }

int main() {
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 512;
    // Image Height Calculation based on Aspect Ratio
    int image_height = (int)image_width / aspect_ratio;
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

    vec3 viewport_upper_left =
        vec3_subtract(camera_center, (vec3){0, 0, focal_length});

    vec3 pixel100_loc =
        vec3_add(viewport_upper_left,
                 vec3_scale(vec3_add(pixel_delta_u, pixel_delta_v), 0.5));

    printf("P3\n %d %d\n255\n", image_width, image_height);
    for (int j = 0; j < image_width; j++) {
        fprintf(stderr, "Scanlines Remaining: %d\n", image_height - j);
        for (int i = 0; i < image_height; i++) {
            colour pixel_val = (colour){(double)i / (image_width - 1), 0,
                                        (double)j / (image_height - 1)};
            write_colour(pixel_val);
        }
    }
    fprintf(stderr, "DONE");
}
