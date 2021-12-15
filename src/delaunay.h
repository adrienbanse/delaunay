#include "BOV.h"
#include <stdlib.h>
#include "mesh.h"
#include "utils.h"

int delaunay(GLfloat points[][2], GLsizei n_points, Mesh* delaunay_triangulation);
void triangulate(GLfloat points[][2], GLsizei begin, GLsizei n_points, Mesh* mesh, Edge* src, Edge* dst);