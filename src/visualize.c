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

void initialize_history(History *hst){
    hst->edge_lists = (Edge**)malloc(sizeof(Edge *));
    hst->n_edge_list = (GLsizei *)malloc(sizeof(GLsizei));
    if (hst->edge_lists == NULL || hst->n_edge_list == NULL)
        error("History cannot be initialized");
    hst->length = 0;
}

void checkpoint_history(Mesh *mesh){
    FILE *f = fopen(HISTORY_FILE, "a");
    if (f == NULL)
        error("Impossible to open " HISTORY_FILE);
    Edge *e;
    GLsizei size = mesh->n_edges - mesh->n_deleted;
    GLsizei ret;
    ret = fwrite(&size, sizeof(GLsizei), 1, f);
    if (ret != 1)
        error("Impossible to write on " HISTORY_FILE);
    for (GLsizei i = 0; i < mesh->n_edges; i++){
        e = mesh->edge_list[i];
        if (!e->deleted)
            ret = fwrite(mesh->edge_list[i], sizeof(Edge), 1, f);
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

void read_history(History *hst){
    FILE *f = fopen(HISTORY_FILE, "r");
    if (f == NULL)
        error("Impossible to open " HISTORY_FILE);
    GLsizei n_edges, ret;

    ret = fread(&n_edges, sizeof(GLsizei), 1, f);
    if (ret != 1)
        error("Impossible to read on " HISTORY_FILE);
    Edge* edge_list = (Edge *)malloc(n_edges * sizeof(Edge));
    if (edge_list == NULL)
        error("Some edge list in read_history cannot be malloc'd");
    ret = fread(edge_list, sizeof(Edge), n_edges, f);
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

        edge_list = (Edge *)malloc(n_edges * sizeof(Edge));
        if (edge_list == NULL)
            error("Some edge list in read_history cannot be malloc'd");
        ret = fread(edge_list, sizeof(Edge), n_edges, f);
        if (ret != n_edges)
            error("Impossible to read on " HISTORY_FILE);

        hst->edge_lists = realloc(hst->edge_lists, (hst->length + 1) * sizeof(Edge *));
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

void clean_history(History *hst){

#if ERASE_AFTER
    erase_history();
#endif

    Edge **edge_list = hst->edge_lists;
    for (GLsizei i = 0; i < hst->length; i++)
        free(edge_list[i]);
    free(edge_list);
    free(hst->n_edge_list);
    free(hst);
}

void visualize_mesh_simple(Mesh *mesh){
    GLfloat (*points)[2] = mesh->points;
    GLsizei n_points = mesh->n_points;

    GLsizei i;
    Edge *e;
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

void visualize_history(Mesh *mesh){
    History *hst = (History *)malloc(sizeof(History));
    initialize_history(hst);
    read_history(hst);

    bov_window_t* window = bov_window_new(800, 800, TITLE_HISTORY_MODE);
    GLfloat (*points)[2] = mesh->points;
    double wtime;
    GLsizei i, history_idx, n_edges_history;
    Edge *edge_history;
    Edge e;
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
        if (wtime > N_SECOND * hst->length){
            history_idx = hst->length - 1;
            mode = 2;
        }
        else
            history_idx = (GLsizei) (wtime / N_SECOND) % hst->length;

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
