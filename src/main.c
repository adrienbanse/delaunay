#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "inputs.h"
#include "utils.h"
#include "mesh.h"
#include "emst.h"
#include "visualize.h"
#include "delaunay.h"
#include "voronoi.h"
#include "config.h"

/* 
TODO :  - VORONOI_SPHERE_MODE : free + faire apparaitre voronoi + order in code
        - visu help message --> API
        - clean code
        - comments in code
        - clean main
        - README.md (end) with GIFs
*/

int main(){

    if (N_POINTS < 2)
        error("2 points minimum required");

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
    random_points(point_list, N_POINTS);
#endif

    mesh_t *d_mesh = (mesh_t *)malloc(sizeof(mesh_t));
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

#if VORONOI

    graph_t *v_graph = (graph_t *)malloc(sizeof(graph_t));
    initialize_graph(v_graph);
    voronoi(v_graph, d_mesh);
#if VORONOI_FINAL_MODE
    visualize_mesh_with_dual(d_mesh, v_graph);
#endif
#if VORONOI_CIRCLES_MODE
    visualize_with_circles(v_graph, d_mesh);
#endif
    free_graph(v_graph);

#endif

    free_mesh(d_mesh);
    exit(EXIT_SUCCESS);
}