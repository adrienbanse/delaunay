#include "mesh.h"
#include "BOV.h"

// TODO
void draw_inter(float point_list[][2], 
                int n_points, 
                Triangle triangle_list[], 
                int n_triangles, 
                float x_c, 
                float y_c, 
                float r, 
                int smooth);

// TODO
void draw_final(float point_list[][2], int n_points, Triangle triangle_list[], int n_triangles);

// TODO
bov_window_t* initialize_window(char* title);

// TODO
void smooth_circle(float smooth_circle_list[][2], float x_c, float y_c, float r, int smooth);