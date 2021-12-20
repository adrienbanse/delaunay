/*H**********************************************************************
* FILENAME :        visualize.c          
*
* DESCRIPTION :     Delaunay triangulation and EMST visualization 
*                   library based on BOV library
*       
* NOTES :           /
*
* AUTHORS :         Adrien Banse and Diego de Crombrugghe   
* DATE :            23 December 2021
* CONTEXT:          LMECA2170 course project at UCLouvain
*                   https://perso.uclouvain.be/vincent.legat/zouLab/meca2170.php
*
*H*/

#include "visualize.h"

void initialize_history(history_t *hst){
    hst->edge_lists = (half_edge_t**)malloc(sizeof(half_edge_t *));
    hst->n_edge_list = (GLsizei *)malloc(sizeof(GLsizei));
    if (hst->edge_lists == NULL || hst->n_edge_list == NULL)
        error("History cannot be initialized");
    hst->length = 0;
}

void checkpoint_history(mesh_t *mesh){
    FILE *f = fopen(HISTORY_FILE, "a");
    if (f == NULL)
        error("Impossible to open " HISTORY_FILE);
    half_edge_t *e;
    GLsizei size = mesh->n_edges - mesh->n_deleted;
    GLsizei ret;
    ret = fwrite(&size, sizeof(GLsizei), 1, f);
    if (ret != 1)
        error("Impossible to write on " HISTORY_FILE);
    for (GLsizei i = 0; i < mesh->n_edges; i++){
        e = mesh->edge_list[i];
        if (!e->deleted)
            ret = fwrite(mesh->edge_list[i], sizeof(half_edge_t), 1, f);
            if (ret != 1)
                error("Impossible to write on " HISTORY_FILE);
    } 
    ret = fclose(f);
    if (ret != 0)
        error("Impossible to close " HISTORY_FILE);
}

void erase_history(){
    FILE *f = fopen(HISTORY_FILE, "w");
    if (f == NULL)
        error("Impossible to erase " HISTORY_FILE);
    GLsizei ret = fclose(f);
    if (ret != 0)
        error("Impossible to close " HISTORY_FILE);
}

void read_history(history_t *hst){
    FILE *f = fopen(HISTORY_FILE, "r");
    if (f == NULL)
        error("Impossible to open " HISTORY_FILE);
    GLsizei n_edges, ret;

    ret = fread(&n_edges, sizeof(GLsizei), 1, f);
    if (ret != 1)
        error("Impossible to read on " HISTORY_FILE);
    half_edge_t* edge_list = (half_edge_t *)malloc(n_edges * sizeof(half_edge_t));
    if (edge_list == NULL)
        error("Some edge list in read_history cannot be malloc'd");
    ret = fread(edge_list, sizeof(half_edge_t), n_edges, f);
    if (ret != n_edges)
        error("Impossible to read on " HISTORY_FILE);

    hst->edge_lists[0] = edge_list;
    hst->n_edge_list[0] = n_edges;
    (hst->length)++;

    while (1){
        ret = fread(&n_edges, sizeof(GLsizei), 1, f);
        if (feof(f))
            break;
        else if (ret != 1)
            error("Impossible to read on " HISTORY_FILE);

        edge_list = (half_edge_t *)malloc(n_edges * sizeof(half_edge_t));
        if (edge_list == NULL)
            error("Some edge list in read_history cannot be malloc'd");
        ret = fread(edge_list, sizeof(half_edge_t), n_edges, f);
        if (ret != n_edges)
            error("Impossible to read on " HISTORY_FILE);

        hst->edge_lists = realloc(hst->edge_lists, (hst->length + 1) * sizeof(half_edge_t *));
        if (hst->edge_lists == NULL)
            error("Memory re-allocation failed for edge lists of history");
        hst->n_edge_list = realloc(hst->n_edge_list, (hst->length + 1) * sizeof(GLsizei));
        if (hst->n_edge_list == NULL)
            error("Memory re-allocation failed for num. of edges list of history");
        hst->edge_lists[hst->length] = edge_list;
        hst->n_edge_list[hst->length] = n_edges;
        (hst->length)++;
    }
    ret = fclose(f);
    if (ret != 0)
        error("Impossible to close " HISTORY_FILE);
}

