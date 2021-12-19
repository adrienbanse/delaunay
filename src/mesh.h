/*H**********************************************************************
* FILENAME:         mesh.h  
*
* DESCRIPTION:      File containing Mesh data structures and methods
*                   associated, i.e. memory, topological, and geometri-
*                   cal functions
*                   
* NOTES:            Edge data structure, topological functions and 
*                   geometrical functions are inspired from their 
*                   Python equivalent in
*                   https://github.com/alexbaryzhikov/triangulation
*
* AUTHORS:          Adrien Banse and Diego de Crombrugghe   
* DATE:             23 December 2021
* CONTEXT:          LMECA2170 course project at UCLouvain
*                   https://perso.uclouvain.be/vincent.legat/zouLab/meca2170.php
*
*H*/

#ifndef __MESH_H__
#define __MESH_H__

#include "BOV.h"
#include "utils.h"
#include "config.h"

typedef struct Mesh Mesh;
typedef struct Edge Edge;

/*******************************************************************
*   Mesh
*
*   Structure containing: 
*       - "points" set of points
*       - "n_points" number of points
*       - "n_edges" number of edges
*       - "n_edges_max" maximal number of edges, if needed this
*         will be incremented
*       - "n_deleted" number of deleted edges
*       - "edge_list" list of pointers to the edges of the mesh
*******************************************************************/
struct Mesh{
    GLfloat (*points)[2];
    GLsizei n_points;
    GLsizei n_edges;
    GLsizei n_edges_max;
    GLsizei n_deleted;
    Edge    **edge_list;
};

/*******************************************************************
*   Edge
*
*   Structure containing: 
*       - "src" the index of the source point of the edge
*       - "dst" the index of the destination point of the edge
*       - "next" pointer to the next edge with same origin in the
*         counter-clockwise orientation
*       - "prev" pointer to the next edge with same origin in the  
*         clockwise orientation (i.e. previous edge in the counter-
*         clockwise orientation)
*       - "sym" pointer to the twin edge
*       - "deleted" boolean, set to 1 if edge was deleted
*       - "length" (squared) euclidian distance between source and
*         destination points (only changed if EMST is 1, see 
*         config.h)
*       - "in_tree" boolean, set to 1 if edge is in EMST (only
*         changed if EMST is 1, see config.h)
*******************************************************************/
struct Edge{
    GLsizei src;
    GLsizei dst;
    Edge    *next; /* CCW origin iterator */
    Edge    *prev; /* CW origin iterator */
    Edge    *sym; 
    int     deleted;
    /* EMST attributes */
    GLfloat length; 
    int     in_tree;
};

/*******************************************************************
*   initialize_mesh
*
*   Intitializes the Mesh structure mesh
*******************************************************************/
void    initialize_mesh( Mesh *mesh, 
                         GLfloat points[][2], 
                         GLsizei n_points, 
                         GLsizei n_edges_max);

/*******************************************************************
*   free_mesh
*
*   Free Mesh structure mesh and all its attributes
*******************************************************************/
void    free_mesh(Mesh *mesh);

/*******************************************************************
*   make_edge
*
*   Add to mesh edge between src and dst
*******************************************************************/
Edge*   make_edge(Mesh* mesh, int src, int dst);

/*******************************************************************
*   connect
*
*   Connects destination of a to the origin of b
*******************************************************************/
Edge*   connect(Mesh* mesh, Edge* a, Edge* b);

/*******************************************************************
*   delete_edge
*
*   Deletes edge e
*******************************************************************/
void    delete_edge(Edge* e);

/*******************************************************************
*   splice
*
*   Breaks the same edge ring in two pieces
*   Note: Explained in depth in 
*   https://graphics.stanford.edu/courses/cs348a-09-fall/Handouts/handout31.pdf
*******************************************************************/
void    splice(Edge* a, Edge* b);

/*******************************************************************
*   clean_mesh
*
*   Removes from edge list of mesh all edges that were deleted and
*   free them
*******************************************************************/
void    clean_mesh(Mesh* mesh);

/*******************************************************************
*   right_of
*
*   Returns 1 if point with index p_id is at the right of the edge 
*   e, 0 otherwise
*******************************************************************/
int     right_of(Mesh* mesh, GLsizei p_id, Edge* e);

/*******************************************************************
*   left_of
*
*   Returns 1 if point with index p_id is at the left of the edge 
*   e, 0 otherwise
*******************************************************************/
int     left_of(Mesh* mesh, GLsizei p_id, Edge* e);

/*******************************************************************
*   in_circle
*
*   Returns 1 if point with index d_id is in the circumscribed 
*   circle of the triangle whose vertices are points with indices
*   a_id, b_id and c_id, 0 otherwise
*******************************************************************/
int     in_circle( Mesh *mesh, 
                   GLsizei a_id, 
                   GLsizei b_id, 
                   GLsizei c_id, 
                   GLsizei d_id);

#endif