#include "mesh.h"

void initialize_mesh(Mesh *mesh, GLfloat points[][2], GLsizei n_points, GLsizei n_edges_max){
    Edge **edge_list = (Edge **)malloc(n_edges_max * sizeof(Edge *));
    mesh->points = points;
    mesh->n_points = n_points;
    mesh->n_edges = 0;
    mesh->n_edges_max = n_edges_max;
    mesh->edge_list = edge_list;
}

void free_mesh(Mesh *mesh){
    Edge **edge_list = mesh->edge_list;
    for (GLsizei i = 0; i < mesh->n_edges; i++){
        free(edge_list[i]->sym);
        free(edge_list[i]);
    }
    free(edge_list);
    free(mesh->points);
    free(mesh);
}



Edge* make_edge(Mesh *mesh, int src, int dst){
    if (mesh->n_edges + 2 >= mesh->n_edges_max){
        mesh->n_edges_max += 100;
        mesh->edge_list = (Edge **)realloc(mesh->edge_list, mesh->n_edges_max * sizeof(Edge *));
    } 
    Edge *e = (Edge *)malloc(sizeof(Edge));
    Edge *s = (Edge *)malloc(sizeof(Edge));
    
    e->src = src;
    e->dst = dst;
    e->sym = s;
    e->next = e;
    e->prev = e;
    e->deleted = 0;
    e->in_tree = 0;

    s->src = dst;
    s->dst = src;
    s->sym = e;
    s->next = s;
    s->prev = s;
    s->deleted = 0;
    s->in_tree = 0;

    mesh->edge_list[mesh->n_edges] = e;
    (mesh->n_edges)++;

    return e;
}

Edge* connect(Mesh *mesh, Edge *a, Edge *b){
    Edge *e = make_edge(mesh, a->dst, b->src);
    splice(e, a->sym->prev);
    splice(e->sym, b);
    return e;
}

void delete_edge(Edge *e){
    splice(e, e->prev);
    splice(e->sym, e->sym->prev);
    e->deleted = 1;
    e->sym->deleted = 1;
}

void splice(Edge *a, Edge *b){
    if (a == b){
        return;
    }
    a->next->prev = b;
    b->next->prev = a;

    Edge **tmp = (Edge **)malloc(sizeof(Edge *));
    *tmp = a->next;
    a->next = b->next;
    b->next = *tmp;
    free(tmp);
}

void clean_mesh(Mesh* mesh){
    for (GLsizei i = 0; i < mesh->n_edges; i++)
        if (mesh->edge_list[i]->deleted){
            Edge *to_delete = mesh->edge_list[i];
            mesh->edge_list[i] = mesh->edge_list[mesh->n_edges - 1];
            free(to_delete->sym);
            free(to_delete);
            (mesh->n_edges)--;
            i--;
        }
}


int right_of(Mesh* mesh, GLsizei p_id, Edge* e){
    GLfloat *p = mesh->points[p_id];
    GLfloat *src = mesh->points[e->src];
    GLfloat *dst = mesh->points[e->dst];
    GLfloat det = (src[0] - p[0]) * (dst[1] - p[1]) - (src[1] - p[1]) * (dst[0] - p[0]);
    return det > 0;
}

int left_of(Mesh *mesh, GLsizei p_id, Edge *e){
    GLfloat *p = mesh->points[p_id];
    GLfloat *src = mesh->points[e->src];
    GLfloat *dst = mesh->points[e->dst];
    GLfloat det = (src[0] - p[0]) * (dst[1] - p[1]) - (src[1] - p[1]) * (dst[0] - p[0]);
    return det < 0;
}

