#include "BOV.h"
#include <stdlib.h>
#include "mesh.h"

void delaunay(Mesh* mesh);
void triangulate(Mesh* mesh, GLsizei begin, GLsizei end, Edge** ret);
void emst(Mesh *mesh);
void kruskal(Mesh* mesh);
int compare_points(const void *pointer_a, const void *pointer_b);
