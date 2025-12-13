#pragma once
#include <string>
using namespace std;

class Parser {
public:
    // Extract specific fields from CSV line
    static void extractTitle(const string& line, string& title);
    static void extractDirector(const string& line, string& director);
    static void extractYear(const string& line, int& year);
    static void extractRating(const string& line, double& rating);
    static void extractDuration(const string& line, int& duration);
    static void extractGenres(const string& line, string genres[], int& count);
    static void extractActors(const string& line, string actors[], int& count);
    
private:
    // Helper functions
    static string getNthField(const string& line, int n);
    static int parseInt(const string& str);
    static double parseDouble(const string& str);
    static void removeSpecialChar(string& str);
    static bool isValidNumber(const string& str);

};