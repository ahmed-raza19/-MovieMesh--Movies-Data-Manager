#include "Parser.h"

// ===== HELPER: GET NTH FIELD FROM CSV =====
string Parser::getNthField(const string& line, int n) {
    int fieldIndex = 0;
    int start = 0;
    bool inQuotes = false;
    string result = "";
    
    // Iterate through the line character by character
    for (int i = 0; i <= line.length(); i++) {
        // Handle quotes
        if (line[i] == '"') {
            inQuotes = !inQuotes;
        }
        // Field delimiter
        else if ((line[i] == ',' && !inQuotes) || i == line.length()) {
            if (fieldIndex == n) {
                // Found our field! Extract it
                for (int j = start; j < i; j++) {
                    if (line[j] != '"') {
                        result += line[j];
                    }
                }
                return result;
            }
            fieldIndex++;   // Move to next field
            start = i + 1;
        }
    }
    return "";  // Field not found
}

// ===== CHECK IF STRING IS A VALID NUMBER =====
bool Parser::isValidNumber(const string& str) {
    if (str.empty()) return false;
    
    // Check for "NaN", "nan", "N/A", "null", empty
    if (str == "NaN" || str == "nan" || str == "N/A" || 
        str == "null" || str == "NULL" || str == "na") {
        return false;
    }
    
    // Check if contains at least one digit
    bool hasDigit = false;
    for (char c : str) {
        if (c >= '0' && c <= '9') {
            hasDigit = true;
            break;
        }
    }
    return hasDigit;
}

// ===== CONVERT STRING TO INTEGER =====
int Parser::parseInt(const string& str) {
    if (str.empty()) 
        return 0;

    if(!isValidNumber(str))
        return 0;
    
    int result = 0;
    int i = 0;
    bool negative = false;
    
    if (str[0] == '-') {
        negative = true;
        i = 1;
    }
    
    while (i < str.length()) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        }
        i++;
    }
    
    // make positive if needed
    return negative ? -result : result;
}

// ===== CONVERT STRING TO DOUBLE =====
double Parser::parseDouble(const string& str) {
    if (str.empty()) return 0.0;

    if(!isValidNumber(str))
        return 0.0;
    
    double result = 0.0;
    double fraction = 0.0;
    bool afterDecimal = false;
    int decimalPlaces = 0;
    int i = 0;
    bool negative = false;
    
    if (str[0] == '-') {
        negative = true;
        i = 1;
    }
    
    while (i < str.length()) {
        if (str[i] == '.') {
            afterDecimal = true;
        }
        else if (str[i] >= '0' && str[i] <= '9') {
            
            if (afterDecimal) { // processing fractional part
                fraction = fraction * 10 + (str[i] - '0');
                decimalPlaces++;
            } 
            else { // processing integer part
                result = result * 10 + (str[i] - '0');
            }
        }
        i++;
    }
    // Adjust fraction based on decimal places
    for (int j = 0; j < decimalPlaces; j++) {
        fraction /= 10.0;
    }
    
    result += fraction;
    return negative ? -result : result;
}

// REMOVE SPECIAL CHARACTER (�) 
void Parser::removeSpecialChar(string& str) {
    string clean = "";

    for (char c : str) {
        // Uppercase
        if (c >= 'A' && c <= 'Z') {
            clean += c;
        }
        // Lowercase
        else if (c >= 'a' && c <= 'z') {
            clean += c;
        }
        // Digits
        else if (c >= '0' && c <= '9') {
            clean += c;
        }
        // Allowed symbols (added comma)
        else if (c == ' ' || c == ':' || c == '-' || c == '.' || c == ',') {
            clean += c;
        }
        // Otherwise skip
    }

    str = clean;
}


// ===== EXTRACT TITLE (Column 11) =====
void Parser::extractTitle(const string& line, string& title) {
    title = getNthField(line, 11);
    removeSpecialChar(title);
}

// ===== EXTRACT DIRECTOR (Column 1) =====
void Parser::extractDirector(const string& line, string& director) {
    director = getNthField(line, 1);
}

// ===== EXTRACT YEAR (Column 23) =====
void Parser::extractYear(const string& line, int& year) {
    string temp = getNthField(line, 23);
    year = parseInt(temp);
}

// ===== EXTRACT RATING (Column 25) =====
void Parser::extractRating(const string& line, double& rating) {
    string temp = getNthField(line, 25);
    rating = parseDouble(temp);
}

// ===== EXTRACT DURATION (Column 3) =====
void Parser::extractDuration(const string& line, int& duration) {
    string temp = getNthField(line, 3);
    duration = parseInt(temp);
}

// ===== EXTRACT GENRES (Column 9, split by |) =====
void Parser::extractGenres(const string& line, string genres[], int& count) {
    string temp = getNthField(line, 9);
    
    count = 0;
    string current = "";
    
    for (int i = 0; i <= temp.length(); i++) {
        if (temp[i] == '|' || i == temp.length()) {
            if (!current.empty()) {
                genres[count++] = current;
                current = "";
            }
        } else {
            current += temp[i];
        }
    }
}

// ===== EXTRACT ACTORS (Columns 10, 6, 14) =====
void Parser::extractActors(const string& line, string actors[], int& count) {
    count = 0;
    
    // Actor 1 (column 10)
    string actor = getNthField(line, 10);
    if (!actor.empty()) {
        actors[count++] = actor;
    }
    
    // Actor 2 (column 6)
    actor = getNthField(line, 6);
    if (!actor.empty()) {
        actors[count++] = actor;
    }
    
    // Actor 3 (column 14)
    actor = getNthField(line, 14);
    if (!actor.empty()) {
        actors[count++] = actor;
    }
}