void clean_history(history_t *hst){

#if ERASE_AFTER
    erase_history();
#endif

    half_edge_t **edge_list = hst->edge_lists;
    for (GLsizei i = 0; i < hst->length; i++)
        free(edge_list[i]);
    free(edge_list);
    free(hst->n_edge_list);
    free(hst);
}

void visualize_mesh_simple(mesh_t *mesh){
    GLfloat (*points)[2] = mesh->points;
    GLsizei n_points = mesh->n_points;

    GLsizei i;
    half_edge_t *e;
    bov_points_t *edge_draw;
    GLfloat (*edge_points)[2] = malloc(sizeof(points[0]) * 2);

    bov_window_t* window = bov_window_new(800, 800, TITLE_FINAL_MODE);

    bov_points_t *points_draw = bov_points_new(points, n_points, GL_STATIC_DRAW);
	bov_points_set_color(points_draw, POINT_COLOR);

	while(!bov_window_should_close(window)){
        for (i = 0; i < mesh->n_edges; i++){
            e = mesh->edge_list[i]; 
            if (e->deleted)
                continue;
            edge_points[0][0] = points[e->src][0];
            edge_points[0][1] = points[e->src][1];
            edge_points[1][0] = points[e->dst][0];
            edge_points[1][1] = points[e->dst][1];
            edge_draw = bov_points_new(edge_points, 2, GL_STATIC_DRAW);
            if (e->in_tree){
                bov_points_set_width(edge_draw, EMST_EDGE_WIDTH);
                bov_points_set_color(edge_draw, EMST_EDGE_COLOR);
            }
            else
                bov_points_set_width(edge_draw, EDGE_WIDTH);
            bov_lines_draw(window, edge_draw, 0, BOV_TILL_END);
            bov_points_delete(edge_draw);
        }

        bov_points_set_width(points_draw, POINT_WIDTH);
		bov_points_draw(window, points_draw, 0, BOV_TILL_END);

		bov_window_update(window);
	}

	bov_points_delete(points_draw);
    free(edge_points);
    bov_window_delete(window);
}

void visualize_history(mesh_t *mesh){
    history_t *hst = (history_t *)malloc(sizeof(history_t));
    initialize_history(hst);
    read_history(hst);

    bov_window_t* window = bov_window_new(800, 800, TITLE_HISTORY_MODE);
    GLfloat (*points)[2] = mesh->points;
    double wtime;
    GLsizei i, history_idx, n_edges_history;
    half_edge_t *edge_history;
    half_edge_t e;
    GLfloat (*edge_points)[2] = malloc(sizeof(GLfloat) * 2);
    bov_points_t *edge_draw;

    bov_points_t *points_draw = bov_points_new(points, mesh->n_points, GL_DYNAMIC_DRAW);
	bov_points_set_color(points_draw, POINT_COLOR);

    bov_text_t* delaunay_txt = bov_text_new(DELAUNAY_TXT, GL_DYNAMIC_DRAW);
    bov_text_t* emst_txt = bov_text_new(EMST_TXT, GL_DYNAMIC_DRAW);
    bov_text_t* done_txt = bov_text_new(DONE_TXT, GL_DYNAMIC_DRAW);

    bov_text_set_pos(delaunay_txt, TEXT_POSITION);
    bov_text_set_pos(emst_txt, TEXT_POSITION);
    bov_text_set_color(emst_txt, EMST_EDGE_COLOR);
    bov_text_set_pos(done_txt, TEXT_POSITION);

    int mode = 0;
    while(!bov_window_should_close(window)){
		wtime = bov_window_get_time(window);
        if (wtime > N_SECOND_STEP * hst->length){
            history_idx = hst->length - 1;
            mode = 2;
        }
        else
            history_idx = (GLsizei) (wtime / N_SECOND_STEP) % hst->length;

        if (mode == 0)
            bov_text_draw(window, delaunay_txt);
        else if (mode == 1)
            bov_text_draw(window, emst_txt);
        else
            bov_text_draw(window, done_txt);

        edge_history = hst->edge_lists[history_idx];
        n_edges_history = hst->n_edge_list[history_idx];
        for (i = 0; i < n_edges_history; i++){
            e = edge_history[i];
            edge_points[0][0] = points[e.src][0];
            edge_points[0][1] = points[e.src][1];
            edge_points[1][0] = points[e.dst][0];
            edge_points[1][1] = points[e.dst][1];
            edge_draw = bov_points_new(edge_points, 2, GL_DYNAMIC_DRAW);
            if (e.in_tree){
                mode = 1;
                bov_points_set_color(edge_draw, EMST_EDGE_COLOR);
                bov_points_set_width(edge_draw, EMST_EDGE_WIDTH);
            }
            else
                bov_points_set_width(edge_draw, EDGE_WIDTH);
            bov_lines_draw(window, edge_draw, 0, BOV_TILL_END);
            bov_points_delete(edge_draw);
        }

        bov_points_set_width(points_draw, POINT_WIDTH);
		bov_points_draw(window, points_draw, 0, BOV_TILL_END);

		bov_window_update(window);
	}

    bov_text_delete(delaunay_txt);
    bov_text_delete(emst_txt);
    bov_text_delete(done_txt);
    bov_points_delete(points_draw);
    free(edge_points);
    bov_window_delete(window);
    clean_history(hst);
}

