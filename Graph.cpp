#include "Graph.h"
#include "queue.h"
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

// Constructor
Graph::Graph(int cap){
    this->capacity = cap;
    this->vertexCount = 0;
    vertices = new GraphNode*[capacity];
    // Initialize all vertices to nullptr
    for (int i = 0; i < capacity; i++) {
        vertices[i] = nullptr;
    }
}

// Destructor
Graph::~Graph() {
    // Deleting all graph nodes and their edges
    for (int i = 0; i < vertexCount; i++) {
        if (vertices[i]) {
            delete vertices[i]->edges;
            delete vertices[i];
        }
    }
    delete[] vertices;
}

// Add a movie to the graph
void Graph::addMovie(MovieNode* movie) {
    // Prevent adding more than capacity
    if (vertexCount >= capacity) 
        return;
    
    // Creating new GraphNode and adding to vertices array
    vertices[vertexCount] = new GraphNode(movie);
    vertices[vertexCount]->edges = new EdgesList();
    vertexCount++;
}

// Helper: Find movie index by title
int Graph::findIndex(const string& title) {
    // iterate through vertices to find the movie
    for (int i = 0; i < vertexCount; i++) {
        if (vertices[i]->movie->title == title) {
            return i;
        }
    }
    // if not found, return -1
    return -1;
}

// Helper: Check if two movies share actors or genres
bool Graph::shareAttributes(MovieNode* m1, MovieNode* m2) {

    // First Checking if they share any genres
    node* genre1 = m1->genres->getHead();
    while (genre1) {
        if (m2->genres->search(genre1->data)) {
            return true;
        }
        genre1 = genre1->next;
    }

    // Then Checking if they share any actors
    node* actor1 = m1->actors->getHead();
    while (actor1) {
        if (m2->actors->search(actor1->data)) {
            return true;
        }
        actor1 = actor1->next;
    }
    
    return false;
}

// Build the graph by connecting movies that share attributes
void Graph::buildGraph() {

    // Comparing each pair of movies
    for (int i = 0; i < vertexCount; i++) {
        for (int j = i + 1; j < vertexCount; j++) {

            // If they share actors or genres, creating an edge
            if (shareAttributes(vertices[i]->movie, vertices[j]->movie)) {
                vertices[i]->edges->insert(j);
                vertices[j]->edges->insert(i);
            }
        }
    }
}

// Helper: BFS to find shortest path
bool Graph::bfsPath(int start, int end, int* parent) {
    bool* visited = new bool[vertexCount];

    // Initialize visited and parent arrays
    for (int i = 0; i < vertexCount; i++) {
        visited[i] = false;
        parent[i] = -1;
    }
    
    Queue *q = new Queue();
    q->enqueue(start);
    visited[start] = true;
    
    while (!q->isEmpty()) {
        // Dequeue a vertex
        int curr = q->peek();
        q->dequeue();
        
        // If we reached the end movie
        if (curr == end) {
            delete[] visited;
            return true;
        }
        
        // Explore neighbors
        Edge* edge = vertices[curr]->edges->getHead();

        // Traverse all adjacent vertices
        while (edge) {
            int neighbor = edge->data;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = curr;
                q->enqueue(neighbor);
            }
            edge = edge->next;
        }
    }
    
    delete[] visited;
    return false;
}

// Recommend movies using BFS (breadth-first)
void Graph::recommendBFS(const string& title, int count) {
    // Find starting movie index
    int startIdx = findIndex(title);

    // If movie not found
    if (startIdx == -1) {
        cout << "\033[1;31mMovie not found!\033[0m" << endl;
        return;
    }
    
    bool* visited = new bool[vertexCount];

    // Initialising visited array
    for (int i = 0; i < vertexCount; i++) {
        visited[i] = false;
    }
    
    Queue *q = new Queue();
    q->enqueue(startIdx);
    visited[startIdx] = true;
    
    cout << "\033[1;35m\n=== BFS Movie Recommendations for: \033[36m" << title << "\033[1;35m ===\033[0m" << endl;
    int recommended = 0;
    
    // BFS traversal
    while (!q->isEmpty() && recommended < count) {
        int curr = q->peek();
        q->dequeue();
        
        // Skip the starting movie itself
        if (curr != startIdx) {
            vertices[curr]->movie->display();
            recommended++;
        }
        
        // Exploring neighbors
        Edge* edge = vertices[curr]->edges->getHead();

        // Traversing all adjacent vertices
        while (edge && recommended < count) {
            int neighbor = edge->data;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q->enqueue(neighbor);
            }
            edge = edge->next;
        }
    }
    
    delete[] visited;
}

// Find shortest path between two movies
void Graph::shortestPath(const string& title1, const string& title2) {
    int startIdx = findIndex(title1);
    int endIdx = findIndex(title2);
    
    // Checking if both movies exist
    if (startIdx == -1 || endIdx == -1) {
        cout << "\033[1;31mOne or both movies not found!\033[0m" << endl;
        return;
    }
    
    // Array to store the parent of each node in the path
    int* parent = new int[vertexCount];
    
    // Performing BFS to find the path
    if (!bfsPath(startIdx, endIdx, parent)) {
        cout << "\033[1;31mNo path exists between these movies!\033[0m" << endl;
        delete[] parent;
        return;
    }
    
    // Reconstructing path
    int* path = new int[vertexCount];
    int pathLen = 0;
    int curr = endIdx;
    
    // Backtracking from end to start using parent array
    while (curr != -1) {
        path[pathLen++] = curr;
        curr = parent[curr];
    }
    
    cout << "\033[1;35m\n=== Shortest Path from \033[36m" << title1 << "\033[1;35m to \033[36m" << title2 << "\033[1;35m ===\033[0m" << endl;
    cout << "\033[1;33mPath length: \033[36m" << pathLen << "\033[1;33m movies\033[0m" << endl;
    
    // Displaying the path in correct order
    for (int i = pathLen - 1; i >= 0; i--) {
        cout << "\033[36m" << vertices[path[i]]->movie->title << "\033[0m";
        if (i > 0) cout << "\033[1;35m -> \033[0m";
    }
    cout << endl;
    
    delete[] parent;
    delete[] path;
}