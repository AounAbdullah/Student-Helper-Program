#include <iostream>
#include <fstream>
#include <sstream>

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