#ifndef __EMST_H__
#define __EMST_H__

#include "BOV.h"
#include "mesh.h"
#include "visualize.h"
#include "utils.h"

typedef struct UFNode UFNode;
struct UFNode{
    UFNode *parent;
    GLsizei size;
};
void make_set(UFNode *node);
UFNode* find(UFNode *node);
void union_find(UFNode *find_u, UFNode *find_v);

void kruskal(Mesh* mesh);
void emst(Mesh *mesh);

void compute_edge_lengths(Mesh* mesh);

int compare_edge_lengths(const void *double_edge_pointer_a, const void *double_edge_pointer_b);

#endif
