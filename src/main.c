#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "inputs.h"
#include "delaunay.h"

int main(){
    int status = EXIT_SUCCESS;
    int i;

    int seed = (int) time(NULL);
	srand(seed);

    const GLsizei n_points = 3;
	GLfloat (*point_list)[2] = malloc(sizeof(point_list[0]) * n_points);
    random_points(point_list, n_points);

    Mesh* mesh = (Mesh *)malloc(sizeof(Mesh));
    if (mesh == NULL){
        status = EXIT_FAILURE;
        goto free;
    }

    if (initialize_mesh(mesh, 100) != EXIT_SUCCESS){
        status = EXIT_FAILURE;
        goto free;
    }

    delaunay(point_list, n_points, mesh);

free:
    free(mesh);
    return status;
}