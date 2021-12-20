/*H**********************************************************************
* FILENAME:         utils.h  
*
* DESCRIPTION:      Utils
*                   
* NOTES:            /
*
* AUTHORS:          Adrien Banse and Diego de Crombrugghe   
* DATE:             23 December 2021
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
void        error(char msg[]);

/*******************************************************************
*   !!! TODO !!! Not used for the moment
*
*   https://www.geeksforgeeks.org/program-find-circumcenter-triangle-2/
*******************************************************************/
void line_from_points(GLfloat p[2], GLfloat q[2], GLfloat *a, GLfloat *b, GLfloat *c);
void perpendicular_bisector_from_line(GLfloat p[2], GLfloat q[2], GLfloat *a, GLfloat *b, GLfloat *c);
GLfloat* line_line_intersection(GLfloat a1, GLfloat b1, GLfloat c1, GLfloat a2, GLfloat b2, GLfloat c2);
GLfloat*    find_circum_center(GLfloat p[2], GLfloat q[2], GLfloat r[2]);

// TODO


// TODO
void print_square_matrix(GLsizei **matrix, GLsizei n);

#endif