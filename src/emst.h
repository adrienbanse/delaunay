/*H**********************************************************************
* FILENAME:         emst.h  
*
* DESCRIPTION:      Euclidian Minimum Spanning Tree implementation 
*                   
* NOTES:            Based on Union-Find data structure implementation 
*                   of Kruskal's algorithm applied to Delaunay trian-
*                   gulation's output
*
* AUTHORS:          Adrien Banse <adrien.banse@student.uclouvain.be>
*                   Diego de Crombrugghe <diego.decrombrugghe@student.uclouvain.be>
*
* DATE:             23 December 2021
*
* CONTEXT:          LMECA2170 course project at UCLouvain
*                   https://perso.uclouvain.be/vincent.legat/zouLab/meca2170.php
*
*H*/

#ifndef __EMST_H__
#define __EMST_H__

#include "BOV.h"
#include "mesh.h"
#include "visualize.h"
#include "utils.h"
#include "config.h"

typedef struct uf_node_t    uf_node_t;

/*******************************************************************
*   uf_node_t
*
*   Structure containing: 
*       - "parent" pointer to the parent node
*       - "size" number of descendants
*******************************************************************/
struct uf_node_t{
    uf_node_t   *parent;
    GLsizei     size;
};

/*******************************************************************
*   make_set
*
*   Adds a new node to the Union Find data structure
*******************************************************************/
void        make_set(               uf_node_t   *node);

/*******************************************************************
*   find
*
*   Iterates on the parent pointers from UFNode whose pointer is
*   node until it reaches a root element, returns it
*******************************************************************/
uf_node_t*  find(                   uf_node_t   *node);

/*******************************************************************
*   union_find
*
*   Replaces the set containing u whose root has pointer find_u 
*   and the set containing v whose root is has pointer find_v with 
*   their union
*   Note: this assumes that find_u != find_v in the first place
*******************************************************************/
void        union_find(             uf_node_t   *find_u, 
                                    uf_node_t   *find_v);

/*******************************************************************
*   kruskal
*
*   Kruskal's algorithm applied to Delaunay triangulation output
*   mesh
*******************************************************************/
void        kruskal(                mesh_t      *mesh);

/*******************************************************************
*   emst
*
*   Computes the Euclidian Minimum Spanning Tree
*******************************************************************/
void        emst(                   mesh_t      *mesh);

/*******************************************************************
*   compute_edge_lengths
*
*   For each edge, computes the (squared) euclidian distance between   
*   source and destination points
*******************************************************************/
void        compute_edge_lengths(   mesh_t      *mesh);

/*******************************************************************
*   compare_edge_lengths
*
*   Comparator function for two edges a and b following the tie-
*   breaking rule :
*   a > b if (length of a) > (length of b)
*******************************************************************/
int         compare_edge_lengths(   const void  *double_edge_pointer_a, 
                                    const void  *double_edge_pointer_b);

#endif
