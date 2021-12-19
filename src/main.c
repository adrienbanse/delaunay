#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "inputs.h"
#include "utils.h"
#include "mesh.h"
#include "emst.h"
#include "visualize.h"
#include "delaunay.h"
#include "config.h"

/* 
TODO :  - voronoi ?
        - comments in code
*/

int main(){
    int seed = (int) time(NULL);
	srand(seed);

	GLfloat (*point_list)[2] = malloc(sizeof(point_list[0]) * N_POINTS);
    if (point_list == NULL)
        error("List of points cannot be malloc'd");

#if UNIFORM
    float min[2] = {-0.8, -0.8};
    float max[2] = {0.8, 0.8};
    random_uniform_points(point_list, N_POINTS, min, max);
#else
    random_points(point_list, n_points);
#endif

    Mesh *d_mesh = (Mesh *)malloc(sizeof(Mesh));
    if (d_mesh == NULL)
        error("Delaunay mesh structure cannot be malloc'd");

    initialize_mesh(d_mesh, point_list, N_POINTS, 2 * N_POINTS);
    delaunay(d_mesh);

#if EMST
    emst(d_mesh);
#endif

#if HISTORY_MODE
    visualize_history(d_mesh);
#endif

#if FINAL_MODE
    visualize_mesh_simple(d_mesh);
#endif

    free_mesh(d_mesh);
    exit(EXIT_SUCCESS);
}