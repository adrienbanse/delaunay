/*H**********************************************************************
* FILENAME:         config.h  
*
* DESCRIPTION:      Configuration parameters
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

#ifndef __CONFIG_H__
#define __CONFIG_H__

/*******************************************************************
* 
*   EXECUTION PARAMETERS
*
*******************************************************************/
#define N_POINTS                    100
#define UNIFORM                     1
#define EMST                        1
#define VORONOI                     1

#define FINAL_MODE                  1
#define HISTORY_MODE                1  
#define VORONOI_FINAL_MODE          1
#define VORONOI_CIRCLES_MODE        1

#define ERASE_AFTER                 1

/*******************************************************************
* 
*   VISUALIZATION PARAMETERS
*
*******************************************************************/
#define N_SECOND_STEP               0.05
#define N_SECOND_CIRCLE             0.02
#define N_SECOND_PAUSE              10 * N_SECOND_CIRCLE           

#define POINT_WIDTH                 0.009
#define POINT_COLOR                 BLACK_COLOR

#define EDGE_WIDTH                  0.0012
#define EDGE_COLOR                  BLACK_COLOR

#define EMST_EDGE_WIDTH             0.004
#define EMST_EDGE_COLOR             RED_COLOR

#define DUAL_EDGE_WIDTH             0.3 * EDGE_WIDTH
#define DUAL_EDGE_COLOR             RED_COLOR

#define CIRCLES_WIDTH               0.4 * EDGE_WIDTH
#define CIRCLES_COLOR               GREY_COLOR

#define CIRCLES_CENTER_WIDTH        POINT_WIDTH
#define CIRCLES_CENTER_COLOR        RED_COLOR

#define CIRCLES_RESOLUTION          1000

#define TITLE_FINAL_MODE            "Fast Delaunay (result)"
#define TITLE_HISTORY_MODE          "Fast Delaunay (history mode)"
#define TITLE_VORONOI_FINAL_MODE    "Delaunay triangulation and Voronoi graph (result)"
#define TITLE_VORONOI_CIRCLES_MODE  "Delaunay triangulation and Voronoi graph (circles mode)"

#define TEXT_X_POSITION             50
#define TEXT_Y_POSITION             1550
#define TEXT_POSITION               (GLfloat[2]){TEXT_X_POSITION, TEXT_Y_POSITION}

#define DELAUNAY_TXT                (GLubyte[]){"Delaunay (divide and conquer)"}
#define EMST_TXT                    (GLubyte[]){"Euclidian Minimum Spanning Tree (Kruskal)"}
#define CIRC_TXT                    (GLubyte[]){"Computing circum-centers of triangles"}
#define VORONOI_TXT                 (GLubyte[]){"Voronoi (from Delaunay triangulation)"}
#define DONE_TXT                    (GLubyte[]){"Done"}

#define DISAPPEAR_X_POSITION        1130
#define DISAPPEAR_Y_POSITION        1550
#define DISAPPEAR_POSITION          (GLfloat[2]){DISAPPEAR_X_POSITION, DISAPPEAR_Y_POSITION}

#define DISAPPEAR_TXT               (GLubyte[]){"Press up or down arrow keys\nto add/remove triangulation"}

#define INFO_X_POSITION             1130
#define INFO_Y_POSITION             90
#define INFO_POSITION               (GLfloat[2]){INFO_X_POSITION, INFO_Y_POSITION}

/*******************************************************************
* 
*   VORONOI PARAMETERS
*
*******************************************************************/
#define X_MARGIN                    10

/*******************************************************************
* 
*   CONSTANTS
*
*******************************************************************/
#define BLACK_COLOR                 (GLfloat[4]){0.0, 0.0, 0.0, 1.0}
#define RED_COLOR                   (GLfloat[4]){1.0, 0.0, 0.0, 1.0}
#define GREY_COLOR                  (GLfloat[4]){0.0, 0.0, 0.0, 0.5}
#define HISTORY_FILE                "../execution.hst"

#endif