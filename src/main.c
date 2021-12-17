#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "inputs.h"
#include "delaunay.h"

#define VISUALIZE 0

int main(){
    int seed = (int) time(NULL);
	srand(seed);

    const GLsizei n_points = 300;
	GLfloat (*point_list)[2] = malloc(sizeof(point_list[0]) * n_points);
    float min[2] = {-0.8, -0.8};
    float max[2] = {0.8, 0.8};
    random_uniform_points(point_list, n_points, min, max);

    Mesh *mesh = (Mesh *)malloc(sizeof(Mesh));
    initialize_mesh(mesh, point_list, n_points, 2 * n_points);
    delaunay(mesh);

#if VISUALIZE
    visualize_mesh(mesh, point_list, n_points); // leaks in here
#endif

    free_mesh(mesh);
    free(point_list);
    return EXIT_SUCCESS;
}
