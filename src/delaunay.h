#include "visualize.h"

#define MARGIN 20
#define VISUALIZE_FINAL 1
#define VISUALIZE_CIRCLES 0 // TODO
#define VERBOSE 0
#define RANDOM 0 // TODO

/* Bowyer-Watson algorithm, returns a mesh 
 * from a list of points */
int bowyer_watson(float point_list[][2], int n_points, Triangle* triangle_list, int* n_triangles);

// TODO
void construct_super_triangle(float point_list[][2], int n_points, Triangle* triangle_list);

// TODO
int is_in_circum_circle(float p[2], float p1[2], float p2[2], float p3[2], float* x_c, float* y_c, float* r_sqrt);
