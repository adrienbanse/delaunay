#include "BOV.h"

#define RED "\e[0;31m"
#define NC "\e[0m"

void error(char msg[]);


GLfloat* find_circum_center(GLfloat p[2], GLfloat q[2], GLfloat r[2]);