/*H**********************************************************************
* FILENAME :        delaunay.c             
*
* DESCRIPTION :     Divide-and-conquer algorithm for Delaunay triangu-
*                   lation. 
*       
* NOTES :           The functions are highly inspired from its Python 
*                   equivalent in 
*                   https://github.com/alexbaryzhikov/triangulation
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

#include "delaunay.h"

void delaunay(mesh_t *mesh){
    qsort(mesh->points, mesh->n_points, sizeof(mesh->points[0]), compare_points);
#if HISTORY_MODE
    erase_history(); /* in case of ERASE_AFTER was not set to 1 */
#endif
    triangulate(mesh, 0, mesh->n_points, NULL); /* beginning of the recursion */
    clean_mesh(mesh);
}

void triangulate(mesh_t *mesh, GLsizei begin, GLsizei end, half_edge_t **res){
    if ((end - begin) == 2){ /* end of the recursion */
        half_edge_t *a = make_edge(mesh, begin + 0, begin + 1);
#if HISTORY_MODE
        checkpoint_history(mesh);
#endif
        if (res == NULL)
            return;
        res[0] = a;
        res[1] = a->sym;
        return;
    }

    if ((end - begin) == 3){ /* end of the recursion */
        half_edge_t *a = make_edge(mesh, begin + 0, begin + 1);
        half_edge_t *b = make_edge(mesh, begin + 1, begin + 2);
        splice(a->sym, b);

        if (right_of(mesh, begin + 2, a)){
            connect(mesh, b, a);
#if HISTORY_MODE
            checkpoint_history(mesh);
#endif
            if (res == NULL)
                return;
            res[0] = a;
            res[1] = b->sym;
            return;
        }
        if (left_of(mesh, begin + 2, a)){
            half_edge_t *c = connect(mesh, b, a);
#if HISTORY_MODE
            checkpoint_history(mesh);
#endif
            if (res == NULL)
                return;
            res[0] = c->sym;
            res[1] = c; 
            return;
        }

        /* the three points are collinear */
#if HISTORY_MODE
        checkpoint_history(mesh);
#endif
        if (res == NULL)
            return;
        res[0] = a;
        res[1] = b->sym;
        return;
    }

    GLsizei middle = (end - begin + 1) / 2;

    /* containers are malloc'd to fetch the results of the children nodes in the recursion */
    half_edge_t **cont_left = (half_edge_t **)malloc(2 * sizeof(half_edge_t *));
    if (cont_left == NULL)
        error("Left container in triangulate cannot be malloc'd");
    half_edge_t **cont_right = (half_edge_t **)malloc(2 * sizeof(half_edge_t *));
    if (cont_left == NULL)
        error("Right container in triangulate cannot be malloc'd");

    /* divide and conquer */
    triangulate(mesh, begin, begin + middle, cont_left);
    triangulate(mesh, begin + middle, end, cont_right);

    half_edge_t *ldo = cont_left[0];
    half_edge_t *ldi = cont_left[1];
    half_edge_t *rdi = cont_right[0];
    half_edge_t *rdo = cont_right[1];

    free(cont_left);
    free(cont_right);

    /* computes the upper common tangent of left and right parts of the set of points */
    while (1){
        if (right_of(mesh, rdi->src, ldi))
            ldi = ldi->sym->next;
        else if (left_of(mesh, ldi->src, rdi))
            rdi = rdi->sym->prev;
        else
            break;
    }

    half_edge_t *base = connect(mesh, ldi->sym, rdi);

    /* adjusts ldo and rdo */
    if ( mesh->points[ldi->src][0] == mesh->points[ldo->src][0] && 
         mesh->points[ldi->src][1] == mesh->points[ldo->src][1])
        ldo = base;
    if ( mesh->points[rdi->src][0] == mesh->points[rdo->src][0] &&
         mesh->points[rdi->src][1] == mesh->points[rdo->src][1])
        rdo = base->sym;

    half_edge_t *rcand, *lcand, *t;
    int v_rcand, v_lcand;

    /* merge both results */
    while (1){
        rcand = base->sym->next;
        lcand = base->prev;
        v_rcand = right_of(mesh, rcand->dst, base);
        v_lcand = right_of(mesh, lcand->dst, base);
        if (!(v_rcand || v_lcand)){
            /* then the base is ok */
            break;
        }
        if (v_rcand){
            /* delete the points that fail the circle test (delaunay's property) */
            while ( right_of(mesh, rcand->next->dst, base) && 
                    in_circle(mesh, base->dst, base->src, rcand->dst, rcand->next->dst)){
                t = rcand->next;
                delete_edge(rcand);
                (mesh->n_deleted)++;
                rcand = t;
            }
        }
        if (v_lcand){
            /* delete the points that fail the circle test (delaunay's property) */
            while ( right_of(mesh, lcand->prev->dst, base) &&
                    in_circle(mesh, base->dst, base->src, lcand->dst, lcand->prev->dst)){
                t = lcand->prev;
                delete_edge(lcand);
                (mesh->n_deleted)++;
                lcand = t;
            }
        }
        if ( !v_rcand || 
             (v_lcand && in_circle(mesh, rcand->dst, rcand->src, lcand->src, lcand->dst)))
            base = connect(mesh, lcand, base->sym);
        else
            base = connect(mesh, base->sym, rcand->sym);
    }
#if HISTORY_MODE
    checkpoint_history(mesh);
#endif
    if (res == NULL)
        return;
    res[0] = ldo;    
    res[1] = rdo;    
}

int compare_points(const void *pointer_a, const void *pointer_b){
    GLfloat (*a)[2] = (GLfloat(*)[2]) pointer_a;
    GLfloat (*b)[2] = (GLfloat(*)[2]) pointer_b;
    GLfloat res = ((*a)[0] - (*b)[0] != 0 ? (*a)[0] - (*b)[0] : (*a)[1] - (*b)[1]);
    return (res > 0) - (res < 0);
}
