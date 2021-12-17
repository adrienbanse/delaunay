#include "BOV.h"
#include <stdlib.h>
#include "mesh.h"
#include "utils.h"

void delaunay(Mesh* mesh);
void triangulate(Mesh* mesh, GLsizei begin, GLsizei end, Edge** ret);
