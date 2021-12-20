/*H**********************************************************************
* FILENAME:         delaunay.h             
*
* DESCRIPTION:      Divide-and-conquer algorithm for Delaunay triangu-
*                   lation. 
*       
* NOTES:            The functions are highly inspired from its Python 
*                   equivalent in 
*                   https://github.com/alexbaryzhikov/triangulation
*
* AUTHORS:          Adrien Banse and Diego de Crombrugghe   
* DATE:             23 December 2021
* CONTEXT:          LMECA2170 course project at UCLouvain
*                   https://perso.uclouvain.be/vincent.legat/zouLab/meca2170.php
*
*H*/

#ifndef __DELAUNAY_H__
#define __DELAUNAY_H__

#include <stdlib.h>
#include "BOV.h"
#include "utils.h"
#include "mesh.h"
#include "visualize.h"
#include "config.h"

/*******************************************************************
*   delaunay
*
*   Computes the Delaunay triangulation for the whole set of points
*   stored in mesh, stores result in mesh
*******************************************************************/
void    delaunay(mesh_t* mesh);

/*******************************************************************
*   triangulate
*
*   Computes the Delaunay triangulation for the set of points 
*   beginning at begin and ending at end, stores result in mesh
*   and stores in ret the CCW convex hull edge out of the leftmost
*   vertex and the CQ convex hull edge out of the rightmost vertex
*******************************************************************/
void    triangulate( mesh_t* mesh, 
                     GLsizei begin, 
                     GLsizei end, 
                     half_edge_t** ret);

/*******************************************************************
*   compare_points
*
*   Comparator function for two points a and b following the tie-
*   breaking rule :
*   a > b if a[0] > b[0] or a[0] == b[0] and a[1] > b[1]
*******************************************************************/
int     compare_points( const void *pointer_a, 
                        const void *pointer_b);

#endif