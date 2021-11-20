#include "mesh.h"

/* Bowyer-Watson algorithm, returns a mesh 
 * from a list of points */
Mesh* bowyer_watson(Point** point_list, int size);

/* Modify mesh potential illegal edge (p_i, p_j)
 * after inserting p_r into mesh */
void legalize_edge(Vertex* p_r, Vertex* p_i, Vertex* p_j, Mesh* mesh);