/*H**********************************************************************
* FILENAME:         emst.c
*
* DESCRIPTION:      Euclidian Minimum Spanning Tree implementation 
*                   
* NOTES:            Based on Union-Find data structure implementation 
*                   of Kruskal's algorithm applied to Delaunay trian-
*                   gulation's output
*
* AUTHORS:          Adrien Banse <adrien.banse@student.uclouvain.be>
*                   Diego de Crombrugghe <diego.decrombrugghe@student.uclouvain.be>
* 
* DATE:             23 December 2021
*
* CONTEXT:          LMECA2170 course project at UCLouvain
*                   https://perso.uclouvain.be/vincent.legat/zouLab/meca2170.php
*
*H*/

#include "emst.h"

void make_set(uf_node_t *node){
    node->parent = node;
    node->size = 1;
}

uf_node_t* find(uf_node_t *node){
    if (node->parent == node)
        return node;
    node->parent = find(node->parent);
    return node->parent;
}

void union_find(uf_node_t *find_u, uf_node_t *find_v){
    if (find_u->size < find_v->size){
        /* swap */
        uf_node_t **tmp = (uf_node_t **)malloc(sizeof(uf_node_t*));
        *tmp = find_u;
        find_u = find_v;
        find_v = *tmp;
        free(tmp);
    }
    find_v->parent = find_u;
    find_u->size += find_v->size;
}

void emst(mesh_t *mesh){
    mesh->n_deleted = 0;
    compute_edge_lengths(mesh);
    kruskal(mesh);
}

void kruskal(mesh_t* mesh){
    uf_node_t *node_list = (uf_node_t *)malloc(mesh->n_points * sizeof(uf_node_t));
    if (node_list == NULL)
        error("Node list in Kruskal algorithm cannot be malloc'd");

    half_edge_t **edge_list_ordered = (half_edge_t **)malloc(mesh->n_edges * sizeof(half_edge_t*));
    if (edge_list_ordered == NULL)
        error("Ordered copy of edge list in Kruskal algorithm cannot be malloc'd");

    memcpy(edge_list_ordered, mesh->edge_list, mesh->n_edges * sizeof(half_edge_t*));

    /* order edges from minimum weight to maximum weight */
    qsort(edge_list_ordered, mesh->n_edges, sizeof(half_edge_t *), compare_edge_lengths);

    GLsizei i;
    uf_node_t *u, *v, *find_u, *find_v;
    half_edge_t *e;

    /* initialize union-find data structure */
    for (i = 0; i < mesh->n_points; i++){
        make_set(&node_list[i]);
    }

    /* iterating on the edges and add to the three if it does not create a cycle */
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

void compute_edge_lengths(mesh_t* mesh){
    half_edge_t *e;
    for (GLsizei i = 0; i < mesh->n_edges; i++){
        e = mesh->edge_list[i];
        GLfloat *src = mesh->points[e->src];
        GLfloat *dst = mesh->points[e->dst];
        /* /!\ squared length */
        e->length = (src[0] - dst[0]) * (src[0] - dst[0]) + (src[1] - dst[1]) * (src[1] - dst[1]);
        e->sym->length = e->length;
    }
}

int compare_edge_lengths(const void *double_edge_pointer_a, const void *double_edge_pointer_b){
    half_edge_t **a = (half_edge_t **) double_edge_pointer_a;
    half_edge_t **b = (half_edge_t **) double_edge_pointer_b;
    GLfloat res = (*a)->length - (*b)->length;
    return (res > 0) - (res < 0);
}
