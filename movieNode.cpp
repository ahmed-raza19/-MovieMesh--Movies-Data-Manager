#include "MovieNode.h"
#include <iostream>
using namespace std;

// Constructor
MovieNode::MovieNode() {
    title = "";
    director = "";
    year = 0;
    rating = 0.0;
    duration = 0;

    actors = new LinkedList();
    genres = new LinkedList();
}

// Destructor
MovieNode::~MovieNode() {
    delete actors;
    delete genres;
}

// Add an actor to the actors list
void MovieNode::addActor(const string actor) {
    // if already exists, do not add
    if (actors->search(actor)) 
        return;
    
    actors->insert(actor);
}

void MovieNode::addGenre(const string genre) {
    // if already exists, do not add
    if (genres->search(genre)) 
        return;
    
    genres->insert(genre);
}

void MovieNode::display() const {
    cout << "\033[1;33m\n=== Movie Details ===\033[0m" << endl;
    cout << "\033[1;32mTitle: \033[36m" << title << "\033[0m" << endl;
    cout << "\033[1;32mDirector: \033[36m" << director << "\033[0m" << endl;
    cout << "\033[1;32mYear: \033[36m" << year << "\033[0m" << endl;
    cout << "\033[1;32mRating: \033[36m" << rating << "\033[0m" << endl;
    cout << "\033[1;32mDuration: \033[36m" << duration << "\033[0m\033[1;32m min\033[0m" << endl;
    cout << "\033[1;32mGenres: \033[0m";
    genres->display();
    cout << "\n\033[1;32mActors: \033[0m";
    actors->display();
    cout << "\033[0m" << endl;
}