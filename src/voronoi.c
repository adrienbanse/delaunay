/*H**********************************************************************
* FILENAME:         voronoi.c            
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

#include "voronoi.h"

void initialize_graph(graph_t *graph){
    graph->n_vertices = 0;
    graph->n_edges = 0;
}

void free_graph(graph_t *graph){
    GLsizei i;
    edge_t **edge_list = graph->edge_list;
    for (i = 0; i < graph->n_edges; i++){
        free(edge_list[i]);
    }
    free(edge_list);
    free(graph->vertices);
    free(graph);
}

void voronoi(graph_t *graph, mesh_t *mesh){
    build_triangles(mesh);
    compute_centers(graph, mesh);
    compute_edges(graph, mesh);
}

void build_triangles(mesh_t *mesh){
    /* for each edge, we check if there is a triangle beginning from e or e->sym */
    for (GLsizei i = 0; i < mesh->n_edges; i++){
        look_for_triangles_from(mesh, mesh->edge_list[i]);
        look_for_triangles_from(mesh, mesh->edge_list[i]->sym);
    }
}

void look_for_triangles_from(mesh_t *mesh, half_edge_t *e){
    GLsizei i, count = 1;
    triangle_t *triangle = (triangle_t*)malloc(sizeof(triangle_t)); 
    if (triangle == NULL)
        error("Triangle cannot be malloc'd");

    if (e->visited){ /* if edge is already visited */
        free(triangle);
        return;
    }

    half_edge_t *curr = e;

    /* construct the candidate triangle */
    triangle->vertices[0] = curr->src;
    triangle->e[0] = curr;

    do{
        /* iteration rule */
        curr = curr->sym->next;
        /*  stop if we encounter an edge already visited
            or we have reached the border                 */
        if (curr->visited || count == 3){ 
            free(triangle);
            return;
        }
        count++;
        triangle->vertices[count - 1] = curr->src;
        triangle->e[count - 1] = curr;
    } while(curr->dst != e->src); /* we have found the triangle */

    add_triangle_to_mesh(mesh, triangle);
}

void add_triangle_to_mesh(mesh_t *mesh, triangle_t *triangle){
    /* mark the edges to be visited + link the triangles to edges */
    for (GLsizei i = 0; i < 3; i++){
        triangle->e[i]->visited = 1;
        triangle->e[i]->t = triangle;
    }
    triangle->idx = mesh->n_triangles;

    /* then add the triangle to mesh */
    (mesh->n_triangles)++;
    if (mesh->n_triangles == 1){
        mesh->triangle_list = (triangle_t **)malloc(sizeof(triangle_t *));
        if (mesh->triangle_list == NULL)
            error("Triangle list cannot be malloc'd");
    }
    if (mesh->n_triangles > 1){
        mesh->triangle_list = realloc(mesh->triangle_list, mesh->n_triangles * sizeof(triangle_t *));
        if (mesh->triangle_list == NULL)
            error("Memory re-allocation failed for triangles list");
    }
    mesh->triangle_list[mesh->n_triangles - 1] = triangle;
}

void compute_centers(graph_t *graph, mesh_t *mesh){
    GLfloat *center, *v1, *v2, *v3;
    triangle_t *triangle;

    for (GLsizei i = 0; i < mesh->n_triangles; i++){
        triangle = mesh->triangle_list[i];
        v1 = mesh->points[triangle->vertices[0]];
        v2 = mesh->points[triangle->vertices[1]];
        v3 = mesh->points[triangle->vertices[2]];
        center = find_circum_center(v1, v2, v3);
        (graph->n_vertices)++;
        /* re-alloc for each new vertex (not optimal) */
        if (graph->n_vertices == 1){
            graph->vertices = malloc(sizeof(graph->vertices[0]));
            if (graph->vertices == NULL)
                error("Vertices of graph cannot be malloc'd");
        }
        else{
            graph->vertices = realloc(graph->vertices, graph->n_vertices * sizeof(graph->vertices[0]));
            if (graph->vertices == NULL)
                error("Impossible to re-allocate memory for vertices of the graph");
        }
        graph->vertices[graph->n_vertices - 1][0] = center[0];
        graph->vertices[graph->n_vertices - 1][1] = center[1];

        free(center);
    }
}

void compute_edges(graph_t *graph, mesh_t *mesh){
    GLsizei n = graph->n_vertices;
    GLsizei i, j, k;
    half_edge_t *e;
    triangle_t *triangle;
    for (i = 0; i < mesh->n_triangles; i++){
        triangle = mesh->triangle_list[i];
        for (k = 0; k < 3; k++){
            e = triangle->e[k];

            if (e->sym->t != NULL){                     /* not a border half edge   --> link to neighbour           */
                j = e->sym->t->idx;
            }
            else{
                add_infinite_vertex(graph, mesh, e);    /* border half edge         --> link to new infinite vertex */
                j = graph->n_vertices - 1;
            }
            add_edge(graph, i, j);
        }
    }
}

void add_edge(graph_t *graph, GLsizei src, GLsizei dst){
    (graph->n_edges)++;
    /* re-alloc for each new edge (not optimal)*/
    if (graph->n_edges == 1){
        graph->edge_list = (edge_t **)malloc(sizeof(edge_t *));
        if (graph->edge_list == NULL)
            error("Edge list of the graph cannot be malloc'd");
    }
    else{
        graph->edge_list = realloc(graph->edge_list, graph->n_edges * sizeof(edge_t *));
        if (graph->edge_list == NULL)
            error("Impossible to re-allocate memory for the edge list of the graph");
    }
    edge_t *e = (edge_t *)malloc(sizeof(edge_t));
    if (e == NULL)
        error("Graph edge cannot be malloc'd to be added");
    e->src = src;
    e->dst = dst;
    graph->edge_list[graph->n_edges - 1] = e;
}

void add_infinite_vertex(graph_t *graph, mesh_t *mesh, half_edge_t *e){
    GLfloat vertex[2];
    GLfloat a, b, c;
    GLsizei triangle_idx = e->t->idx;
    GLfloat *src = mesh->points[e->src];
    GLfloat *dst = mesh->points[e->dst];
    line_from_points(src, dst, &a, &b, &c);
    GLfloat slope = - a / b;

    /*  If the slope is > 0 and the dst is right of the src, or 
        if the slope is < 0 and the dst is left of the src, then
        the infinite edge goes to the right
        Otherwise the infinite edge goes to the left               */
    int orientation = ((slope > 0 && dst[0] > src[0]) || (slope < 0 && dst[0] < src[0])) ? 1 : -1;

    perpendicular_bisector_from_line(mesh->points[e->src], mesh->points[e->dst], &a, &b, &c);
    vertex[0] = orientation * X_MARGIN;     /* x target, left on right depending on orientation                     */
    vertex[1] = (c - a * vertex[0]) / b;    /* y target from the equation of the line perpendicular to hull edge    */

    (graph->n_vertices)++;

    /* re-alloc for each infinite vertex (not optimal) */
    graph->vertices = realloc(graph->vertices, graph->n_vertices * sizeof(graph->vertices[0]));
    if (graph->vertices == NULL)
        error("Impossible to re-allocate memory for vertices of the graph");
    graph->vertices[graph->n_vertices - 1][0] = vertex[0];
    graph->vertices[graph->n_vertices - 1][1] = vertex[1];
}