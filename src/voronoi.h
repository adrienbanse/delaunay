#ifndef __VORONOI_H__
#define __VORONOI_H__

#include "mesh.h"
#include "utils.h"
#include "config.h"

typedef struct graph_t      graph_t;
typedef struct edge_t       edge_t;

struct graph_t{
    GLfloat     (*vertices)[2];
    GLsizei     n_vertices;
    edge_t      **edge_list;
    GLsizei     n_edges;
};

struct edge_t{
    int         src, dst;
};

void voronoi(graph_t *graph, mesh_t *mesh);
void build_triangles(mesh_t *mesh);
void look_for_triangles_from(mesh_t *mesh, half_edge_t *e);
void add_triangle_to_mesh(mesh_t *mesh, triangle_t *triangle);
void compute_centers(graph_t *graph, mesh_t *mesh);
void compute_edges(graph_t *graph, mesh_t *mesh);
void add_edge(graph_t *graph, GLsizei src, GLsizei dst);
void add_infinite_vertex(graph_t *graph, mesh_t *mesh, half_edge_t *e);
void initialize_graph(graph_t *graph);
void free_graph(graph_t *graph);

#endif