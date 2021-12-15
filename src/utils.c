#include "utils.h"

int compare_points(const void *pointer_a, const void *pointer_b){
    GLfloat (*a)[2] = (GLfloat(*)[2]) pointer_a;
    GLfloat (*b)[2] = (GLfloat(*)[2]) pointer_b;
    GLfloat res = ((*a)[0] - (*b)[0] != 0 ? (*a)[0] - (*b)[0] : (*a)[1] - (*b)[1]);
    return (res > 0) - (res < 0);
}