int in_circle(Mesh *mesh, GLsizei a_id, GLsizei b_id, GLsizei c_id, GLsizei d_id){
    GLfloat *a = mesh->points[a_id];
    GLfloat *b = mesh->points[b_id];
    GLfloat *c = mesh->points[c_id];
    GLfloat *d = mesh->points[d_id];
    GLfloat a1 = a[0] - d[0];
    GLfloat a2 = a[1] - d[1];
    GLfloat b1 = b[0] - d[0];
    GLfloat b2 = b[1] - d[1];
    GLfloat c1 = c[0] - d[0];
    GLfloat c2 = c[1] - d[1];
    GLfloat a3 = a1 * a1 + a2 * a2;
    GLfloat b3 = b1 * b1 + b2 * b2;
    GLfloat c3 = c1 * c1 + c2 * c2;
    GLfloat det = a1 * b2 * c3 + a2 * b3 * c1 + a3 * b1 * c2 - (a3 * b2 * c1 + a1 * b3 * c2 + a2 * b1 * c3);
    return det < 0;
}

void compute_edge_lengths(Mesh* mesh){
    Edge *e;
    for (GLsizei i = 0; i < mesh->n_edges; i++){
        e = mesh->edge_list[i];
        GLfloat *src = mesh->points[e->src];
        GLfloat *dst = mesh->points[e->dst];
        e->length = (src[0] - dst[0]) * (src[0] - dst[0]) + (src[1] - dst[1]) * (src[1] - dst[1]);
        e->sym->length = e->length;
    }
}

int compare_edge_lengths(const void *double_edge_pointer_a, const void *double_edge_pointer_b){
    Edge **a = (Edge **) double_edge_pointer_a;
    Edge **b = (Edge **) double_edge_pointer_b;
    GLfloat res = (*a)->length > (*b)->length;
    return (res > 0) - (res < 0);
}

void make_set(UFNode *node){
    node->parent = node;
    node->size = 1;
}

UFNode* find(UFNode *node){
    if (node->parent == node)
        return node;
    node->parent = find(node->parent);
    return node->parent;
}

void union_find(UFNode *find_u, UFNode *find_v){
    if (find_u->size < find_v->size){
        // swap
        UFNode **tmp = (UFNode **)malloc(sizeof(UFNode*));
        *tmp = find_u;
        find_u = find_v;
        find_v = *tmp;
        free(tmp);
    }
    find_v->parent = find_u;
    find_u->size += find_v->size;
}



void visualize_mesh_simple(Mesh *mesh){
    GLfloat (*points)[2] = mesh->points;
    GLsizei n_points = mesh->n_points;

    GLsizei i;
    Edge *e;
    bov_points_t *edge_draw;
    GLfloat (*edge_points)[2] = malloc(sizeof(points[0]) * 2);

    bov_window_t* window = bov_window_new(800, 800, "Fast Delaunay");
	// bov_window_set_color(window, (GLfloat[]){0.9f, 0.85f, 0.8f, 1.0f});
    bov_window_set_color(window, (GLfloat[]){1, 1, 1, 1});

    bov_points_t *points_draw = bov_points_new(points, n_points, GL_STATIC_DRAW);
	bov_points_set_color(points_draw, (GLfloat[4]) {0.0, 0.0, 0.0, 1.0});
	bov_points_set_outline_color(points_draw, (GLfloat[4]) {0.3, 0.12, 0.0, 0.25});

	while(!bov_window_should_close(window)){
        for (i = 0; i < mesh->n_edges; i++){
            e = mesh->edge_list[i]; 
            edge_points[0][0] = points[e->src][0];
            edge_points[0][1] = points[e->src][1];
            edge_points[1][0] = points[e->dst][0];
            edge_points[1][1] = points[e->dst][1];

            edge_draw = bov_points_new(edge_points, 2, GL_STATIC_DRAW);
            bov_points_set_width(edge_draw, 0.0012);
            if (e->in_tree)
                bov_points_set_color(edge_draw, (GLfloat[4]) {1.0, 0.0, 0.0, 1.0});
            bov_lines_draw(window, edge_draw, 0, BOV_TILL_END);
            bov_points_delete(edge_draw);
        }

        bov_points_set_width(points_draw, 0.009);
		bov_points_draw(window, points_draw, 0, BOV_TILL_END);

		bov_window_update(window);
	}

	bov_points_delete(points_draw);
    free(edge_points);
    bov_window_delete(window);
}