void visualize_mesh_with_dual(mesh_t *mesh, graph_t *graph){
    edge_t *se;

    GLfloat (*points)[2] = mesh->points;
    GLsizei n_points = mesh->n_points;

    GLfloat (*vertices)[2] = graph->vertices;
    GLsizei n_vertices = graph->n_vertices;

    GLsizei i, j;
    half_edge_t *e;
    bov_points_t *edge_draw;
    GLfloat (*edge_points)[2] = malloc(sizeof(edge_points[0]) * 2);

    bov_points_t *dual_edge_draw;
    GLfloat (*dual_edge_vertices)[2] = malloc(sizeof(dual_edge_vertices[0]) * 2);

    bov_window_t* window = bov_window_new(800, 800, "Delaunay triangulation and Voronoi graph");

    bov_points_t *points_draw = bov_points_new(points, n_points, GL_STATIC_DRAW);
	bov_points_set_color(points_draw, POINT_COLOR);

    bov_points_t *vertices_draw = bov_points_new(vertices, n_vertices, GL_STATIC_DRAW);
    bov_points_set_color(vertices_draw, POINT_COLOR);

    unsigned int counter;
	while(!bov_window_should_close(window)){
        counter = bov_window_get_counter(window);
        for (i = 0; i < mesh->n_edges && (counter % 2 != 0); i++){
            e = mesh->edge_list[i]; 
            if (e->deleted)
                continue;
            edge_points[0][0] = points[e->src][0];
            edge_points[0][1] = points[e->src][1];
            edge_points[1][0] = points[e->dst][0];
            edge_points[1][1] = points[e->dst][1];
            edge_draw = bov_points_new(edge_points, 2, GL_STATIC_DRAW);
            if (e->in_tree){
                bov_points_set_width(edge_draw, EMST_EDGE_WIDTH);
                bov_points_set_color(edge_draw, EMST_EDGE_COLOR);
            }
            else{
                bov_points_set_width(edge_draw, EDGE_WIDTH);
                bov_points_set_color(edge_draw, EMST_EDGE_COLOR);
            }
            bov_lines_draw(window, edge_draw, 0, BOV_TILL_END);
            bov_points_delete(edge_draw);
        }

        for (i = 0; i < graph->n_edges; i++){
            se = graph->edge_list[i];
            dual_edge_vertices[0][0] = vertices[se->src][0];
            dual_edge_vertices[0][1] = vertices[se->src][1];
            dual_edge_vertices[1][0] = vertices[se->dst][0];
            dual_edge_vertices[1][1] = vertices[se->dst][1];

            if (dual_edge_vertices[1][0] == 0 && dual_edge_vertices[1][1] == 0)
                continue;

            dual_edge_draw = bov_points_new(dual_edge_vertices, 2, GL_STATIC_DRAW);
            bov_points_set_width(dual_edge_draw, 0.3 * EDGE_WIDTH);
            bov_lines_draw(window, dual_edge_draw, 0, BOV_TILL_END);
            bov_points_delete(dual_edge_draw);
        }

        bov_points_set_width(points_draw, POINT_WIDTH);
		bov_points_draw(window, points_draw, 0, BOV_TILL_END);

		bov_window_update(window);
	}

    bov_points_delete(vertices_draw);
	bov_points_delete(points_draw);
    free(dual_edge_vertices);
    free(edge_points);
    bov_window_delete(window);
}

