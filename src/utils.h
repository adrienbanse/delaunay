/*H**********************************************************************
* FILENAME:         utils.h  
*
* DESCRIPTION:      Utils
*                   
* NOTES:            /
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

#ifndef __UTILS_H__
#define __UTILS_H__

#include "BOV.h"

#define RED     "\e[0;31m"
#define NC      "\e[0m"

/*******************************************************************
*   error
*
*   Prints on stderr an error with specified message msg and 
*   exits program with status EXIT_FAILURE
*******************************************************************/
void        error(                              char        msg[]);

/*******************************************************************
*   line_from_points
*
*   Stores in a, b and c the values such that the line passing 
*   by points p and q have equation ax + by = c
*   Note: this code was inspired from
*   https://www.geeksforgeeks.org/program-find-circumcenter-triangle-2/
*******************************************************************/
void        line_from_points(                   GLfloat     p[2], 
                                                GLfloat     q[2], 
                                                GLfloat     *a, 
                                                GLfloat     *b, 
                                                GLfloat     *c);

/*******************************************************************
*   perpendicular_bisector_from_line
*
*   Stores in a, b and c the values such that the line perpendicular 
*   to the segment pq passing by the center of pq have equation 
*   ax + by = c
*   Note: this code was inspired from
*   https://www.geeksforgeeks.org/program-find-circumcenter-triangle-2/
*******************************************************************/
void        perpendicular_bisector_from_line(   GLfloat     p[2], 
                                                GLfloat     q[2], 
                                                GLfloat     *a, 
                                                GLfloat     *b, 
                                                GLfloat     *c);

/*******************************************************************
*   line_line_intersection
*
*   Returns the intersection point between the lines that have 
*   equations a1x + b1y = c1 and a2x + b2y = c2
*   Note: this code was inspired from
*   https://www.geeksforgeeks.org/program-find-circumcenter-triangle-2/
*******************************************************************/
GLfloat*    line_line_intersection(             GLfloat     a1, 
                                                GLfloat     b1, 
                                                GLfloat     c1, 
                                                GLfloat     a2, 
                                                GLfloat     b2, 
                                                GLfloat     c2);

/*******************************************************************
*   find_circum_center
*
*   Returns the circumcenter of the circle circumscribed to 
*   triangle pqr
*   Note: this code was inspired from
*   https://www.geeksforgeeks.org/program-find-circumcenter-triangle-2/
*******************************************************************/
GLfloat*    find_circum_center(                 GLfloat     p[2], 
                                                GLfloat     q[2], 
                                                GLfloat     r[2]);

#endif