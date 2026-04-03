#include "colour.h"
#include <stdio.h>

int main() {
    int image_width = 512;
    int image_height = 512;

    printf("P3\n %d %d\n255\n", image_width, image_height);
    for (int j = 0; j < image_width; j++) {
        fprintf(stderr, "Scanlines Remaining: %d\n", image_height - j);
        for (int i = 0; i < image_height; i++) {
            colour pixel_val = (colour){(double)i / (image_width - 1), 0,
                                        (double)j / (image_height - 1)};
            write_colour(&pixel_val);
        }
    }
    fprintf(stderr, "DONE");
}
