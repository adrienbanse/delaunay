#include "utils.h"

// https://www.geeksforgeeks.org/program-find-circumcenter-triangle-2/
void line_from_points(GLfloat p[2], GLfloat q[2], GLfloat *a, GLfloat *b, GLfloat *c){
    *a = q[1] - p[1];
    *b = p[0] - q[0];
    *c = *a * (p[0]) + *b * p[1];
}

// https://www.geeksforgeeks.org/program-find-circumcenter-triangle-2/
void perpendicular_bisector_from_line(GLfloat p[2], GLfloat q[2], GLfloat *a, GLfloat *b, GLfloat *c){
    GLfloat mid_point[2] = {(p[0] + q[0]) / 2, (p[1] + q[1]) / 2};
    *c = - *b * (mid_point[0]) + *a * (mid_point[1]);
    GLfloat temp = *a;
    *a = - *b;
    *b = temp;
}

// https://www.geeksforgeeks.org/program-find-circumcenter-triangle-2/
GLfloat* line_line_intersection(GLfloat a1, GLfloat b1, GLfloat c1, GLfloat a2, GLfloat b2, GLfloat c2){
    GLfloat det = a1 * b2 - a2 * b1;
    GLfloat* res = malloc(2 * sizeof(GLfloat));
    if (det == 0){
        res[0] = __FLT_MAX__;
        res[1] = __FLT_MAX__;
    }
    else{
        res[0] = (b2 * c1 - b1 * c2) / det;
        res[1] = (a1 * c2 - a2 * c1) / det;
    }
    return res;
}

// https://www.geeksforgeeks.org/program-find-circumcenter-triangle-2/
GLfloat* find_circum_center(GLfloat p[2], GLfloat q[2], GLfloat r[2]){
    GLfloat a, b, c, e, f, g;
    line_from_points(p, q, &a, &b, &c);
    line_from_points(q, r, &e, &f, &g);
    perpendicular_bisector_from_line(p, q, &a, &b, &c);
    perpendicular_bisector_from_line(q, r, &e, &f, &g);
    GLfloat* circumcenter = line_line_intersection(a, b, c, e, f, g);
    return (circumcenter[0] == __FLT_MAX__ && circumcenter[0] == __FLT_MAX__ ? NULL : circumcenter);
}
