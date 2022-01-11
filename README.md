# Delaunay triangulations and extensions

This C program is a O(n log(n)) "divide and conquer" implementation of the Delaunay triangulation of a given set of points. It is extended with
  * an application of the Delaunay triangulation: efficient computation of the Euclidian Minimum Spanning Tree thanks to Kruskal's algorithm, 
  * a linear time implementation of the derivation of the Voronoi diagram from the Delaunay triangulation, 
  * four types of visualization (see Visualization)

This program was written as part of the "LMECA2170 - Numerical Geometry" course project course at UCLouvain (website: https://perso.uclouvain.be/vincent.legat/zouLab/meca2170.php?action=valves).

**Any source of inspiration is explicitely written in the code source.**

## Structure of the project

The project should contain:
  * this file (**README.md**),
  * the description of the structure of the program in **CMakeLists.txt**,
  * a **src** directory containing the the source code of your program,
  * a **doc** directory containing more documentation,
  * a **deps** directory containing the BOV library.

Each source code file (.c, .h) in the **src** directory comes with a description in the header of the latter.

See [doc/COMPILING.md](doc/COMPILING.md) for a step by step tutorial on how to build the program, see [doc/tutorial.md](doc/tutorial.md) for a step by step tutorial on how to use the BOV library, see [deps/BOV/include/BOV.h](deps/BOV/include/BOV.h) for help on the BOV library functions and see [deps/BOV/examples/](deps/BOV/examples/) for more examples using the BOV library.

## Usage

See [doc/COMPILING.md](doc/COMPILING.md) for a tutorial on how to build the program. Here are some examples of usage, in **src/config.h**.

Test the rapidity of the triangulation:
```c
#define EMST                        0
#define VORONOI                     0

#define FINAL_MODE                  0
#define HISTORY_MODE                0  
#define VORONOI_FINAL_MODE          0
#define VORONOI_CIRCLES_MODE        0
```

See all the visualizations (see Visualization):
```c
#define EMST                        1
#define VORONOI                     1

#define FINAL_MODE                  1
#define HISTORY_MODE                1  
#define VORONOI_FINAL_MODE          1
#define VORONOI_CIRCLES_MODE        1
```

Compute and see final results of Delaunay triangulation and Voronoi diagram (see Visualization):
```c
#define EMST                        0
#define VORONOI                     1

#define FINAL_MODE                  1
#define HISTORY_MODE                0  
#define VORONOI_FINAL_MODE          1
#define VORONOI_CIRCLES_MODE        0
```

## Visualization

There are four visualization modes : <code>FINAL_MODE</code>, <code>HISTORY_MODE</code>, <code>VORONOI_FINAL_MODE</code> and <code>VORONOI_CIRCLES_MODE</code>.

### <code>FINAL_MODE = 1</code>

Shows the final result of the Delaunay triangulation, EMST edges are in red if EMST is executed (see Parameters).

<img src="https://user-images.githubusercontent.com/45042779/146961100-b600502b-1edb-4110-aed8-3a64ce7685ea.jpg" width="800" height="800">

### <code>HISTORY_MODE = 1</code>

Show the whole "divide-and-conquer" execution of the Delaunay triangulation, and the execution of Kruskal's algorithm if EMST is executed (see Parameters). It saves the execution in <code>HISTORY_FILE</code> where current states were saved during the execution. If <code>ERASE_AFTER</code> is set to 1 (see Parameters), then the file is erased just after the visualization. 

<img src="https://user-images.githubusercontent.com/45042779/146959524-edaa4aea-66b0-4132-8a37-6e465b511ccf.gif" width="800" height="800"> 

### <code>VORONOI_FINAL_MODE = 1</code>

Shows the final result of the derivation of the Voronoi diagram from the Delaunay triangulation, if Voronoi derivation is executed (see Parameters). There is the possibility to show or not the Delaunay triangulation with it during the animation.

<img src="https://user-images.githubusercontent.com/45042779/146962301-63562610-b130-4c43-a291-e15cf2e42eef.jpg" width="800" height="800"> 

### <code>VORONOI_CIRCLES_MODE = 1</code>

Shows the computation of the vertices of the Voronoi diagram (the circumcenters of the triangles of the Delaunay triangulation), and the derivation of its edges. There is the possibility to show or not the Delaunay triangulation with it during the animation.

<img src="https://user-images.githubusercontent.com/45042779/146960552-1a56c91e-945a-4055-999c-5e2f22819eca.gif" width="800" height="800"> 

## Complexity

The divide-and-conquer is in O(n log(n)), and so are both extensions.

![time_1](https://user-images.githubusercontent.com/45042779/148994569-c8272dc7-9190-45bf-b608-3d30dc43176f.png)

Suppose a Delaunay triangulation is given, applying Kruskal's algorithm to it requires O(n log(n)) operations since there are O(n) edges in the triangulation, and finding the Voronoi triangulation takes O(n) operations. 

![time_2](https://user-images.githubusercontent.com/45042779/148994593-bb9ea7e1-26e8-4c27-9d61-4e33039c247d.png)

## Parameters

All execution, visualization, and other parameters lie in **src/config.h** file. 

Here is a description for each execution parameter: 
  * <code>N_POINTS</code>: number of points generated
  * <code>UNIFORM</code>: boolean variable to decide if the generation is uniform or not
  * <code>EMST</code>: boolean variable to decide if the Euclidian Minimum Spanning Tree is computed
  * <code>VORONOI</code>: boolean variable to decide if the Voronoi diagram is computed
  * <code>FINAL_MODE</code>: visualization in <code>FINAL_MODE</code> is executed (see Visualization)
  * <code>HISTORY_MODE</code>: visualization in <code>HISTORY_MODE</code> is executed (see Visualization)
  * <code>VORONOI_FINAL_MODE</code>: visualization in <code>VORONOI_FINAL_MODE</code> is executed (see Visualization)
  * <code>VORONOI_CIRCLES_MODE</code>: visualization in <code>VORONOI_CIRCLES_MODE</code> is executed (see Visualization)
  * <code>ERASE_AFTER</code>: the <code>HISTORY_FILE</code> is erased after usage (see Visualization)

Here is a description for some visualization parameter (we skip the message configurations, see **config.h**):
  * <code>N_SECOND_STEP</code>: duration in seconds of one step for the <code>HISTORY_MODE</code> visualization
  * <code>N_SECOND_CIRCLE</code>: duration in seconds of one step for the <code>VORONOI_CIRCLES_MODE</code> visualization
  * <code>N_SECOND_PAUSE</code>: duration in seconds of one pause for the <code>VORONOI_CIRCLES_MODE</code> visualization
  * <code>POINT_WIDTH</code>: basic point width
  * <code>POINT_COLOR</code>: basic point color
  * <code>EDGE_WIDTH</code>: basic edge width
  * <code>EDGE_COLOR</code>: basic edge color
  * <code>EMST_EDGE_WIDTH</code>: Euclidian Minimum Spanning Tree edge width
  * <code>EMST_EDGE_COLOR</code>: Euclidian Minimum Spanning Tree basic edge color
  * <code>DUAL_EDGE_WIDTH</code>: Voronoi diagram edge width
  * <code>DUAL_EDGE_COLOR</code>: Voronoi diagram edge color
  * <code>CIRCLES_WIDTH</code>: circles width
  * <code>CIRCLES_WIDTH</code>: circles color
  * <code>CIRCLES_CENTER_WIDTH</code>: center of circles width
  * <code>CIRCLES_CENTER_COLOR</code>: center of circles color
  * <code>CIRCLES_RESOLUTION</code>: number of points for visualizing a circle

Finally, here is a description of the only parameter concerning Voronoi diagrams: 
  * <code>X_MARGIN</code>: x coordinate of the "infinite" vertex of a Voronoi diagram, must be great in absolute value compared to the maximum x coordinate of the set of points


