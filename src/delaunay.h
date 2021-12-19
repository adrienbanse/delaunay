#ifndef __DELAUNAY_H__
#define __DELAUNAY_H__

#include <stdlib.h>
#include "BOV.h"
#include "utils.h"
#include "mesh.h"
#include "visualize.h"


void delaunay(Mesh* mesh);
void triangulate(Mesh* mesh, GLsizei begin, GLsizei end, Edge** ret);

int compare_points(const void *pointer_a, const void *pointer_b);

#endif