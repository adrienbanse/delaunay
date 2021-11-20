typedef struct Point2D Point2D;
typedef struct Triangle Triangle;
typedef struct Edge Edge;

struct Point2D{
    double x;
    double y;
};

struct Triangle{
    int p1;     // index of p1
    int p2;     // index of p2
    int p3;     // index of p3
};

struct Edge{
    int p1;     // index of p1
    int p2;     // index of p2
};
