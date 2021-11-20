#include "mesh.h"
#include <stdio.h>
#include <stdlib.h>

void is_illegal(Vertex* p_i, Vertex* p_j, Mesh* mesh){
    // TODO
}

Triangle** adjacent_triangles(Vertex* p_i, Vertex* p_j){
    Triangle* first_adjacent_triangle = p_i->root;
    Triangle** res = (Triangle**) malloc(2 * sizeof(Triangle*));
    res[0] = first_adjacent_triangle;

    Triangle* second_adjacent_triangle = p_j->root;
    if (first_adjacent_triangle == second_adjacent_triangle){
        res[1] = second_adjacent_triangle;
        return res;
    }
    
    Triangle** first_adjacent_triangle_nei = (Triangle**) malloc(3 * sizeof(Triangle*));
    first_adjacent_triangle_nei[0] = first_adjacent_triangle->t1;
    first_adjacent_triangle_nei[1] = first_adjacent_triangle->t2;
    first_adjacent_triangle_nei[2] = first_adjacent_triangle->t3;

    for (int k=0; k<3; k++){
        Vertex** v_list = (Vertex**) malloc(3 * sizeof(Vertex*));
        v_list[0] = first_adjacent_triangle_nei[k]->v1;
        v_list[1] = first_adjacent_triangle_nei[k]->v2;
        v_list[2] = first_adjacent_triangle_nei[k]->v3;
        int p_i_in_triangle = 0;
        int p_j_in_triangle = 0;
        for (int l=0; l<3; l++){
            if (v_list[l] == p_i){
                p_i_in_triangle = 1;
            }
            else if (v_list[l] == p_j){
                p_j_in_triangle = 1;
            }
        }
        if (p_i_in_triangle && p_j_in_triangle){
            res[1] = first_adjacent_triangle_nei[k];
            return res;
        }
    }
    return NULL;
}