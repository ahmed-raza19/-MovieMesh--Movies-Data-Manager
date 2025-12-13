#pragma once
#include "MovieList.h"
#include "MovieNode.h"
#include <cstring>
#include <iostream>
using namespace std;

// HASH NODE
struct HashNode {
    string Name;       // Actor or Genre name
    MovieList movies;       // List of movies
    HashNode* next;
    
    HashNode(const string name) {
        this->Name = name;
        next = nullptr;
    }
};

// HASH TABLE CLASS
class HashTable {
private:
    static const int TABLE_SIZE = 500;
    HashNode* table[TABLE_SIZE];
    
    // Simple hash function (used to get random index)
    int hash(const string& key) {
        int h = 0;
        for (char c : key) {
            h = (h * 31 + c) % TABLE_SIZE;
        }
        return h < 0 ? -h : h;
    }

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }
    
    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            HashNode* curr = table[i];
            while (curr) {
                HashNode* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
    }
    
    // Insert movie for actor name
    void insert(const string& actor_name, MovieNode* movie) {
        int hashId = hash(actor_name);
        HashNode* curr = table[hashId];
        
        // Search for existing actor name
        while (curr) {
            if (curr->Name == actor_name) {
                // Key exists, add movie to its list
                if (!curr->movies.search(movie)) {
                    curr->movies.insert(movie);
                }
                return;
            }
            curr = curr->next;
        }
        
        // Key doesn't exist, create new node
        HashNode* newNode = new HashNode(actor_name);
        newNode->movies.insert(movie);
        newNode->next = table[hashId];
        table[hashId] = newNode;
    }
    
    // Get movie list for actor name
    MovieList* get(const string& actor_name) {
        int hashId = hash(actor_name);
        HashNode* curr = table[hashId];
        
        while (curr) {
            if (curr->Name == actor_name) {
                return &curr->movies;
            }
            curr = curr->next;
        }
        return nullptr;
    }
    
    // Display all movies for an actor
    void display(const string& actor_name) {
        MovieList* list = get(actor_name);
        if (!list || list->isEmpty()) {
            cout << "Not found." << endl;
            return;
        }
        
        list->display();
    }
};