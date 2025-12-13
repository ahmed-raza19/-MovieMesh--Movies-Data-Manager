#include <iostream>
#include "linkedList.h"
#include "MovieNode.h"
#include "Parser.h"
#include "AVL.h"
#include "Graph.h"
#include "HashTable.h"
#include <fstream>
#include <cstring>
using namespace std;

// ANSI Color Codes
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BG_BLUE "\033[44m"

// Global data structures
AVLTree movieTree;
HashTable actorTable;
HashTable genreTable;
Graph graph;
int movieCount = 0;

// Helper function to print centered text
void printCentered(const string& text, int width = 60) {
    int padding = (width - text.length()) / 2;
    for (int i = 0; i < padding; i++) cout << " ";
    cout << text << endl;
}

// Helper function to print box border
void printBox(int width = 60) {
    cout << CYAN;
    for (int i = 0; i < width; i++) cout << "=";
    cout << RESET << endl;
}

void printBoxBottom(int width = 60) {
    cout << CYAN;
    for (int i = 0; i < width; i++) cout << "=";
    cout << RESET << endl;
}

// LOAD DATASET 
void loadDataset(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << RED << "Error: Cannot open " << filename << RESET << endl;
        return;
    }
    
    char line[5000];
    file.getline(line, 5000);  // Skip header
    
    cout << "\n" << YELLOW << "Loading movies from dataset..." << RESET << endl;
    
    while (file.getline(line, 5000) && movieCount < 5045) {
        MovieNode* movie = new MovieNode();
        
        // Extract title
        Parser::extractTitle(line, movie->title);
        if (movie->title == "") {
            delete movie;
            continue;
        }
        
        // Extract other fields
        Parser::extractDirector(line, movie->director);
        Parser::extractYear(line, movie->year);
        Parser::extractRating(line, movie->rating);
        Parser::extractDuration(line, movie->duration);
        
        // Extract genres
        string genres[10];
        int genreCount;
        Parser::extractGenres(line, genres, genreCount);
        for (int i = 0; i < genreCount; i++) {
            movie->addGenre(genres[i]);
            genreTable.insert(genres[i], movie);
        }
        
        // Extract actors
        string actors[3];
        int actorCount;
        Parser::extractActors(line, actors, actorCount);
        for (int i = 0; i < actorCount; i++) {
            movie->addActor(actors[i]);
            actorTable.insert(actors[i], movie);
        }
        
        // Add to structures
        movieTree.insert(movie);
        graph.addMovie(movie);
        movieCount++;
        
        if (movieCount % 100 == 0) {
            cout << GREEN << "  Loaded " << movieCount << " movies..." << RESET << endl;
        }
    }
    
    file.close();
    cout << "\n" << GREEN << BOLD << "Total movies loaded: " << movieCount << RESET << endl;
    
    // Build graph connections
    cout << YELLOW << "Building movie relationship graph..." << RESET << endl;
    graph.buildGraph();
    cout << GREEN << BOLD << "System ready!" << RESET << endl;
}

// ===== SEARCH BY TITLE =====
void searchByTitle() {
    cout << "\n" << CYAN << BOLD << "SEARCH BY TITLE" << RESET << endl;
    printBox(60);
    
    char title[300];
    cout << YELLOW << "Enter movie title: " << RESET;
    cin.ignore();
    cin.getline(title, 300);
    
    MovieNode* movie = movieTree.search(title);
    if (movie) {
        cout << GREEN << "\nMovie found!" << RESET << endl;
        movie->display();
    } else {
        cout << RED << "\nMovie not found!" << RESET << endl;
    }
}

// ===== SEARCH BY ACTOR =====
void searchByActor() {
    cout << "\n" << CYAN << BOLD << "SEARCH BY ACTOR" << RESET << endl;
    printBox(60);
    
    char actor[200];
    cout << YELLOW << "Enter actor name: " << RESET;
    cin.ignore();
    cin.getline(actor, 200);
    
    cout << "\n" << MAGENTA << BOLD << "Movies featuring " << actor << RESET << endl;
    actorTable.display(actor);
}

