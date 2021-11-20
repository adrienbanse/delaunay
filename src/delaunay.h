#include "mesh.h"

#define DBL_EPSILON 2.2204460492503131e-16
#define MARGIN 20

/* Bowyer-Watson algorithm, returns a mesh 
 * from a list of points */
int bowyer_watson(Point2D* point_list, int n_points, Triangle* triangle_list, int* n_triangles);

// TODO
void construct_super_triangle(Point2D* point_list, int n_points, Triangle* triangle_list, int* n_triangles);

int is_in_circum_circle(Point2D p, Point2D p1, Point2D p2, Point2D p3, double* x_c, double* y_c, double* r_sqrt);
