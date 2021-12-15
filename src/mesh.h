#include "BOV.h"

typedef struct Edge Edge;
typedef struct Mesh Mesh;

struct Mesh{
    Edge* edge_list;
    GLsizei n_edges, n_edges_max;
};

struct Edge{
   int src;
   int dst;
   Edge* next;
   Edge* prev;
   Edge* sym;
};

int initialize_mesh(Mesh* mesh, GLsizei n_edges_max);
void make_edge(Mesh* mesh, int src, int dst);
void splice(Edge* a, Edge* b);
int right_of(GLfloat p[2], GLfloat src[2], GLfloat dst[2]);
int left_of(GLfloat p[2], GLfloat src[2], GLfloat dst[2]);
void connect(Mesh* mesh, Edge a, Edge b);