// ===== SEARCH BY GENRE =====
void searchByGenre() {
    cout << "\n" << CYAN << BOLD << "SEARCH BY GENRE" << RESET << endl;
    printBox(60);
    
    char genre[100];
    cout << YELLOW << "Enter genre: " << RESET;
    cin.ignore();
    cin.getline(genre, 100);
    
    cout << "\n" << MAGENTA << BOLD << "Movies in genre: " << genre << RESET << endl;
    genreTable.display(genre);
}

// ===== SEARCH BY YEAR =====
void searchByYear() {
    cout << "\n" << CYAN << BOLD << "SEARCH BY YEAR" << RESET << endl;
    printBox(60);
    
    int year;
    cout << YELLOW << "Enter year: " << RESET;
    cin >> year;
    
    cout << "\n" << MAGENTA << BOLD << "Movies from year " << year << RESET << endl;
    movieTree.searchByYear(year);
}

// ===== SEARCH BY RATING RANGE =====
void searchByRating() {
    cout << "\n" << CYAN << BOLD << "SEARCH BY RATING" << RESET << endl;
    printBox(60);
    
    double minRating, maxRating;
    cout << YELLOW << "Enter minimum rating: " << RESET;
    cin >> minRating;
    cout << YELLOW << "Enter maximum rating: " << RESET;
    cin >> maxRating;
    
    cout << "\n" << MAGENTA << BOLD << "Movies with rating between " 
         << minRating << " and " << maxRating << RESET << endl;
    movieTree.searchByRating(minRating, maxRating);
}

// ===== RECOMMEND MOVIES (BFS) =====
void recommendBFS() {
    cout << "\n" << CYAN << BOLD << "MOVIE RECOMMENDATIONS" << RESET << endl;
    printBox(60);
    
    char title[300];
    int count;
    
    cout << YELLOW << "Enter movie title for recommendations: " << RESET;
    cin.ignore();
    cin.getline(title, 300);
    
    cout << YELLOW << "How many recommendations (1-10): " << RESET;
    cin >> count;
    if (count < 1) count = 5;
    if (count > 10) count = 10;
    
    graph.recommendBFS(title, count);
}

// ===== SHORTEST PATH =====
void findShortestPath() {
    cout << "\n" << CYAN << BOLD << "SHORTEST CONNECTION PATH" << RESET << endl;
    printBox(60);
    
    char title1[300], title2[300];
    
    cout << YELLOW << "Enter first movie title: " << RESET;
    cin.ignore();
    cin.getline(title1, 300);
    
    cout << YELLOW << "Enter second movie title: " << RESET;
    cin.getline(title2, 300);
    
    graph.shortestPath(title1, title2);
}

// ===== UPDATE MOVIE RATING =====
void updateMovieRating() {
    cout << "\n" << CYAN << BOLD << "UPDATE MOVIE RATING" << RESET << endl;
    printBox(60);
    
    char title[300];
    cout << YELLOW << "Enter movie title to update: " << RESET;
    cin.ignore();
    cin.getline(title, 300);

    MovieNode* movie = movieTree.search(title);
    if (movie) {
        cout << BLUE << "Current Rating: " << RESET << movie->rating << endl;
        cout << YELLOW << "Enter New Rating: " << RESET;
        double newRating;
        cin >> newRating;
        movie->rating = newRating;
        cout << GREEN << "Rating updated successfully!" << RESET << endl;
    } else {
        cout << RED << "\nMovie not found!" << RESET << endl;
    }
}

// ===== DISPLAY ALL MOVIES =====
void displayAllMovies() {
    cout << "\n" << CYAN << BOLD << "ALL MOVIES" << RESET << endl;
    cout << MAGENTA << "Sorted by Title" << RESET << endl;
    printBox(60);
    movieTree.displayAll();
}

