#include "delaunay.h"
#include <stdlib.h>

int bowyer_watson(Point2D* point_list, int n_points, Triangle* triangle_list, int* n_triangles){

    /* INITIALIZATION */
    int status = 0;
    int n_triangles_max = 4 * n_points;
    int n_edges_max = 200;

    // dynamic memory allocation for complete and edges
    int* complete = (int*) malloc(n_triangles_max * sizeof(int));
    Edge* edges = (Edge*) malloc(n_edges_max * sizeof(Edge));
    if (complete == NULL){
        status = 1;
        goto skip;
    }
    if (edges == NULL){
        status = 2;
        goto skip;
    }

    double x_c, y_c, r;
    int n_edges, inside;

    /* TRIANGULATION */

    construct_super_triangle(point_list, n_points, triangle_list, n_triangles);
    for (int i=0; i<n_points; i++){
        Point2D p = point_list[i];
        n_edges = 0;
        // Find a triangle with p into it
        for (int j=0; j<*n_triangles; j++){
            if (complete[j]) continue;
            Point2D p1 = point_list[triangle_list[j].p1];
            Point2D p2 = point_list[triangle_list[j].p2];
            Point2D p3 = point_list[triangle_list[j].p3];
            inside = is_in_circum_circle(p, p1, p2, p3, &x_c, &y_c, &r);
            if (x_c < p.x && (p.x-x_c)*(p.x-x_c) > r) complete[j] = 1;
            if (inside){
                // re-allocate memory for edges if needed
                if (n_edges + 3 >= n_edges_max){
                    n_edges_max += 100;
                    edges = realloc(edges, n_edges_max * sizeof(Edge));
                    if (edges == NULL){
                        status = 3;
                        goto skip;
                    }
                }
                // add edges
                edges[n_edges].p1 = triangle_list[j].p1;
                edges[n_edges].p2 = triangle_list[j].p2;
                edges[n_edges + 1].p1 = triangle_list[j].p2;
                edges[n_edges + 1].p2 = triangle_list[j].p3;
                edges[n_edges + 2].p1 = triangle_list[j].p3;
                edges[n_edges + 2].p2 = triangle_list[j].p1;
                n_edges += 3;
                // remove triangle
                triangle_list[j] = triangle_list[*n_triangles - 1];
                complete[j] = complete[*n_triangles - 1];
                (*n_triangles)--;
                j--;
            }
        }

        // TODO
        for (int j=0; j<n_edges - 1; j++){
            for (int k=j+1; k<n_edges; k++){
                if (edges[j].p1 == edges[k].p2 && edges[j].p2 == edges[k].p1){
                    edges[j].p1 = -1;
                    edges[j].p2 = -1;
                    edges[k].p1 = -1;
                    edges[k].p2 = -1;
                }
                if (edges[j].p1 == edges[k].p1 && edges[j].p2 == edges[k].p2){
                    edges[j].p1 = -1;
                    edges[j].p2 = -1;
                    edges[k].p1 = -1;
                    edges[k].p2 = -1;
                }
            }
        }

        // add triangle for each new edge
        for (int j=0; j<n_edges; j++){
            if (edges[j].p1 < 0 || edges[j].p2 < 0) continue;
            if (*n_triangles >= n_triangles_max){
                status = 4;
                goto skip;
            }
            triangle_list[*n_triangles].p1 = edges[j].p1;
            triangle_list[*n_triangles].p2 = edges[j].p2;
            triangle_list[*n_triangles].p3 = i;
            complete[*n_triangles] = 0;
            (*n_triangles)++;
        }

    }

    // remove super-triangle
    for (int i = 0; i<*n_triangles; i++){
        if (triangle_list[i].p1 >= n_points || triangle_list[i].p2 >= n_points || triangle_list[i].p3 >= n_points){
            triangle_list[i] = triangle_list[*n_triangles - 1];
            (*n_triangles)--;
            i--;
        }
    }

skip:
    free(complete);
    free(edges);
    return(status);
}

