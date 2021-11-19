typedef struct Point Point;
typedef struct HalfEdge HalfEdge;
typedef struct Vertex Vertex;

struct Point{
    double x;
    double y;
}:

struct HalfEdge{
    HalfEdge prev;
    HalfEdge next;
    HalfEdge twin;
    Vertex v;
    Point p;
};

struct Vertex{
    HalfEdge e;
    Point p;
};

struct Face{
    HalfEdge e;
};

