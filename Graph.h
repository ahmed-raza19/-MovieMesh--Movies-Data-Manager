#include "MovieNode.h"
#include "LinkedList.h"
#include "edgesList.h"
#include <iostream>

// GRAPH NODE
// Represents ONE movie in the graph
struct GraphNode {
    MovieNode* movie;          // Pointer to the movie
    EdgesList* edges;     // List of connected movie indices
    
    GraphNode(MovieNode* m) : movie(m), edges(nullptr){}
};

// GRAPH CLASS
class Graph {
private:
    GraphNode** vertices;      // Array of all movies
    int vertexCount;           // How many movies we've added
    int capacity;              // Maximum capacity
    
    // Helper: Check if two movies share actors or genres
    bool shareAttributes(MovieNode* m1, MovieNode* m2);
    
    // Helper: Find movie index by title
    int findIndex(const string& title);
    
    // Helper: BFS for shortest path
    bool bfsPath(int start, int end, int* parent);
    
public:
    Graph(int cap = 5000);
    ~Graph();
    
    void addMovie(MovieNode* movie);
    void buildGraph();
    void recommendBFS(const string& title, int count = 5);
    void shortestPath(const string& title1, const string& title2);
};