#include "delaunay.h"

int delaunay(GLfloat points[][2], GLsizei n_points, Mesh* delaunay_triangulation){
    qsort(points, n_points, sizeof(points[0]), compare_points);
    triangulate(
        points, 
        0, 
        n_points, 
        delaunay_triangulation,
        NULL, 
        NULL
    );
    return EXIT_SUCCESS;
}

void triangulate(GLfloat points[][2], GLsizei begin, GLsizei n_points, Mesh* mesh, Edge* src, Edge* dst){
    if ((n_points - begin) == 2){
        make_edge(mesh, begin + 0, begin + 1);
        Edge a = mesh->edge_list[mesh->n_edges - 1];
        src = &a;
        dst = a.sym;
        return;
    }    

    if ((n_points - begin) == 3){
        make_edge(mesh, begin + 0, begin + 1);
        Edge a = mesh->edge_list[mesh->n_edges - 1];
        make_edge(mesh, begin + 1, begin + 2);
        Edge b = mesh->edge_list[mesh->n_edges - 1];
        splice(a.sym, &b);

        // Close triangle
        if (right_of(points[begin + 2], points[a.src], points[a.dst])){
            connect(mesh, b, a);
            src = &a;
            dst = b.sym;
            return;
        }
        
        if (left_of(points[begin + 2], points[a.src], points[a.dst])){
            connect(mesh, b, a);
            Edge c = mesh->edge_list[mesh->n_edges - 1];
            src = c.sym;
            dst = &c;
            return;
        }
        
        src = &a;
        dst = b.sym;
        return;
    }

    GLsizei middle = (n_points - begin + 1) / 2;
    

}