void construct_super_triangle(Point2D* point_list, int n_points, Triangle* triangle_list, int* n_triangles){
    // Find x_max, x_min, y_max, y_min to construct super-triangle
    double x_min = point_list[0].x;
    double y_min = point_list[0].y;
    double x_max = x_min; 
    double y_max = y_min;
    for (int i=1; i<n_points; i++){
        if (point_list[i].x < x_min) x_min = point_list[i].x;
        if (point_list[i].y < y_min) y_min = point_list[i].y;
        if (point_list[i].x > x_max) x_max = point_list[i].x;
        if (point_list[i].y > y_max) y_max = point_list[i].y;
    }
    // Compute mid points
    double x_mid = (x_max + x_min) / 2.0;
    double y_mid = (y_max + y_min) / 2.0;
    // Compute difference max
    double dx = x_max - x_min;
    double dy = y_max - y_min;
    double d_max = (dx > dy) ? dx : dy;
    // Put at the end of point_list the new points
    point_list[n_points].x = x_mid - MARGIN * d_max;
    point_list[n_points].y = y_mid - d_max;
    point_list[n_points+1].x = x_mid;
    point_list[n_points+1].y = y_mid + MARGIN * d_max;
    point_list[n_points+2].x = x_mid + MARGIN * d_max;
    point_list[n_points+2].y = y_mid - d_max;
    // Fill the first triangle
    triangle_list[0].p1 = n_points;
    triangle_list[0].p2 = n_points + 1;
    triangle_list[0].p3 = n_points + 2;
    *n_triangles = 1;
}

int is_in_circum_circle(Point2D p, Point2D p1, Point2D p2, Point2D p3, double* x_c, double* y_c, double* r_sqrt){
    double d12 = p1.y - p2.y > 0 ? p1.y - p2.y : p2.y - p1.y;
    double d23 = p2.y - p3.y > 0 ? p2.y - p3.y : p3.y - p2.y;
    if (d12 < DBL_EPSILON && d23 < DBL_EPSILON) return 0;
    double m1, m2, mx1, mx2, my1, my2;
    if (d12 < DBL_EPSILON){
        m2 = - (p3.x - p2.x) / (p3.y - p2.y);
        mx2 = (p2.x + p3.x) / 2.0;
        my2 = (p2.y + p3.y) / 2.0;
        *x_c = (p1.x + p2.x) / 2.0;
        *y_c = m2 * (*x_c - mx2) + my2;
    } else if (d23 < DBL_EPSILON){
        m1 = - (p2.x - p1.x) / (p2.y - p1.y);
        mx1 = (p1.x + p2.x) / 2.0;
        my1 = (p1.y + p2.y) / 2.0;
        *x_c = (p2.x + p3.x) / 2.0;
        *y_c = m1 * (*x_c - mx1) + my1;
    } else {
        m1 = - (p2.x - p1.x) / (p2.y - p1.y);
        m2 = - (p3.x - p2.x) / (p3.y - p2.y);
        mx1 = (p1.x + p2.x) / 2.0;
        mx2 = (p2.x + p3.x) / 2.0;
        my1 = (p1.y + p2.y) / 2.0;
        my2 = (p2.y + p3.y) / 2.0;
        *x_c = (m1 * mx1 - m2 * mx2 + my2 - my1) / (m1 - m2);
        if (d12 > d23) {
            *y_c = m1 * (*x_c - mx1) + my1;
        } else {
            *y_c = m2 * (*x_c - mx2) + my2;
        }
    }
    double dx, dy;
    dx = p2.x - *x_c;
    dy = p2.y - *y_c;
    *r_sqrt = dx*dx + dy*dy;
    dx = p.x - *x_c;
    dy = p.y - *y_c;
    double dr_sqrt = dx*dx + dy*dy;
    return (dr_sqrt - *r_sqrt <= DBL_EPSILON ? 1 : 0);
}
