#include "camera.h"
#include "sphere.h"
#include "sphere_list.h"
#include "weekend.h"
#include <math.h>

int main() {
    sphere_list world;

    sphere_list_init(&world);
    sphere_list_add(&world, (sphere){(point3){0, 0, -1.0}, 0.55});
    sphere_list_add(&world, (sphere){(point3){0, -100.1, -1.0}, 100});

    render(world);
}
