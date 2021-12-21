/*H**********************************************************************
* FILENAME:         voronoi.h             
*
* DESCRIPTION:      Construction of the Voronoi graph from a Delaunay
*                   triangulation
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

#ifndef __VORONOI_H__

#define __VORONOI_H__

#include "mesh.h"
#include "utils.h"
#include "config.h"

typedef struct graph_t      graph_t;
typedef struct edge_t       edge_t;

/*******************************************************************
*   graph_t
*
*   Structure containing: 
*       - "vertices" the vertices of the graph
*       - "n_vertices" the number of vertices of the graph
*       - "edge_list" the list of edges of the graph
*       - "n_edges" the number of edges of the graph
*******************************************************************/
struct graph_t{
    GLfloat     (*vertices)[2];
    GLsizei     n_vertices;
    edge_t      **edge_list;
    GLsizei     n_edges;
};

/*******************************************************************
*   edge_t
*
*   Structure containing: 
*       - "src" the index of the source vertex of the edge
*       - "dst" the index of the destination vertex of the edge
*   Note: this edge is not directed
*******************************************************************/
struct edge_t{
    int         src, dst;
};

/*******************************************************************
*   voronoi
*
*   Stores in the graph_t structure graph the Voronoi dual graph
*   of the Delaunay triangulation stored in the mesh_t structure
*   mesh 
*******************************************************************/
void    voronoi(                graph_t     *graph, 
                                mesh_t      *mesh);

/*******************************************************************
*   build_triangles
*
*   Constructs the triangles from the half edge list of the trian-
*   gulation stored in mesh
*******************************************************************/
void    build_triangles(        mesh_t      *mesh);

/*******************************************************************
*   look_for_triangles_from
*
*   Looks if there is a triangle beginning from the half-edge e
*   by iterating on its neighbors
*******************************************************************/
void    look_for_triangles_from(mesh_t      *mesh, 
                                half_edge_t *e);

/*******************************************************************
*   add_triangle_to_mesh
*
*   Adds one triangle_t structure whose pointer is triangle in 
*   the triangle list of mesh
*******************************************************************/
void    add_triangle_to_mesh(   mesh_t      *mesh, 
                                triangle_t  *triangle);

/*******************************************************************
*   compute_centers
*
*   Computes the vertices of the graph by computing the circum-
*   centers of the triangles of the mesh
*******************************************************************/
void    compute_centers(        graph_t     *graph, 
                                mesh_t      *mesh);

/*******************************************************************
*   compute_edges
*
*   Computes the edges of the graph either
*       - by connecting two triangles that are neighbors
*       - by adding an infinite edge from a triangle with an edge
*         belonging to the convex hull of the set of points of the
*         mesh
*******************************************************************/
void    compute_edges(          graph_t     *graph, 
                                mesh_t      *mesh);

/*******************************************************************
*   add_edge
*
*   Adds an edge between src and dst vertices in the graph
*******************************************************************/
void    add_edge(               graph_t     *graph, 
                                GLsizei     src, 
                                GLsizei     dst);

/*******************************************************************
*   add_infinite_vertex
*
*   Adds the "infinite" vertex to the graph, that will be linked 
*   the circumcenter of the triangle who has half edge e belonging 
*   to the convex hull of the set of points of the mesh
*******************************************************************/
void    add_infinite_vertex(    graph_t     *graph, 
                                mesh_t      *mesh, 
                                half_edge_t *e);

/*******************************************************************
*   initialize_graph
*
*   Memory function to initialize a graph_t structure and all its
*   attributes
*******************************************************************/
void    initialize_graph(       graph_t *graph);

/*******************************************************************
*   free_graph
*
*   Memory function to free a graph_t structure and all its
*   attributes
*******************************************************************/
void    free_graph(             graph_t *graph);

#endif