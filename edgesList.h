#include <iostream>
#include <string>
using namespace std;

// EDGE STRUCT
// shows connection to another vertex
struct Edge {
    int data;
    Edge* next;
    // Constructor
    Edge(const int val) {
        this->data = val;
        this->next = nullptr;   
    }
};

// EDGES LIST CLASS
// Linked list specifically for storing edges (connections)
class EdgesList {
private:
    Edge* head;
    int size;

public:
    // Constructor
    EdgesList(){
        this->head = nullptr;
        this->size = 0;
    }
    
    // Destructor
    ~EdgesList() {
        while (head) {
            Edge* temp = head;
            head = head->next;
            delete temp;
        }
    }
    // function to insert a new element at the beginning
    void insert(const int val) {
        Edge* newEdge = new Edge(val);
        newEdge->next = head;
        head = newEdge;
        size++;
    }
    
    // function to check if the list contains a value
    bool search(const int val) const {
        Edge* curr = head;
        while (curr) {
            if (curr->data == val) return true;
            curr = curr->next;
        }
        return false;
    }
    
    // function to display the list
    void display() const {
        Edge* curr = head;
        while (curr) {
            cout << curr->data;
            if (curr->next) cout << ", ";
            curr = curr->next;
        }
    }
    
    // getter for head
    Edge* getHead() const { 
        return head; 
    }

    // getter for size
    int getSize() const { 
        return size; 
    }

    // function to check if the list is empty
    bool isEmpty() const { 
        return head == nullptr; 
    }
};