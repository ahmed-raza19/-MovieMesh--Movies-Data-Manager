#pragma once
#include "MovieNode.h"
#include <iostream>
#include <cstring>
using namespace std;

// MOVIE LIST NODE 
// Node that stores a pointer to a movie
struct ListNode {
    MovieNode* movie;          // Pointer to the actual movie
    ListNode* next;       // Pointer to next node
    
    ListNode(MovieNode* m){
        this->movie = m;
        this->next = nullptr;
    }
};

// MOVIE LIST CLASS 
// Linked list specifically for storing movies
class MovieList {
private:
    ListNode* head;
    int size;

public:
    // Constructor
    MovieList() : head(nullptr), size(0) {}
    
    // Destructor
    ~MovieList() {
        while (head) {
            ListNode* temp = head;
            head = head->next;
            delete temp;  
        }
    }
    
    // Inserting movie at beginning
    void insert(MovieNode* movie) {
        ListNode* newNode = new ListNode(movie);
        newNode->next = head;
        head = newNode;
        size++;
    }
    
    // Checking if movie exists
    bool search(MovieNode* movie) {
        ListNode* curr = head;
        while (curr) {
            if (curr->movie->title == movie->title) {
                return true;
            }
            curr = curr->next;
        }
        return false;
    }
    
    // Displaying all movies
    void display() {
        ListNode* curr = head;
        while (curr) {
            curr->movie->display();
            curr = curr->next;
        }
    }
    
    // Getter for head
    ListNode* getHead() const {
        return head;
    }
    
    // Getter for size
    int getSize() const {
        return size;
    }
    
    // Check if empty
    bool isEmpty() const {
        return head == nullptr;
    }
};