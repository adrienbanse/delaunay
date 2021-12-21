/*H**********************************************************************
* FILENAME :        visualize.c          
*
* DESCRIPTION :     Delaunay triangulation and EMST visualization 
*                   library based on BOV library
*       
* NOTES:            Voronoi circle's animation is inspired from 
*                   https://observablehq.com/@mbostock/the-delaunays-dual
* 
* AUTHORS :         Adrien Banse <adrien.banse@student.uclouvain.be>
*                   Diego de Crombrugghe <diego.decrombrugghe@student.uclouvain.be>
*
* DATE :            23 December 2021
*
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
    /* first write number of edges */
    ret = fwrite(&size, sizeof(GLsizei), 1, f);
    if (ret != 1)
        error("Impossible to write on " HISTORY_FILE);
    /* then write the edges */
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

    /* first read the number of edges */
    ret = fread(&n_edges, sizeof(GLsizei), 1, f);
    if (ret != 1)
        error("Impossible to read on " HISTORY_FILE);
    half_edge_t* edge_list = (half_edge_t *)malloc(n_edges * sizeof(half_edge_t));
    if (edge_list == NULL)
        error("Some edge list in read_history cannot be malloc'd");

    /* then read the edges */
    ret = fread(edge_list, sizeof(half_edge_t), n_edges, f);
    if (ret != n_edges)
        error("Impossible to read on " HISTORY_FILE);

    hst->edge_lists[0] = edge_list;
    hst->n_edge_list[0] = n_edges;
    (hst->length)++;

    /* continue until reach end of file */
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
    if (edge_points == NULL)
        error("Edge points cannot be malloc'd");
    bov_window_t* window = bov_window_new(800, 800, TITLE_FINAL_MODE);
    bov_window_enable_help(window);

    bov_points_t *points_draw = bov_points_new(points, n_points, GL_STATIC_DRAW);
	bov_points_set_color(points_draw, POINT_COLOR);

    char* info_txt_str = write_info_txt();
    bov_text_t* info_txt= bov_text_new((GLubyte*) info_txt_str, GL_DYNAMIC_DRAW);
    bov_text_set_pos(info_txt, INFO_POSITION);
    bov_text_set_space_type(info_txt, PIXEL_SPACE);

	while(!bov_window_should_close(window)){

        /*  *************************
            DRAW EDGES
            ************************* */

        for (i = 0; i < mesh->n_edges; i++){
            e = mesh->edge_list[i]; 
            if (e->deleted)
                continue;
            edge_points[0][0] = points[e->src][0];
            edge_points[0][1] = points[e->src][1];
            edge_points[1][0] = points[e->dst][0];
            edge_points[1][1] = points[e->dst][1];
            edge_draw = bov_points_new(edge_points, 2, GL_STATIC_DRAW);
            /* if in EMST, different width and color */
            if (e->in_tree){
                bov_points_set_width(edge_draw, EMST_EDGE_WIDTH);
                bov_points_set_color(edge_draw, EMST_EDGE_COLOR);
            }
            else{
                bov_points_set_width(edge_draw, EDGE_WIDTH);
                bov_points_set_color(edge_draw, EDGE_COLOR);
            }
            bov_lines_draw(window, edge_draw, 0, BOV_TILL_END);
            bov_points_delete(edge_draw);
        }

        /*  *************************
            DRAW POINTS
            ************************* */

        bov_points_set_width(points_draw, POINT_WIDTH);
		bov_points_draw(window, points_draw, 0, BOV_TILL_END);

        bov_text_draw(window, info_txt);

		bov_window_update(window);
	}   

    bov_text_delete(info_txt);  
    free(info_txt_str);
	bov_points_delete(points_draw);
    free(edge_points);
    bov_window_delete(window);
}

