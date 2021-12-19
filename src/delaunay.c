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
* AUTHORS :         Adrien Banse and Diego de Crombrugghe   
* DATE :            23 December 2021
* CONTEXT:          LMECA2170 course project at UCLouvain
*                   https://perso.uclouvain.be/vincent.legat/zouLab/meca2170.php
*
*H*/

#include "delaunay.h"

void delaunay(Mesh *mesh){
    qsort(mesh->points, mesh->n_points, sizeof(mesh->points[0]), compare_points);
#if HISTORY_MODE
    erase_history(); // in case of
#endif
    triangulate(mesh, 0, mesh->n_points, NULL);
    clean_mesh(mesh);
}

void triangulate(Mesh *mesh, GLsizei begin, GLsizei end, Edge **res){
    if ((end - begin) == 2){
        Edge *a = make_edge(mesh, begin + 0, begin + 1);
#if HISTORY_MODE
        checkpoint_history(mesh);
#endif
        if (res == NULL)
            return;
        res[0] = a;
        res[1] = a->sym;
        return;
    }    

    if ((end - begin) == 3){
        Edge *a = make_edge(mesh, begin + 0, begin + 1);
        Edge *b = make_edge(mesh, begin + 1, begin + 2);
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
            Edge *c = connect(mesh, b, a);
#if HISTORY_MODE
            checkpoint_history(mesh);
#endif
            if (res == NULL)
                return;
            res[0] = c->sym;
            res[1] = c; 
            return;
        }
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

    Edge **cont_left = (Edge **)malloc(2 * sizeof(Edge *));
    if (cont_left == NULL)
        error("Left container in triangulate cannot be malloc'd");
    Edge **cont_right = (Edge **)malloc(2 * sizeof(Edge *));
    if (cont_left == NULL)
        error("Right container in triangulate cannot be malloc'd");

    triangulate(mesh, begin, begin + middle, cont_left);
    triangulate(mesh, begin + middle, end, cont_right);

    Edge *ldo = cont_left[0];
    Edge *ldi = cont_left[1];
    Edge *rdi = cont_right[0];
    Edge *rdo = cont_right[1];

    free(cont_left);
    free(cont_right);

    while (1){
        if (right_of(mesh, rdi->src, ldi))
            ldi = ldi->sym->next;
        else if (left_of(mesh, ldi->src, rdi))
            rdi = rdi->sym->prev;
        else
            break;
    }

    Edge *base = connect(mesh, ldi->sym, rdi);

    if ( mesh->points[ldi->src][0] == mesh->points[ldo->src][0] && 
         mesh->points[ldi->src][1] == mesh->points[ldo->src][1])
        ldo = base;
    if ( mesh->points[rdi->src][0] == mesh->points[rdo->src][0] &&
         mesh->points[rdi->src][1] == mesh->points[rdo->src][1])
        rdo = base->sym;

    Edge *rcand, *lcand, *t;
    int v_rcand, v_lcand;

    while (1){
        rcand = base->sym->next;
        lcand = base->prev;
        v_rcand = right_of(mesh, rcand->dst, base);
        v_lcand = right_of(mesh, lcand->dst, base);
        if (!(v_rcand || v_lcand))
            break;
        if (v_rcand){
            while ( right_of(mesh, rcand->next->dst, base) && 
                    in_circle(mesh, base->dst, base->src, rcand->dst, rcand->next->dst)){
                t = rcand->next;
                delete_edge(rcand);
                (mesh->n_deleted)++;
                rcand = t;
            }
        }
        if (v_lcand){
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
