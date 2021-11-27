#include "delaunay.h"
#include <stdlib.h>
#include <stdio.h>
#include <float.h>

int bowyer_watson(float point_list[][2], int n_points, Triangle* triangle_list, int* n_triangles){

    /* INITIALIZATION */
    int n_triangles_max = 4 * n_points;
    int n_edges_max = 200;

    int* complete = (int*) malloc(n_triangles_max * sizeof(int));
    if (complete == NULL){
        free(complete);
        return(1);
    }

    Edge* edges = (Edge*) malloc(n_edges_max * sizeof(Edge));
    if (edges == NULL){
        free(complete);
        free(edges);
        return(1);
    }
    
    float x_c, y_c, r;
    int n_edges, inside, i, j, k;

    /* TRIANGULATION */
    construct_super_triangle(point_list, n_points, triangle_list);
    *n_triangles = 1;
    complete[0] = 0;

    for (i=0; i<n_points; i++){
        float* p = point_list[i];
        n_edges = 0;
        // find a triangle with p into it
        for (j=0; j<*n_triangles; j++){
            if (complete[j]) continue;
            float* p1 = point_list[triangle_list[j].p1];
            float* p2 = point_list[triangle_list[j].p2];
            float* p3 = point_list[triangle_list[j].p3];
            inside = is_in_circum_circle(p, p1, p2, p3, &x_c, &y_c, &r);

            if (x_c < p[0] && (p[0]-x_c)*(p[0]-x_c) > r) complete[j] = 1;
            if (inside){
                // re-allocate memory for edges if needed
                if (n_edges + 3 >= n_edges_max){
                    n_edges_max += 100;
                    edges = realloc(edges, n_edges_max * sizeof(Edge));
                    if (edges == NULL){
                        free(complete);
                        free(edges);
                        return(2);
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

        // in case edges are equal
        for (j=0; j<n_edges - 1; j++){
            for (k=j+1; k<n_edges; k++){
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
        for (j=0; j<n_edges; j++){
            if (edges[j].p1 < 0 || edges[j].p2 < 0) continue;
            if (*n_triangles >= n_triangles_max){
                free(complete);
                free(edges);
                return(3);
            }
            triangle_list[*n_triangles].p1 = edges[j].p1;
            triangle_list[*n_triangles].p2 = edges[j].p2;
            triangle_list[*n_triangles].p3 = i;
            complete[*n_triangles] = 0;
            (*n_triangles)++;
        }
    }

    // remove super-triangle
    for (i = 0; i<*n_triangles; i++){
        if (triangle_list[i].p1 >= n_points || triangle_list[i].p2 >= n_points || triangle_list[i].p3 >= n_points){
            triangle_list[i] = triangle_list[*n_triangles - 1];
            (*n_triangles)--;
            i--;
        }
    }

    free(complete);
    free(edges);
    return(0);
}

void construct_super_triangle(float point_list[][2], int n_points, Triangle* triangle_list){
    int i;

    // Find x_max, x_min, y_max, y_min to construct super-triangle
    float x_min = point_list[0][0];
    float y_min = point_list[0][1];
    float x_max = x_min; 
    float y_max = y_min;
    for (i=1; i<n_points; i++){
        if (point_list[i][0] < x_min) x_min = point_list[i][0];
        if (point_list[i][1] < y_min) y_min = point_list[i][1];
        if (point_list[i][0] > x_max) x_max = point_list[i][0];
        if (point_list[i][1] > y_max) y_max = point_list[i][1];
    }
    // Compute mid points
    float x_mid = (x_max + x_min) / 2.;
    float y_mid = (y_max + y_min) / 2.;
    // Compute difference max
    float dx = x_max - x_min;
    float dy = y_max - y_min;
    float d_max = (dx > dy) ? dx : dy;
    // Put at the end of point_list the new points
    point_list[n_points][0] = x_mid - MARGIN * d_max;
    point_list[n_points][1] = y_mid - d_max;
    point_list[n_points + 1][0] = x_mid;
    point_list[n_points + 1][1] = y_mid + MARGIN * d_max;
    point_list[n_points + 2][0] = x_mid + MARGIN * d_max;
    point_list[n_points + 2][1] = y_mid - d_max;
    // Fill the first triangle
    triangle_list[0].p1 = n_points;
    triangle_list[0].p2 = n_points + 1;
    triangle_list[0].p3 = n_points + 2;
}

int is_in_circum_circle(float p[2], float p1[2], float p2[2], float p3[2], float* x_c, float* y_c, float* r_sqrt){
    float d12 = p1[1] - p2[1] > 0 ? p1[1] - p2[1] : p2[1] - p1[1];
    float d23 = p2[1] - p3[1] > 0 ? p2[1] - p3[1] : p3[1] - p2[1];
    if (d12 < FLT_EPSILON && d23 < FLT_EPSILON) return 0;
    float m1, m2, mx1, mx2, my1, my2;
    if (d12 < FLT_EPSILON){
        m2 = - (p3[0] - p2[0]) / (p3[1] - p2[1]);
        mx2 = (p2[0] + p3[0]) / 2.;
        my2 = (p2[1] + p3[1]) / 2.;
        *x_c = (p1[0] + p2[0]) / 2.;
        *y_c = m2 * (*x_c - mx2) + my2;
    } else if (d23 < FLT_EPSILON){
        m1 = - (p2[0] - p1[0]) / (p2[1] - p1[1]);
        mx1 = (p1[0] + p2[0]) / 2.;
        my1 = (p1[1] + p2[1]) / 2.;
        *x_c = (p2[0] + p3[0]) / 2.;
        *y_c = m1 * (*x_c - mx1) + my1;
    } else {
        m1 = - (p2[0] - p1[0]) / (p2[1] - p1[1]);
        m2 = - (p3[0] - p2[0]) / (p3[1] - p2[1]);
        mx1 = (p1[0] + p2[0]) / 2.;
        mx2 = (p2[0] + p3[0]) / 2.;
        my1 = (p1[1] + p2[1]) / 2.;
        my2 = (p2[1] + p3[1]) / 2.;
        *x_c = (m1 * mx1 - m2 * mx2 + my2 - my1) / (m1 - m2);
        if (d12 > d23) {
            *y_c = m1 * (*x_c - mx1) + my1;
        } else {
            *y_c = m2 * (*x_c - mx2) + my2;
        }
    }
    float dx, dy;
    dx = p2[0] - *x_c;
    dy = p2[1] - *y_c;
    *r_sqrt = dx*dx + dy*dy;
    dx = p[0] - *x_c;
    dy = p[1] - *y_c;
    float dr_sqrt = dx*dx + dy*dy;

    return (dr_sqrt - *r_sqrt <= FLT_EPSILON ? 1 : 0);
}
