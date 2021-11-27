#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "inputs.h"
#include "delaunay.h"

int main(){
    /* Initialization */
    const int seed = (int) time(NULL);
	srand(seed);
    const int n_points = 10;
	float (*point_list)[2] = malloc(sizeof(point_list[0]) * n_points);
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
    printf("Boyer-Watson algorithm was terminated with code : %d\n", debug);
    if (debug != 0) return EXIT_FAILURE;
    printf("Number of triangles : %d\n", n_triangles);

    /* Visualization */
    bov_window_t* window = bov_window_new(800, 800, "Delaunay triangulation");
	bov_window_set_color(window, (float[4]){0.9f, 0.85f, 0.8f, 1.0f});

    int i, j, idx1, idx2, idx3;
    float triangle[3][2];
    bov_points_t *point_list_draw, *triangle_draw;

    while(!bov_window_should_close(window)){
        // draw points
        point_list_draw = bov_points_new(point_list, n_points, GL_STATIC_DRAW);
        bov_points_set_color(point_list_draw, (float[4]) {0.0, 0.0, 0.0, 1.0});
        bov_points_set_width(point_list_draw, 0.02);
        bov_points_draw(window, point_list_draw, 0, n_points);
        bov_points_delete(point_list_draw);     

        // draw triangle lines
        for(i=0; i<n_triangles; i++){
            for(j=0; j<2; j++){
                triangle[0][j] = point_list[triangle_list[i].p1][j];
                triangle[1][j] = point_list[triangle_list[i].p2][j];
                triangle[2][j] = point_list[triangle_list[i].p3][j];
            }
            triangle_draw = bov_points_new(triangle, 3, GL_STATIC_DRAW);
            bov_points_set_width(triangle_draw, 0.001);
            bov_line_loop_draw(window, triangle_draw, 0, 3);
            bov_points_delete(triangle_draw);
        }

		bov_window_update(window);
	}

    free(point_list);
    free(triangle_list);

	bov_window_delete(window);
    return EXIT_SUCCESS;
}