// ===== DISPLAY MENU =====
void displayMenu() {
    
    // Header
    printBox(60);
    cout << CYAN << "|" << RESET << BOLD << BLUE << "           MOVIE DATA MANAGER SYSTEM                     " 
         << RESET << CYAN << "|" << RESET << endl;
    cout << CYAN << "|" << RESET << "                  " << YELLOW << "IMDb 5000 Dataset" 
         << RESET << "                      " << CYAN << "|" << RESET << endl;
    printBoxBottom(60);
    
    cout << "\n";
    
    // Menu options
    cout << CYAN << " +-------------------------------------------------------+" << RESET << endl;
    cout << CYAN << " |" << RESET << "  " << GREEN << "1." << RESET << "  Search movie by title                            " << CYAN << "|" << RESET << endl;
    cout << CYAN << " |" << RESET << "  " << GREEN << "2." << RESET << "  Search movies by actor                           " << CYAN << "|" << RESET << endl;
    cout << CYAN << " |" << RESET << "  " << GREEN << "3." << RESET << "  Search movies by genre                           " << CYAN << "|" << RESET << endl;
    cout << CYAN << " |" << RESET << "  " << GREEN << "4." << RESET << "  Search movies by year                            " << CYAN << "|" << RESET << endl;
    cout << CYAN << " |" << RESET << "  " << GREEN << "5." << RESET << "  Search movies by rating range                    " << CYAN << "|" << RESET << endl;
    cout << CYAN << " |" << RESET << "  " << GREEN << "6." << RESET << "  Get movie recommendations (BFS)                  " << CYAN << "|" << RESET << endl;
    cout << CYAN << " |" << RESET << "  " << GREEN << "7." << RESET << "  Find shortest connection between movies          " << CYAN << "|" << RESET << endl;
    cout << CYAN << " |" << RESET << "  " << GREEN << "8." << RESET << "  Update movie rating                              " << CYAN << "|" << RESET << endl;
    cout << CYAN << " |" << RESET << "  " << GREEN << "9." << RESET << "  Display all movies                               " << CYAN << "|" << RESET << endl;
    cout << CYAN << " |" << RESET << "  " << RED << "0." << RESET << "  Exit                                             " << CYAN << "|" << RESET << endl;
    cout << CYAN << " +-------------------------------------------------------+" << RESET << endl;
    
    cout << "\n" << YELLOW << BOLD << "> Enter your choice: " << RESET;
}

// ===== MAIN FUNCTION =====
int main() {
    
    
    // Welcome screen
    cout << "\n\n";
    printBox(60);
    cout << CYAN << "|" << RESET << BOLD << MAGENTA << "                    WELCOME TO                           " 
         << RESET << CYAN << "|" << RESET << endl;
    cout << CYAN << "|" << RESET << BOLD << BLUE << "            MOVIE DATA MANAGER SYSTEM                    " 
         << RESET << CYAN << "|" << RESET << endl;
    printBoxBottom(60);
    cout << "\n";
    
    // Load the dataset
    loadDataset("movie_metadata.csv");
    
    cout << "\n" << GREEN << "Press any key to continue..." << RESET;
    cin.get();
    
    int choice;
    
    // Main menu loop
    while (true) {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                searchByTitle();
                break;
                
            case 2:
                searchByActor();
                break;
                
            case 3:
                searchByGenre();
                break;
                
            case 4:
                searchByYear();
                break;
                
            case 5:
                searchByRating();
                break;
                
            case 6:
                recommendBFS();
                break;
                
            case 7:
                findShortestPath();
                break;
                
            case 8:
                updateMovieRating();
                break;

            case 9:
                displayAllMovies();
                break;
                
            case 0:
                cout << "\n\n";
                printBox(60);
                cout << CYAN << "|" << RESET << BOLD << GREEN << "        Thank you for using Movie Manager!               " 
                     << RESET << CYAN << "|" << RESET << endl;
                cout << CYAN << "|" << RESET << "                    " << YELLOW << "Goodbye!" 
                     << RESET << "                           " << CYAN << "|" << RESET << endl;
                printBoxBottom(60);
                cout << "\n";
                return 0;
                
            default:
                cout << RED << "\nInvalid choice! Please enter a number between 0-9." << RESET << endl;
        }
        
        // Pause before showing menu again
        cout << "\n" << YELLOW << "Press any key to to continue or 'E' to exit... " << RESET;
        char exitChoice;
        cin >> exitChoice;
        if (exitChoice == 'E' || exitChoice == 'e')
            return 0;
    }
    
    return 0;
}