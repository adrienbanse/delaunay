#ifndef __VISUALIZE_H__
#define __VISUALIZE_H__

#include "BOV.h"
#include "mesh.h"
#include "utils.h"

#define HISTORY_FILE "../test.hst"

typedef struct History History;
struct History{
    Edge **edge_lists;
    GLsizei *n_edge_list;
    GLsizei length;
};

void initialize_history(History *hst);
void checkpoint_history(Mesh *mesh);
void erase_history();
void read_history(History *hst);
void clean_history(History *hst);

#define N_SECOND 0.2

// visualization
void visualize_mesh_simple(Mesh *mesh);
void visualize_history(Mesh *mesh);

#endif