void visualize_history(mesh_t *mesh){
    /* first we store what is in the history file */
    history_t *hst = (history_t *)malloc(sizeof(history_t));
    if (hst == NULL)
        error("History cannot be malloc'd");

    initialize_history(hst);
    read_history(hst);

    bov_window_t* window = bov_window_new(800, 800, TITLE_HISTORY_MODE);
    bov_window_enable_help(window);

    GLfloat (*points)[2] = mesh->points;
    double wtime;
    GLsizei i, history_idx, n_edges_history;
    half_edge_t *edge_history;
    half_edge_t e;
    GLfloat (*edge_points)[2] = malloc(sizeof(GLfloat) * 2);
    if (edge_points == NULL)
        error("Edge points cannot be malloc'd");
    bov_points_t *edge_draw;

    bov_points_t *points_draw = bov_points_new(points, mesh->n_points, GL_DYNAMIC_DRAW);
	bov_points_set_color(points_draw, POINT_COLOR);

    bov_text_t* delaunay_txt = bov_text_new(DELAUNAY_TXT, GL_DYNAMIC_DRAW);
    bov_text_t* emst_txt = bov_text_new(EMST_TXT, GL_DYNAMIC_DRAW);
    bov_text_t* done_txt = bov_text_new(DONE_TXT, GL_DYNAMIC_DRAW);

    bov_text_set_pos(delaunay_txt, TEXT_POSITION);
    bov_text_set_space_type(delaunay_txt, PIXEL_SPACE);
    bov_text_set_pos(emst_txt, TEXT_POSITION);
    bov_text_set_space_type(emst_txt, PIXEL_SPACE);
    bov_text_set_color(emst_txt, EMST_EDGE_COLOR);
    bov_text_set_pos(done_txt, TEXT_POSITION);
    bov_text_set_space_type(done_txt, PIXEL_SPACE);

    char* info_txt_str = write_info_txt();
    bov_text_t* info_txt = bov_text_new((GLubyte*) info_txt_str, GL_DYNAMIC_DRAW);
    bov_text_set_pos(info_txt, INFO_POSITION);
    bov_text_set_space_type(info_txt, PIXEL_SPACE);

    /*  mode = 0 <--> delaunay execution
        mode = 1 <--> EMST execution
        mode = 2 <--> done                 */
    int mode = 0; 
    while(!bov_window_should_close(window)){
		wtime = bov_window_get_time(window);

        if (wtime > N_SECOND_STEP * hst->length){
            history_idx = hst->length - 1;
            mode = 2;
        }
        else
            history_idx = (GLsizei) (wtime / N_SECOND_STEP) % hst->length;

        /*  *************************
            DRAW HISTORY EDGES
            ************************* */

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
            else{
                bov_points_set_width(edge_draw, EDGE_WIDTH);
                bov_points_set_color(edge_draw, EDGE_COLOR);
            }
            bov_lines_draw(window, edge_draw, 0, BOV_TILL_END);
            bov_points_delete(edge_draw);
        }

        /*  *************************
            DRAW POINTS
            ************************* */

        bov_points_set_width(points_draw, POINT_WIDTH);
		bov_points_draw(window, points_draw, 0, BOV_TILL_END);

        /* handle modes for text */
        if (mode == 0)
            bov_text_draw(window, delaunay_txt);
        else if (mode == 1)
            bov_text_draw(window, emst_txt);
        else
            bov_text_draw(window, done_txt);

        bov_text_draw(window, info_txt);

		bov_window_update(window);
	}

    bov_text_delete(delaunay_txt);
    bov_text_delete(emst_txt);
    bov_text_delete(done_txt);
    bov_text_delete(info_txt);
    free(info_txt_str);
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
    if (edge_points == NULL)
        error("Edge points cannot be malloc'd");

    bov_points_t *dual_edge_draw;
    GLfloat (*dual_edge_vertices)[2] = malloc(sizeof(dual_edge_vertices[0]) * 2);
    if (dual_edge_vertices == NULL)
        error("Dual edge vertices cannot be malloc'd");

    bov_window_t* window = bov_window_new(800, 800, TITLE_VORONOI_FINAL_MODE);
    bov_window_enable_help(window);

    char* info_txt_str = write_info_txt();
    bov_text_t* info_txt= bov_text_new((GLubyte*) info_txt_str, GL_DYNAMIC_DRAW);
    bov_text_set_pos(info_txt, INFO_POSITION);
    bov_text_set_space_type(info_txt, PIXEL_SPACE);

    bov_text_t* disappear_txt = bov_text_new(DISAPPEAR_TXT, GL_DYNAMIC_DRAW);
    bov_text_set_pos(disappear_txt, DISAPPEAR_POSITION);
    bov_text_set_space_type(disappear_txt, PIXEL_SPACE);

    bov_points_t *points_draw = bov_points_new(points, n_points, GL_STATIC_DRAW);
	bov_points_set_color(points_draw, POINT_COLOR);

    bov_points_t *vertices_draw = bov_points_new(vertices, n_vertices, GL_STATIC_DRAW);
    bov_points_set_color(vertices_draw, POINT_COLOR);

    /*  counter % 2 == 0 <--> without delaunay edges
        counter % 2 != 0 <--> with delaunay edges    */
    unsigned int counter;
	while(!bov_window_should_close(window)){
        /*  *************************
            DRAW DELAUNAY EDGES
            ************************* */

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
            bov_points_set_width(edge_draw, EDGE_WIDTH);
            bov_points_set_color(edge_draw, EDGE_COLOR);
            bov_lines_draw(window, edge_draw, 0, BOV_TILL_END);
            bov_points_delete(edge_draw);
        }

        /*  *************************
            DRAW VORONOI EDGES
            ************************* */

        for (i = 0; i < graph->n_edges; i++){
            se = graph->edge_list[i];
            dual_edge_vertices[0][0] = vertices[se->src][0];
            dual_edge_vertices[0][1] = vertices[se->src][1];
            dual_edge_vertices[1][0] = vertices[se->dst][0];
            dual_edge_vertices[1][1] = vertices[se->dst][1];

            dual_edge_draw = bov_points_new(dual_edge_vertices, 2, GL_STATIC_DRAW);
            bov_points_set_width(dual_edge_draw, DUAL_EDGE_WIDTH);
            bov_points_set_color(dual_edge_draw, DUAL_EDGE_COLOR);
            bov_lines_draw(window, dual_edge_draw, 0, BOV_TILL_END);
            bov_points_delete(dual_edge_draw);
        }

        /*  *************************
            DRAW DELAUNAY POINTS
            ************************* */

        bov_points_set_width(points_draw, POINT_WIDTH);
		bov_points_draw(window, points_draw, 0, BOV_TILL_END);


        bov_text_draw(window, info_txt);
        bov_text_draw(window, disappear_txt);

		bov_window_update(window);
	}

    bov_points_delete(vertices_draw);
	bov_points_delete(points_draw);
    bov_text_delete(info_txt);
    free(info_txt_str);
    bov_text_delete(disappear_txt);
    free(dual_edge_vertices);
    free(edge_points);
    bov_window_delete(window);
}

