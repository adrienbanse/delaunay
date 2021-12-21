/*H**********************************************************************

* FILENAME:         mesh.c       
*
* DESCRIPTION:      File containing implementation of methods associated
*                   to meshes, i.e. memory, topological, and geometrical
*                   functions
*                   
* NOTES:            Imlpementations are inspired from their Python
*                   equivalent in
*                   https://github.com/alexbaryzhikov/triangulation
*
* AUTHORS:          Adrien Banse and Diego de Crombrugghe   
* DATE:             23 December 2021
* CONTEXT:          LMECA2170 course project at UCLouvain
*                   https://perso.uclouvain.be/vincent.legat/zouLab/meca2170.php
*
*H*/

#include "mesh.h"

void initialize_mesh(mesh_t *mesh, GLfloat points[][2], GLsizei n_points, GLsizei n_edges_max){
    half_edge_t **edge_list = (half_edge_t **)malloc(n_edges_max * sizeof(half_edge_t *));
    if (edge_list == NULL)
        error("Delaunay mesh cannot be initialized");
    mesh->points = points;
    mesh->n_points = n_points;
    mesh->n_edges = 0;
    mesh->n_edges_max = n_edges_max;
    mesh->n_deleted = 0;
    mesh->edge_list = edge_list;
    mesh->triangle_list = NULL;
    mesh->n_triangles = 0;
}

void free_mesh(mesh_t *mesh){
    GLsizei i;
    half_edge_t **edge_list = mesh->edge_list;
    for (i = 0; i < mesh->n_edges; i++){
        free(edge_list[i]->sym);
        free(edge_list[i]);
    }
    free(edge_list);
    triangle_t **triangle_list = mesh->triangle_list;
    if (triangle_list != NULL){
        for (i = 0; i < mesh->n_triangles; i++)
            free(triangle_list[i]);
        free(triangle_list);
    }
    free(mesh->points);
    free(mesh);
}

half_edge_t* make_edge(mesh_t *mesh, int src, int dst){
    /* re-alloc if needed */
    if (mesh->n_edges + 2 >= mesh->n_edges_max){
        mesh->n_edges_max += 100;
        mesh->edge_list = (half_edge_t **)realloc(mesh->edge_list, mesh->n_edges_max * sizeof(half_edge_t *));
    } 
    half_edge_t *e = (half_edge_t *)malloc(sizeof(half_edge_t));
    half_edge_t *s = (half_edge_t *)malloc(sizeof(half_edge_t));
    
    e->src = src;
    e->dst = dst;
    e->sym = s;
    e->next = e;
    e->prev = e;
    e->deleted = 0;
    e->in_tree = 0;
    e->visited = 0;
    e->t = NULL;

    s->src = dst;
    s->dst = src;
    s->sym = e;
    s->next = s;
    s->prev = s;
    s->deleted = 0;
    s->in_tree = 0;
    s->visited = 0;
    s->t = NULL;

    mesh->edge_list[mesh->n_edges] = e;
    (mesh->n_edges)++;

    return e;
}

half_edge_t* connect(mesh_t *mesh, half_edge_t *a, half_edge_t *b){
    half_edge_t *e = make_edge(mesh, a->dst, b->src);
    splice(e, a->sym->prev);
    splice(e->sym, b);
    return e;
}

void delete_edge(half_edge_t *e){
    splice(e, e->prev);
    splice(e->sym, e->sym->prev);
    e->deleted = 1;
    e->sym->deleted = 1;
}

void splice(half_edge_t *a, half_edge_t *b){
    if (a == b){
        return;
    }
    a->next->prev = b;
    b->next->prev = a;

    /* swap here */
    half_edge_t **tmp = (half_edge_t **)malloc(sizeof(half_edge_t *));
    *tmp = a->next;
    a->next = b->next;
    b->next = *tmp;
    
    free(tmp);
}

void clean_mesh(mesh_t* mesh){
    for (GLsizei i = 0; i < mesh->n_edges; i++)
        if (mesh->edge_list[i]->deleted){
            half_edge_t *to_delete = mesh->edge_list[i];
            mesh->edge_list[i] = mesh->edge_list[mesh->n_edges - 1];
            free(to_delete->sym);
            free(to_delete);
            (mesh->n_edges)--;
            i--;
        }
}


int right_of(mesh_t* mesh, GLsizei p_id, half_edge_t* e){
    GLfloat *p = mesh->points[p_id];
    GLfloat *src = mesh->points[e->src];
    GLfloat *dst = mesh->points[e->dst];
    GLfloat det = (src[0] - p[0]) * (dst[1] - p[1]) - (src[1] - p[1]) * (dst[0] - p[0]);
    return det > 0;
}

int left_of(mesh_t *mesh, GLsizei p_id, half_edge_t *e){
    GLfloat *p = mesh->points[p_id];
    GLfloat *src = mesh->points[e->src];
    GLfloat *dst = mesh->points[e->dst];
    GLfloat det = (src[0] - p[0]) * (dst[1] - p[1]) - (src[1] - p[1]) * (dst[0] - p[0]);
    return det < 0;
}

int in_circle(mesh_t *mesh, GLsizei a_id, GLsizei b_id, GLsizei c_id, GLsizei d_id){
    GLfloat *a = mesh->points[a_id];
    GLfloat *b = mesh->points[b_id];
    GLfloat *c = mesh->points[c_id];
    GLfloat *d = mesh->points[d_id];
    GLfloat a1 = a[0] - d[0];
    GLfloat a2 = a[1] - d[1];
    GLfloat b1 = b[0] - d[0];
    GLfloat b2 = b[1] - d[1];
    GLfloat c1 = c[0] - d[0];
    GLfloat c2 = c[1] - d[1];
    GLfloat a3 = a1 * a1 + a2 * a2;
    GLfloat b3 = b1 * b1 + b2 * b2;
    GLfloat c3 = c1 * c1 + c2 * c2;
    GLfloat det = a1 * b2 * c3 + a2 * b3 * c1 + a3 * b1 * c2 - (a3 * b2 * c1 + a1 * b3 * c2 + a2 * b1 * c3);
    return det < 0;
}

