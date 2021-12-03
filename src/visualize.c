#include "visualize.h"
#include "BOV.h"

void draw_final(float point_list[][2], int n_points, Triangle triangle_list[], int n_triangles){
    bov_window_t* window = bov_window_new(800, 800, "Delaunay triangulation");
	bov_window_set_color(window, (float[4]){0.9f, 0.85f, 0.8f, 1.0f});

    int i, j, idx1, idx2, idx3;
    float triangle[3][2];
    bov_points_t *point_list_draw, *triangle_draw;

    while(!bov_window_should_close(window)){
        // draw points
        point_list_draw = bov_points_new(point_list, n_points, GL_STATIC_DRAW);
        bov_points_set_color(point_list_draw, (float[4]) {0.0, 0.0, 0.0, 1.0});
        bov_points_set_width(point_list_draw, 0.002);
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
            bov_points_set_width(triangle_draw, 0.0001);
            bov_line_loop_draw(window, triangle_draw, 0, 3);
            bov_points_delete(triangle_draw);
        }

		bov_window_update(window);
	}
    bov_window_delete(window);
}