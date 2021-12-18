#include "BOV.h"

typedef struct Mesh Mesh;
typedef struct Edge Edge;

struct Mesh{
    GLfloat (*points)[2];
    GLsizei n_points, n_edges, n_edges_max;
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

// memory
void initialize_mesh(Mesh *mesh, GLfloat points[][2], GLsizei n_points, GLsizei n_edges_max);
void free_mesh(Mesh *mesh);

// topological functions
Edge* make_edge(Mesh* mesh, int src, int dst);
Edge* connect(Mesh* mesh, Edge* a, Edge* b);
void delete_edge(Edge* e);
void splice(Edge* a, Edge* b);
void clean_mesh(Mesh* mesh);

// geometric functions
int right_of(Mesh* mesh, GLsizei p_id, Edge* e);
int left_of(Mesh* mesh, GLsizei p_id, Edge* e);
int in_circle(Mesh *mesh, GLsizei a_id, GLsizei b_id, GLsizei c_id, GLsizei d_id);
void compute_edge_lengths(Mesh* mesh);

// EMST
typedef struct UFNode UFNode;
struct UFNode{
    UFNode *parent;
    GLsizei size;
};
int compare_edge_lengths(const void *double_edge_pointer_a, const void *double_edge_pointer_b);
void make_set(UFNode *node);
UFNode* find(UFNode *node);
void union_find(UFNode *find_u, UFNode *find_v);
void kruskal(Mesh* mesh);

// visualization
void visualize_mesh_simple(Mesh *mesh);
