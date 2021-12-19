/*H**********************************************************************
* FILENAME:         emst.c
*
* DESCRIPTION:      Euclidian Minimum Spanning Tree implementation 
*                   
* NOTES:            Based on Union-Find data structure implementation 
*                   of Kruskal's algorithm applied to Delaunay trian-
*                   gulation's output
*
* AUTHORS:          Adrien Banse and Diego de Crombrugghe   
* DATE:             23 December 2021
* CONTEXT:          LMECA2170 course project at UCLouvain
*                   https://perso.uclouvain.be/vincent.legat/zouLab/meca2170.php
*
*H*/

#include "emst.h"

void make_set(UFNode *node){
    node->parent = node;
    node->size = 1;
}

UFNode* find(UFNode *node){
    if (node->parent == node)
        return node;
    node->parent = find(node->parent);
    return node->parent;
}

void union_find(UFNode *find_u, UFNode *find_v){
    if (find_u->size < find_v->size){
        // swap
        UFNode **tmp = (UFNode **)malloc(sizeof(UFNode*));
        *tmp = find_u;
        find_u = find_v;
        find_v = *tmp;
        free(tmp);
    }
    find_v->parent = find_u;
    find_u->size += find_v->size;
}

void emst(Mesh *mesh){
    mesh->n_deleted = 0;
    compute_edge_lengths(mesh);
    kruskal(mesh);
}

void kruskal(Mesh* mesh){
    UFNode *node_list = (UFNode *)malloc(mesh->n_points * sizeof(UFNode));
    if (node_list == NULL)
        error("Node list in Kruskal algorithm cannot be malloc'd");

    Edge **edge_list_ordered = (Edge **)malloc(mesh->n_edges * sizeof(Edge*));
    if (edge_list_ordered == NULL)
        error("Ordered copy of edge list in Kruskal algorithm cannot be malloc'd");

    memcpy(edge_list_ordered, mesh->edge_list, mesh->n_edges * sizeof(Edge*));
    qsort(edge_list_ordered, mesh->n_edges, sizeof(Edge *), compare_edge_lengths);

    GLsizei i;
    UFNode *u, *v, *find_u, *find_v;
    Edge* e;

    for (i = 0; i < mesh->n_points; i++){
        make_set(&node_list[i]);
    }
    for (i = 0; i < mesh->n_edges; i++){
        e = edge_list_ordered[i];
        u = &node_list[e->src];
        v = &node_list[e->dst];
        find_u = find(u);
        find_v = find(v);
        if (find_u != find_v){
            e->in_tree = 1; // add to the tree
            e->sym->in_tree = 1;
#if HISTORY_MODE
            checkpoint_history(mesh);
#endif
            union_find(find_u, find_v);
        }
    }

    free(node_list);
    free(edge_list_ordered);
}

void compute_edge_lengths(Mesh* mesh){
    Edge *e;
    for (GLsizei i = 0; i < mesh->n_edges; i++){
        e = mesh->edge_list[i];
        GLfloat *src = mesh->points[e->src];
        GLfloat *dst = mesh->points[e->dst];
        e->length = (src[0] - dst[0]) * (src[0] - dst[0]) + (src[1] - dst[1]) * (src[1] - dst[1]);
        e->sym->length = e->length;
    }
}

int compare_edge_lengths(const void *double_edge_pointer_a, const void *double_edge_pointer_b){
    Edge **a = (Edge **) double_edge_pointer_a;
    Edge **b = (Edge **) double_edge_pointer_b;
    GLfloat res = (*a)->length - (*b)->length;
    return (res > 0) - (res < 0);
}
