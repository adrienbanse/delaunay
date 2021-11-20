typedef struct Point Point;
typedef struct Triangle Triangle;
typedef struct Vertex Vertex;
typedef struct Mesh Mesh;

struct Point{
    double x;
    double y;
};

struct Triangle{
    Triangle *t1, *t2, *t3;     // references to neighboring faces
    Vertex *v1, *v2, *v3;       // references to incident vertices
};

struct Vertex{
    Triangle *root;             // any incident face
    Point *p;                   // corresponding point
};

struct Mesh{
    Triangle **t_list;          // list of triangles
};

/* TODO */
void is_illegal(Vertex* p_i, Vertex* p_j, Mesh* mesh);

/* TODO */
Triangle** adjacent_triangles(Vertex* p_i, Vertex* p_j);











// typedef struct Point Point;
// typedef struct HalfEdge HalfEdge;
// typedef struct Vertex Vertex;

// struct Point{
//     double x;
//     double y;
// };

// struct HalfEdge{
//     HalfEdge *prev;
//     HalfEdge *next;
//     HalfEdge *twin;
//     Vertex *v;
//     Point *p;
// };

// struct Vertex{
//     HalfEdge *e;
//     Point *p;
// };

// struct Face{
//     HalfEdge *e;
// };


