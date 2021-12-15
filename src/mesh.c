#include "mesh.h"

int initialize_mesh(Mesh* mesh, GLsizei n_edges_max){
    Edge* edge_list = (Edge*)malloc(n_edges_max * sizeof(Edge));
    if (edge_list == NULL){
        free(edge_list);
        return EXIT_FAILURE;
    }
    mesh->n_edges = 0;
    mesh->n_edges_max = n_edges_max;
    mesh->edge_list = edge_list;
    return EXIT_SUCCESS;
}

void make_edge(Mesh* mesh, int src, int dst){
    // check if not too many edges
    if (mesh->n_edges + 2 >= mesh->n_edges_max){
        mesh->n_edges_max += 100;
        mesh->edge_list = realloc(mesh->edge_list, mesh->n_edges_max * sizeof(Edge));
    }

    Edge* e = (Edge *)malloc(sizeof(Edge));
    Edge* s = (Edge *)malloc(sizeof(Edge));
    
    // add edge
    e->src = src;
    e->dst = dst;
    e->sym = s;
    e->next = e;
    e->prev = e;

    s->src = dst;
    s->dst = src;
    s->sym = e;
    s->next = s;
    s->prev = s;

    mesh->edge_list[mesh->n_edges] = *e;
    mesh->n_edges += 1;
}

void splice(Edge* a, Edge* b){
    if (a == b){
        return;
    }
    a->next->prev = b;
    b->next->prev = a;
    a->next = b->next;
    b->next = a->next;
}

int right_of(GLfloat p[2], GLfloat src[2], GLfloat dst[2]){
    return ((src[0]-p[0]) * (dst[1]-p[1]) - (src[1]-p[1]) * (dst[0]-p[0])) > 0;
}

int left_of(GLfloat p[2], GLfloat src[2], GLfloat dst[2]){
    return ((src[0]-p[0]) * (dst[1]-p[1]) - (src[1]-p[1]) * (dst[0]-p[0])) < 0;
}

void connect(Mesh* mesh, Edge a, Edge b){
    make_edge(mesh, a.dst, b.src);
    Edge e = mesh->edge_list[mesh->n_edges - 1];
    splice(&e, a.sym->prev);
    splice(e.sym, &b);
}