void visualize_with_circles(graph_t *graph, mesh_t *mesh){

    circle_t *circle_st;
    circle_t *circles = (circle_t *)malloc(mesh->n_triangles * sizeof(circle_t));
    if (circles == NULL)
        error("Circles cannot be malloc'd for visualization");

    /* first we construct the circles for each triangle */
    GLfloat radius, *center, *ref_point, (*circle)[2];
    for (GLsizei i = 0; i < mesh->n_triangles; i++){
        circle = malloc(CIRCLES_RESOLUTION * sizeof(circle[0]));
        if (circle == NULL)
            error("Some circle cannot be malloc'd");
        center = graph->vertices[i];
        ref_point = mesh->points[mesh->triangle_list[i]->e[0]->src];
        radius = sqrtf((center[0] - ref_point[0]) * (center[0] - ref_point[0]) + (center[1] - ref_point[1]) * (center[1] - ref_point[1]));
        smooth_circle(circle, center[0], center[1], radius);
        circle_st = (circle_t *)malloc(sizeof(circle_t));
        if (circle_st == NULL)
            error("Circle structure cannot be malloc'd");
        circle_st->circle = circle;
        circles[i] = *circle_st;
        free(circle_st);
    }

    GLfloat (*points)[2] = mesh->points;
    GLsizei n_points = mesh->n_points;

    GLsizei i;
    half_edge_t *e;
    bov_points_t *edge_draw;
    GLfloat (*edge_points)[2] = malloc(sizeof(edge_points[0]) * 2);
    if (edge_points == NULL)
        error("Edge points cannot be malloc'd");

    bov_window_t* window = bov_window_new(800, 800, TITLE_VORONOI_CIRCLES_MODE);
    bov_window_enable_help(window);

    bov_points_t *points_draw = bov_points_new(points, n_points, GL_DYNAMIC_DRAW);
	bov_points_set_color(points_draw, POINT_COLOR);

    char* info_txt_str = write_info_txt();
    bov_text_t* info_txt= bov_text_new((GLubyte*) info_txt_str, GL_DYNAMIC_DRAW);
    bov_text_set_pos(info_txt, INFO_POSITION);
    bov_text_set_space_type(info_txt, PIXEL_SPACE);

    bov_text_t* disappear_txt = bov_text_new(DISAPPEAR_TXT, GL_DYNAMIC_DRAW);
    bov_text_set_pos(disappear_txt, DISAPPEAR_POSITION);
    bov_text_set_space_type(disappear_txt, PIXEL_SPACE);

    bov_text_t* current_txt;
    bov_text_t* circ_txt = bov_text_new(CIRC_TXT, GL_DYNAMIC_DRAW);
    bov_text_set_pos(circ_txt, TEXT_POSITION);
    bov_text_set_space_type(circ_txt, PIXEL_SPACE);
    bov_text_t* voronoi_txt = bov_text_new(VORONOI_TXT, GL_DYNAMIC_DRAW);
    bov_text_set_pos(voronoi_txt, TEXT_POSITION);
    bov_text_set_color(voronoi_txt, RED_COLOR);
    bov_text_set_space_type(voronoi_txt, PIXEL_SPACE);
    bov_text_t* done_txt = bov_text_new(DONE_TXT, GL_DYNAMIC_DRAW);
    bov_text_set_pos(done_txt, TEXT_POSITION);
    bov_text_set_space_type(done_txt, PIXEL_SPACE);


    double wtime;

    /*  counter % 2 == 0 <--> with delaunay edges
        counter % 2 != 0 <--> without delaunay edges */
    GLsizei n_circles, counter, n_edges = 0;
    int mode = 0;
    edge_t *se;
    GLfloat (*dual_edge_vertices)[2] = malloc(sizeof(dual_edge_vertices[0]) * 2);
    if (dual_edge_vertices == NULL)
        error("Dual edge vertices cannot be malloc'd");

    bov_points_t *circle_points_draw, *circle_center_draw, *dual_edge_draw;

    /*                      0 < wtime < time_for_full_circles   <--> draw circles one at a time
        time_for_full_circles < wtime < time_for_mode_1         <--> draw all circles
        time_for_mode_1       < wtime < time_for_voronoi        <--> draw voronoi edges one at a time 
        time_for_voronoi      < wtime < time_for_full_voronoi   <--> draw all voronoi edges            */
    double time_for_full_circles = N_SECOND_CIRCLE * mesh->n_triangles;
    double time_for_mode_1 = time_for_full_circles + N_SECOND_PAUSE;
    double time_for_voronoi = time_for_mode_1 + N_SECOND_PAUSE;
    double time_for_full_voronoi = time_for_voronoi +  N_SECOND_CIRCLE * graph->n_edges;

	while(!bov_window_should_close(window)){
        counter = bov_window_get_counter(window);
        wtime = bov_window_get_time(window);
        if (wtime > time_for_full_voronoi){
            current_txt = done_txt;
            n_edges = graph->n_edges;
        }
        else if (wtime > time_for_voronoi)
            n_edges = (GLsizei) ((wtime - time_for_voronoi) / N_SECOND_CIRCLE) % graph->n_edges;
        else if (wtime > time_for_mode_1){
            current_txt = voronoi_txt;
            mode = 1;
        }
        else if (wtime > time_for_full_circles)
            n_circles = mesh->n_triangles;
        else{
            current_txt = circ_txt;
            n_circles = (GLsizei) (wtime / N_SECOND_CIRCLE) % mesh->n_triangles;
        }

        /*  *************************
            DRAW CIRCLES
            ************************* */

        for (i = 0; i < n_circles; i++){
            if (mode == 0){
                circle_points_draw = bov_points_new(circles[i].circle, CIRCLES_RESOLUTION, GL_DYNAMIC_DRAW);
                bov_points_set_width(circle_points_draw, CIRCLES_WIDTH);
                bov_points_set_color(circle_points_draw, CIRCLES_COLOR);
                bov_line_loop_draw(window, circle_points_draw, 0, BOV_TILL_END);  
                bov_points_delete(circle_points_draw);
            }

            circle_center_draw = bov_points_new(&graph->vertices[i], 1, GL_DYNAMIC_DRAW);
            bov_points_set_width(circle_center_draw, CIRCLES_CENTER_WIDTH);
            bov_points_set_color(circle_center_draw, CIRCLES_CENTER_COLOR);
            bov_points_draw(window, circle_center_draw, 0, BOV_TILL_END);
            bov_points_delete(circle_center_draw);
        }

        /*  *************************
            DRAW VORONOI EDGES
            ************************* */

        for (i = 0; i < n_edges; i++){
            se = graph->edge_list[i];
            dual_edge_vertices[0][0] = graph->vertices[se->src][0];
            dual_edge_vertices[0][1] = graph->vertices[se->src][1];
            dual_edge_vertices[1][0] = graph->vertices[se->dst][0];
            dual_edge_vertices[1][1] = graph->vertices[se->dst][1];
            dual_edge_draw = bov_points_new(dual_edge_vertices, 2, GL_STATIC_DRAW);
            bov_points_set_color(dual_edge_draw, DUAL_EDGE_COLOR);
            bov_points_set_width(dual_edge_draw, DUAL_EDGE_WIDTH);
            bov_lines_draw(window, dual_edge_draw, 0, BOV_TILL_END);
            bov_points_delete(dual_edge_draw);
        }

        /*  *************************
            DRAW DELAUNAY EDGES
            ************************* */
        
        for (i = 0; i < mesh->n_edges && (counter % 2 == 0); i++){
            e = mesh->edge_list[i]; 
            if (e->deleted)
                continue;
            edge_points[0][0] = points[e->src][0];
            edge_points[0][1] = points[e->src][1];
            edge_points[1][0] = points[e->dst][0];
            edge_points[1][1] = points[e->dst][1];
            edge_draw = bov_points_new(edge_points, 2, GL_DYNAMIC_DRAW);
            bov_points_set_width(edge_draw, EDGE_WIDTH);
            bov_points_set_color(edge_draw, EDGE_COLOR);
            bov_lines_draw(window, edge_draw, 0, BOV_TILL_END);
            bov_points_delete(edge_draw);
        }

        /*  *************************
            DRAW DELAUNAY POINTS
            ************************* */

        bov_points_set_width(points_draw, POINT_WIDTH);
		bov_points_draw(window, points_draw, 0, BOV_TILL_END);

        bov_text_draw(window, info_txt);
        bov_text_draw(window, disappear_txt);
        bov_text_draw(window, current_txt);

		bov_window_update(window);
	}

    bov_text_delete(info_txt);
    free(info_txt_str);
    bov_text_delete(disappear_txt);
    bov_text_delete(circ_txt);
    bov_text_delete(voronoi_txt);
    bov_text_delete(done_txt);

	bov_points_delete(points_draw);
    free(edge_points);
    free(dual_edge_vertices);
    bov_window_delete(window);

    for (i = 0; i < mesh->n_triangles; i++){
        free(circles[i].circle);
    }
    free(circles);
    
}

void smooth_circle(GLfloat (*circle)[2], GLfloat center_x, GLfloat center_y, GLfloat radius){
    GLsizei i;
    GLfloat theta;
    for (i = 0; i < CIRCLES_RESOLUTION; i++){
        theta = ((float)i / (float)CIRCLES_RESOLUTION) * 2 * M_PI;
        circle[i][0] = center_x + radius * cosf(theta);
        circle[i][1] = center_y + radius * sinf(theta);
    }
}

char* write_info_txt(){
    char n_points_str[10];
    sprintf(n_points_str, "%d", N_POINTS);
#if UNIFORM
    char *uniform_str = "\nUniform sampling";
#else
    char *uniform_str = "\nNon-uniform sampling";
#endif
    char* info_txt = (char *) malloc(100 * sizeof(char));
    strcat(info_txt, "-- Point set informations --\n");
    strcat(info_txt, "Number of points: ");
    strcat(info_txt, n_points_str);
    strcat(info_txt, uniform_str);
    return info_txt;
}