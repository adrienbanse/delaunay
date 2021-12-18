#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "inputs.h"
#include "delaunay.h"

#define EMST 1
#define VISUALIZE 0
#define UNIFORM 1

int main(){
    int seed = (int) time(NULL);
	srand(seed);

    const GLsizei n_points = 10;
	GLfloat (*point_list)[2] = malloc(sizeof(point_list[0]) * n_points);

#if UNIFORM
    float min[2] = {-0.8, -0.8};
    float max[2] = {0.8, 0.8};
    random_uniform_points(point_list, n_points, min, max);
#else
    random_points(point_list, n_points);
#endif

    Mesh *d_mesh = (Mesh *)malloc(sizeof(Mesh));
    initialize_mesh(d_mesh, point_list, n_points, 2 * n_points);
    delaunay(d_mesh);

#if EMST
    emst(d_mesh);
#endif

#if VISUALIZE 
    visualize_mesh_simple(d_mesh);
#endif

    free_mesh(d_mesh);

    return EXIT_SUCCESS;
}
