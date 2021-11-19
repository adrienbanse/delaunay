#include <stdlib.h>
#include "inputs.h"
#include "delaunay.h"

int main(){
    Point* point_a = (Point*)malloc(sizeof(Point));
    point_a->x = 8;
    point_a->y = 7.4;
    Point* point_b = (Point*)malloc(sizeof(Point));
    point_b->x = 4;
    point_b->y = 10.4;

    Point* point_list[2] = {point_a, point_b};
    Mesh* res_mesh = bowyer_watson(point_list, 2);

    return EXIT_SUCCESS;
}