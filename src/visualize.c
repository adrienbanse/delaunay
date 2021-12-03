#include "visualize.h"
#include <math.h>

void draw_inter(float point_list[][2], 
                int n_points, 
                Triangle triangle_list[], 
                int n_triangles, 
                float x_c, 
                float y_c, 
                float r, 
                int smooth){
    bov_window_t* window = initialize_window("Delaunay triangulation");

    int i, j, idx1, idx2, idx3;
    float triangle[3][2];
    bov_points_t *point_list_draw, *triangle_draw, *smooth_circle_list_draw;

    float (*smooth_circle_list)[2] = malloc(sizeof(smooth_circle_list[0]) * smooth);
    smooth_circle(smooth_circle_list, x_c, y_c, r, smooth);

    while(!bov_window_should_close(window)){

        // draw circle
        smooth_circle_list_draw = bov_points_new(smooth_circle_list, smooth, GL_STATIC_DRAW);
        bov_points_set_color(smooth_circle_list_draw, (float[4]) {255.0, 0.0, 0.0, 1.0});
        bov_points_set_width(smooth_circle_list_draw, 0.001);
        bov_line_loop_draw(window, smooth_circle_list_draw, 0, BOV_TILL_END);
        bov_points_delete(smooth_circle_list_draw);  

        // draw points
        point_list_draw = bov_points_new(point_list, n_points, GL_STATIC_DRAW);
        bov_points_set_color(point_list_draw, (float[4]) {0.0, 0.0, 0.0, 1.0});
        bov_points_set_width(point_list_draw, 0.008);
        bov_points_draw(window, point_list_draw, 0, BOV_TILL_END);
        bov_points_delete(point_list_draw);     

        // draw triangles SO FAR
        for(i=0; i<n_triangles; i++){
            for(j=0; j<2; j++){
                triangle[0][j] = point_list[triangle_list[i].p1][j];
                triangle[1][j] = point_list[triangle_list[i].p2][j];
                triangle[2][j] = point_list[triangle_list[i].p3][j];
            }
            triangle_draw = bov_points_new(triangle, 3, GL_STATIC_DRAW);
            bov_points_set_width(triangle_draw, 0.0001);
            bov_line_loop_draw(window, triangle_draw, 0, BOV_TILL_END);
            bov_points_delete(triangle_draw);
        }

		bov_window_update(window);
	}

    free(smooth_circle_list);
    bov_window_delete(window);
}


void draw_final(float point_list[][2], int n_points, Triangle triangle_list[], int n_triangles){
    bov_window_t* window = initialize_window("Delaunay triangulation");

    int i, j, idx1, idx2, idx3;
    float triangle[3][2];
    bov_points_t *point_list_draw, *triangle_draw;

    while(!bov_window_should_close(window)){
        // draw points
        point_list_draw = bov_points_new(point_list, n_points, GL_STATIC_DRAW);
        bov_points_set_color(point_list_draw, (float[4]) {0.0, 0.0, 0.0, 1.0});
        bov_points_set_width(point_list_draw, 0.005);
        bov_points_draw(window, point_list_draw, 0, BOV_TILL_END);
        bov_points_delete(point_list_draw);     

        // draw triangles
        for(i=0; i<n_triangles; i++){
            for(j=0; j<2; j++){
                triangle[0][j] = point_list[triangle_list[i].p1][j];
                triangle[1][j] = point_list[triangle_list[i].p2][j];
                triangle[2][j] = point_list[triangle_list[i].p3][j];
            }
            triangle_draw = bov_points_new(triangle, 3, GL_STATIC_DRAW);
            bov_points_set_width(triangle_draw, 0.0001);
            bov_line_loop_draw(window, triangle_draw, 0, BOV_TILL_END);
            bov_points_delete(triangle_draw);
        }

		bov_window_update(window);
	}
    bov_window_delete(window);
}

bov_window_t* initialize_window(char* title){
    bov_window_t* window = bov_window_new(800, 800, title);
    bov_window_set_zoom(window, 0.5);
	bov_window_set_color(window, (float[4]){0.9f, 0.85f, 0.8f, 1.0f});
    return(window);
}

void smooth_circle(float smooth_circle_list[][2], float x_c, float y_c, float r, int smooth){
    int i;
    float theta;
    for (i=0; i<smooth; i++){
        theta = ((float)i / (float)smooth) * 2 * M_PI;
        smooth_circle_list[i][0] = x_c + sqrtf(r) * cosf(theta);
        smooth_circle_list[i][1] = y_c + sqrtf(r) * sinf(theta);
    }
}
