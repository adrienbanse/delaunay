#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "inputs.h"
#include "delaunay.h"

#define TEST 0

int main(){

    if (TEST) goto test;

    /* Initialization */
    const int seed = (int) time(NULL);
	srand(seed);
    const int n_points = 30;
	float (*point_list)[2] = malloc(sizeof(point_list[0]) * (n_points + 3));
    if (point_list==NULL) return EXIT_FAILURE;

    float min[2] = {-1, -1};
    float max[2] = {1, 1};
    random_uniform_points(point_list, n_points, min, max);

    const int n_triangles_max = 4 * n_points;
    Triangle* triangle_list = (Triangle*) malloc(n_triangles_max * sizeof(Triangle));
    if (triangle_list == NULL) return EXIT_FAILURE;
    
    int n_triangles;

    /* Triangulation */
    int debug = bowyer_watson(point_list, n_points, triangle_list, &n_triangles);
    if (VERBOSE) printf("Boyer-Watson algorithm was terminated with code : %d\n", debug);
    if (debug != 0) return EXIT_FAILURE;

    free(point_list);
    free(triangle_list);

test:
    if (TEST){
        ; // write here
    }

    return EXIT_SUCCESS;
}