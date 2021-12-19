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
#define N_POINTS            200
#define EMST                1
#define UNIFORM             1
#define HISTORY_MODE        1
#define FINAL_MODE          0
#define HISTORY_FILE        "../execution.hst"
#define ERASE_AFTER         1

// visualization config
#define N_SECOND            0.05
#define EDGE_WIDTH          0.0012
#define EDGE_COLOR          BLACK_COLOR
#define EMST_EDGE_WIDTH     0.004
#define EMST_EDGE_COLOR     RED_COLOR
#define POINT_WIDTH         0.009
#define POINT_COLOR         BLACK_COLOR
#define TEXT_X_POSITION     -0.8
#define TEXT_Y_POSITION     0.9
#define TEXT_POSITION       (GLfloat[2]){TEXT_X_POSITION, TEXT_Y_POSITION}
#define TITLE_FINAL_MODE    "Fast Delaunay (result)"
#define TITLE_HISTORY_MODE  "Fast Delaunay (history mode)"
#define DELAUNAY_TXT        (GLubyte[]){"Delaunay (divide and conquer)"}
#define EMST_TXT            (GLubyte[]){"Euclidian Minimum Spanning Tree (Kruskal)"}
#define DONE_TXT            (GLubyte[]){"Done"}

// constants
#define BLACK_COLOR         (GLfloat[4]){0.0, 0.0, 0.0, 1.0}
#define RED_COLOR           (GLfloat[4]){1.0, 0.0, 0.0, 1.0}

#endif