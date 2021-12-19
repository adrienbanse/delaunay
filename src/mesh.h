#ifndef __MESH_H__
#define __MESH_H__

#include "BOV.h"
#include "utils.h"

typedef struct Mesh Mesh;
typedef struct Edge Edge;

struct Mesh{
    GLfloat (*points)[2];
    GLsizei n_points, n_edges, n_edges_max, n_deleted;
    Edge **edge_list;
};

struct Edge{
    GLsizei src, dst;
    Edge *next; // CCW origin iterator
    Edge *prev; // CW origin iterator
    Edge *sym; 
    int deleted;
    // FOR EMST ONLY
    GLfloat length; 
    int in_tree;
};

// mesh memory and topology
void initialize_mesh(Mesh *mesh, GLfloat points[][2], GLsizei n_points, GLsizei n_edges_max);
void free_mesh(Mesh *mesh);
Edge* make_edge(Mesh* mesh, int src, int dst);
Edge* connect(Mesh* mesh, Edge* a, Edge* b);
void delete_edge(Edge* e);
void splice(Edge* a, Edge* b);
void clean_mesh(Mesh* mesh);

// geometric functions
int right_of(Mesh* mesh, GLsizei p_id, Edge* e);
int left_of(Mesh* mesh, GLsizei p_id, Edge* e);
int in_circle(Mesh *mesh, GLsizei a_id, GLsizei b_id, GLsizei c_id, GLsizei d_id);

#endif