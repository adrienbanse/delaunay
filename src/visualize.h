/*H**********************************************************************
* FILENAME:         visualize.h             
*
* DESCRIPTION:      Delaunay triangulation and EMST visualization 
*                   library based on BOV library
*       
* NOTES:            /
*
* AUTHORS:          Adrien Banse and Diego de Crombrugghe   
* DATE:             23 December 2021
* CONTEXT:          LMECA2170 course project at UCLouvain
*                   https://perso.uclouvain.be/vincent.legat/zouLab/meca2170.php
*
*H*/

#ifndef __VISUALIZE_H__
#define __VISUALIZE_H__

#include "BOV.h"
#include "utils.h"
#include "mesh.h"
#include "voronoi.h"
#include "config.h"
#include "inputs.h"

typedef struct history_t    history_t;
typedef struct circle_t     circle_t;

struct circle_t{
    GLfloat (*circle)[2];
};

/*******************************************************************
*   History
*
*   Structure containing: 
*       - "edge_lists" list of edge list, each edge list corresponds 
*         to the edge list of at a checkpoint
*       - "n_edge_list" list of number of edge, each number of edge 
*         corresponds to the number of edges at a checkpoint
*       - "length" length is the number of checkpoints
*******************************************************************/
struct history_t{
    half_edge_t     **edge_lists;
    GLsizei         *n_edge_list;
    GLsizei         length;
};

/*******************************************************************
*   initialize_history
*
*   Intitializes the History structure hst
*******************************************************************/
void    initialize_history(history_t *hst);

/*******************************************************************
*   checkpoint_history
*
*   Stores the the number of edges and the edge list
*   when called in .hst file HISTORY_FILE (see config.h)
*   Note: data is appended to the end of the file
*******************************************************************/
void    checkpoint_history(mesh_t *mesh);

/*******************************************************************
*   erase_history
*
*   Erases data in .hst file HISTORY_FILE (see config.h)
*******************************************************************/
void    erase_history();

/*******************************************************************
*   read_history
*
*   Transfers data from .hst file HISTORY_FILE (see config.h) to 
*   History structure hst
*******************************************************************/
void    read_history(history_t *hst);

/*******************************************************************
*   clean_history
*
*   Free History structure hst and all its attributes, erase 
*   HISTORY_FILE content if ERASE_AFTER is set to 1 (see config.h)
*******************************************************************/
void    clean_history(history_t *hst);

/*******************************************************************
*   visualize_mesh_simple
*
*   Function for visualizing a simple Mesh structure mesh
*   Typically used to visualize the output of the Delaunay
*   triangulation algorithm
*   Note: based on BOV library
*******************************************************************/
void    visualize_mesh_simple(mesh_t *mesh);

/*******************************************************************
*   visualize_history
*
*   Functions for visualizing the whole execution of the Delaunay
*   triangulation algorithm
*   Note: based on BOV library
*******************************************************************/
void    visualize_history(mesh_t *mesh);

void    visualize_mesh_with_dual(mesh_t *mesh, graph_t *graph);

void visualize_with_circles(graph_t *graph, mesh_t *mesh);
void smooth_circle(GLfloat (*circle)[2], GLfloat center_x, GLfloat center_y, GLfloat radius);

#endif