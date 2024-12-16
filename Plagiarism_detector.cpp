#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>

using namespace std;
// Simple hash map implementation
class HashMap {
private:
    static const int TABLE_SIZE = 1000;
    vector<pair<string, int>> table[TABLE_SIZE];

    int hashFunction(const string &key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % TABLE_SIZE;
        }
        return hash;
    }

public:
    void insert(const string &key) {
        int hashIndex = hashFunction(key);
        for (auto &entry : table[hashIndex]) {
            if (entry.first == key) {
                entry.second++;
                return;
            }
        }
        table[hashIndex].emplace_back(key, 1);
    }

    int getFrequency(const string &key) {
        int hashIndex = hashFunction(key);
        for (const auto &entry : table[hashIndex]) {
            if (entry.first == key) {
                return entry.second;
            }
        }
        return 0;
    }
};

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

// Function to generate N-grams from tokens using a linked list
list<string> generateNgrams(const vector<string> &tokens, int n) {
    list<string> ngrams;
    for (size_t i = 0; i + n <= tokens.size(); ++i) {
        string ngram;
        for (int j = 0; j < n; ++j) {
            ngram += (j > 0 ? " " : "") + tokens[i + j];
        }
        ngrams.push_back(ngram);
    }
    return ngrams;
}

/* Function to calculate plagiarism percentage
float calculatePlagiarism(HashMap &sourceMap, const list<string> &targetNgrams) {
    int matches = 0;
    for (const string &ngram : targetNgrams) {
        if (sourceMap.getFrequency(ngram) > 0) {
            matches++;
        }
    }
    return (float(matches) / targetNgrams.size()) * 100;
}*/