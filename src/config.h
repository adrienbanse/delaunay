/*H**********************************************************************
* FILENAME:         config.h  
*
* DESCRIPTION:      Configuration parameters
*                   
* NOTES:            /
*
* AUTHORS:          Adrien Banse and Diego de Crombrugghe   
* DATE:             23 December 2021
* CONTEXT:          LMECA2170 course project at UCLouvain
*                   https://perso.uclouvain.be/vincent.legat/zouLab/meca2170.php
*
*H*/

#ifndef __CONFIG_H__
#define __CONFIG_H__

// execution config
#define N_POINTS                    100
#define UNIFORM                     1
#define EMST                        0
#define VORONOI                     1

#define HISTORY_MODE                0
#define FINAL_MODE                  0
#define VORONOI_FINAL_MODE          0
#define VORONOI_CIRCLES_MODE        1

#define ERASE_AFTER                 1

// visualization config
#define N_SECOND_STEP               0.05
#define N_SECOND_CIRCLE             0.05
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

#define TITLE_FINAL_MODE            "Fast Delaunay (result)"
#define TITLE_HISTORY_MODE          "Fast Delaunay (history mode)"
#define TITLE_VORONOI_FINAL_MODE    "Delaunay triangulation and Voronoi graph (result)"
#define TITLE_VORONOI_CIRCLES_MODE  "Delaunay triangulation and Voronoi graph (circles mode)"

#define TEXT_X_POSITION             -0.8
#define TEXT_Y_POSITION             0.9
#define TEXT_POSITION               (GLfloat[2]){TEXT_X_POSITION, TEXT_Y_POSITION}

#define DELAUNAY_TXT                (GLubyte[]){"Delaunay (divide and conquer)"}
#define EMST_TXT                    (GLubyte[]){"Euclidian Minimum Spanning Tree (Kruskal)"}
#define DONE_TXT                    (GLubyte[]){"Done"}

#define CIRCLES_RESOLUTION          1000

// voronoi
#define X_MARGIN                    10

// constants
#define BLACK_COLOR                 (GLfloat[4]){0.0, 0.0, 0.0, 1.0}
#define RED_COLOR                   (GLfloat[4]){1.0, 0.0, 0.0, 1.0}
#define GREY_COLOR                  (GLfloat[4]){0.0, 0.0, 0.0, 0.5}
#define HISTORY_FILE                "../execution.hst"


#endif