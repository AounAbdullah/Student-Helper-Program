#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// This function is being implemented to read a file and return its contents in the form of a string 
string readFile(const string &filename) {
    ifstream file(filename);

    if(!file.is_open()) {
        cout << "Error! Could not open File " <<filename<<endl;
        return "";
    }

    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Function to tokenize text into words
vector<string> tokenize(const string &text) {
    vector<string> tokens;
    string word;
    for (char c : text) {
        if (isalnum(c)) {
            word += tolower(c);
        } else if (!word.empty()) {
            tokens.push_back(word);
            word.clear();
        }
    }
    if (!word.empty()) {
        tokens.push_back(word);
    }
    return tokens;
}