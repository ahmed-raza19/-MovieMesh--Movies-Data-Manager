#include <iostream>
using namespace std;

// Node struct for queue
struct QueueNode {
    int data;
    QueueNode* next;
    
    QueueNode(int val) : data(val), next(nullptr) {}
};

// Queue class
class Queue {
private:
    QueueNode* front;
    QueueNode* rear;
    int size;

public:
    // Constructor
    Queue() : front(nullptr), rear(nullptr), size(0) {}
    
    // Destructor
    ~Queue() {
        while (front) {
            QueueNode* temp = front;
            front = front->next;
            delete temp;
        }
    }
    
    // Enqueue - add element at rear
    void enqueue(int val) {
        QueueNode* newNode = new QueueNode(val);
        
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }
    
    // Dequeue - remove element from front
    int dequeue() {
        if (front == nullptr) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        
        QueueNode* temp = front;
        int data = temp->data;
        front = front->next;
        delete temp;
        size--;
        
        if (front == nullptr) {
            rear = nullptr;
        }
        
        return data;
    }
    
    // Peek - view front element
    int peek() const {
        if (front == nullptr) {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        return front->data;
    }
    
    // Check if empty
    bool isEmpty() const {
        return front == nullptr;
    }
    
    // Get size
    int getSize() const {
        return size;
    }
};