void visualize_with_circles(graph_t *graph, mesh_t *mesh){

    circle_t *circle_st;
    circle_t *circles = (circle_t *)malloc(mesh->n_triangles * sizeof(circle_t));

    GLfloat radius, *center, *ref_point;
    for (GLsizei i = 0; i < mesh->n_triangles; i++){
        GLfloat (*circle)[2] = malloc(CIRCLES_RESOLUTION * sizeof(circle[0]));
        center = graph->vertices[i];
        ref_point = mesh->points[mesh->triangle_list[i]->e[0]->src];
        radius = sqrtf((center[0] - ref_point[0]) * (center[0] - ref_point[0]) + (center[1] - ref_point[1]) * (center[1] - ref_point[1]));
        smooth_circle(circle, center[0], center[1], radius);
        circle_st = (circle_t *)malloc(sizeof(circle_t));
        circle_st->circle = circle;
        circles[i] = *circle_st;
    }

    GLfloat (*points)[2] = mesh->points;
    GLsizei n_points = mesh->n_points;

    GLsizei i;
    half_edge_t *e;
    bov_points_t *edge_draw;
    GLfloat (*edge_points)[2] = malloc(sizeof(edge_points[0]) * 2);

    bov_window_t* window = bov_window_new(800, 800, "to change");

    bov_points_t *points_draw = bov_points_new(points, n_points, GL_DYNAMIC_DRAW);
	bov_points_set_color(points_draw, POINT_COLOR);

    double wtime;
    GLsizei n_circles;

    bov_points_t *circle_points_draw, *circle_center_draw;

	while(!bov_window_should_close(window)){
        wtime = bov_window_get_time(window);
        if (wtime > N_SECOND_CIRCLE * mesh->n_triangles){
            n_circles = mesh->n_triangles;
        }
        else
            n_circles = (GLsizei) (wtime / N_SECOND_CIRCLE) % mesh->n_triangles;

        for (i = 0; i < n_circles; i++){
            // draw circles
            circle_points_draw = bov_points_new(circles[i].circle, CIRCLES_RESOLUTION, GL_DYNAMIC_DRAW);
            bov_points_set_width(circle_points_draw, 0.2 * EDGE_WIDTH);
            bov_line_loop_draw(window, circle_points_draw, 0, BOV_TILL_END);  
            circle_center_draw = bov_points_new(&graph->vertices[i], 1, GL_DYNAMIC_DRAW);
            bov_points_set_color(circle_center_draw, RED_COLOR);
            bov_points_set_width(circle_center_draw, POINT_WIDTH);
            bov_points_draw(window, circle_center_draw, 0, BOV_TILL_END);
            bov_points_delete(circle_points_draw);
            bov_points_delete(circle_center_draw);
        }
        
        for (i = 0; i < mesh->n_edges; i++){
            e = mesh->edge_list[i]; 
            if (e->deleted)
                continue;
            edge_points[0][0] = points[e->src][0];
            edge_points[0][1] = points[e->src][1];
            edge_points[1][0] = points[e->dst][0];
            edge_points[1][1] = points[e->dst][1];
            edge_draw = bov_points_new(edge_points, 2, GL_DYNAMIC_DRAW);
            if (e->in_tree){
                bov_points_set_width(edge_draw, EMST_EDGE_WIDTH);
                bov_points_set_color(edge_draw, EMST_EDGE_COLOR);
            }
            else
                bov_points_set_width(edge_draw, EDGE_WIDTH);
            bov_lines_draw(window, edge_draw, 0, BOV_TILL_END);
            bov_points_delete(edge_draw);
        }

        bov_points_set_width(points_draw, POINT_WIDTH);
		bov_points_draw(window, points_draw, 0, BOV_TILL_END);

		bov_window_update(window);
	}

	bov_points_delete(points_draw);
    free(edge_points);
    bov_window_delete(window);
    
}

void smooth_circle(GLfloat (*circle)[2], GLfloat center_x, GLfloat center_y, GLfloat radius){
    GLsizei i;
    GLfloat theta;
    for (i=0; i<CIRCLES_RESOLUTION; i++){
        theta = ((float)i / (float)CIRCLES_RESOLUTION) * 2 * M_PI;
        circle[i][0] = center_x + radius * cosf(theta);
        circle[i][1] = center_y + radius * sinf(theta);
    }
}
