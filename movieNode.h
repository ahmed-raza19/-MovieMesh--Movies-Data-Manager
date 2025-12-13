#pragma once
#include "linkedList.h"
#include <string>
#include <iostream>
using namespace std;

class MovieNode {
public:
    string title;
    string director;
    int year;
    double rating;
    int duration;

    LinkedList* actors;
    LinkedList* genres;
    
    MovieNode();
    ~MovieNode();
    void display() const;
    void addActor(const string actor);
    void addGenre(const string genre);
};