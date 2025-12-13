#ifndef LINKEDLIST_H 
#define LINKEDLIST_H 

#include <iostream>
#include <string>
using namespace std;

struct node
{
    string data;
    node *next;
    // Constructor
    node(string val = "")
    {
        this->data = val;
        this->next = nullptr;
    }
};

class LinkedList
{
private:
    node *head;
    int size;

public:
    // Constructor
    LinkedList()
    {
        this->head = nullptr;
        this->size = 0;
    }

    // Destructor
    ~LinkedList()
    {
        while (head)
        {
            node *temp = head;
            head = head->next;
            delete temp;
        }
    }

    // function to insert at head
    void insert(string val)
    {
        node *newNode = new node(val);
        newNode->next = head;
        head = newNode;
        size++;
    }

    // function to check if the list contains a value
    bool search(string val) const
    {
        node *curr = head;

        // iterating through the list
        while (curr)
        {
            // if value found
            if (curr->data == val)
                return true;
            curr = curr->next;
        }
        return false;
    }

    // function to display the list
    void display() const
    {
        node *curr = head;
        while (curr)
        {
            // Display with color - cyan for data
            cout << "\033[36m" << curr->data << "\033[0m";

            // printing comma if not last element - white comma
            if (curr->next)
                cout << "\033[37m, \033[0m";
            curr = curr->next;
        }
    }

    // getter for head
    node *getHead() const
    {
        return head;
    }

    // getter for size
    int getSize() const
    {
        return size;
    }

    // function to check if the list is empty
    bool isEmpty() const
    {
        return head == nullptr;
    }
};

#endif