#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "inputs.h"
#include "utils.h"
#include "mesh.h"
#include "emst.h"
#include "visualize.h"
#include "delaunay.h"

/* 
TODO :  - verify EMST correctness
        - voronoi ?
        - defensive
*/

#define UNIFORM 1

int main(){
    int seed = (int) time(NULL);
	srand(seed);

    const GLsizei n_points = 25;
	GLfloat (*point_list)[2] = malloc(sizeof(point_list[0]) * n_points);
    if (point_list == NULL)
        error("List of points cannot be malloc'd");

#if UNIFORM
    float min[2] = {-0.8, -0.8};
    float max[2] = {0.8, 0.8};
    random_uniform_points(point_list, n_points, min, max);
#else
    random_points(point_list, n_points);
#endif

    Mesh *d_mesh = (Mesh *)malloc(sizeof(Mesh));
    if (d_mesh == NULL)
        error("Delaunay mesh structure cannot be malloc'd");

    initialize_mesh(d_mesh, point_list, n_points, 2 * n_points);

    delaunay(d_mesh);
    emst(d_mesh);

    visualize_history(d_mesh);
    // visualize_mesh_simple(d_mesh);

    free_mesh(d_mesh);

    exit(EXIT_SUCCESS);
}