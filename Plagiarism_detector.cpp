// Plagiarism_detector.h
#ifndef PLAGIARISM_DETECTOR_H
#define PLAGIARISM_DETECTOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>

using namespace std;

const int HASH_SIZE = 1000;
// Simple hash map implementation
class HashMap {
    struct Node {
        string key;
        int value;
        Node* next;
        Node(string k, int v) : key(k), value(v), next(nullptr) {}
    };
    Node* table[HASH_SIZE];

    int hashFunction(const string& key) {
        int hash = 0;
        for (char c : key) hash = (hash * 31 + c) % HASH_SIZE;
        return hash;
    }

public:
    HashMap() {
        for (int i = 0; i < HASH_SIZE; i++) table[i] = nullptr;
    }

    void insert(const string& key) {
        int idx = hashFunction(key);
        Node* node = table[idx];
        while (node) {
            if (node->key == key) {
                node->value++;
                return;
            }
            node = node->next;
        }
        Node* newNode = new Node(key, 1);
        newNode->next = table[idx];
        table[idx] = newNode;
    }

    int get(const string& key) {
        int idx = hashFunction(key);
        Node* node = table[idx];
        while (node) {
            if (node->key == key) return node->value;
            node = node->next;
        }
        return 0;
    }

    vector<string> getAllKeys() {
        vector<string> keys;
        for (int i = 0; i < HASH_SIZE; i++) {
            Node* node = table[i];
            while (node) {
                keys.push_back(node->key);
                node = node->next;
            }
        }
        return keys;
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

float jaccardSimilarity(const string& ngram1, const string& ngram2) {
    vector<string> words1, words2;
    stringstream ss1(ngram1), ss2(ngram2);
    string word;

    while (ss1 >> word) words1.push_back(word);
    while (ss2 >> word) words2.push_back(word);

    int intersection = 0, unionSize = words1.size() + words2.size();

    for (const string& w1 : words1) {
        for (size_t i = 0; i < words2.size(); i++) {
            if (w1 == words2[i]) {
                intersection++;
                words2[i] = ""; // Mark as used
                break;
            }
        }
    }

    return unionSize == 0 ? 0.0 : float(intersection) / (unionSize - intersection);
}

 //Function to calculate plagiarism percentage
float calculatePlagiarism(HashMap& sourceMap, const list<string>& targetNgrams, float threshold = 0.8) {
    int matches = 0; // Total matching N-grams
    int totalTargetNgrams = targetNgrams.size(); // Total target N-grams

    vector<string> sourceKeys = sourceMap.getAllKeys(); // All source N-grams
    for (const string& target : targetNgrams) {
        bool matchFound = false;
        for (const string& source : sourceKeys) {
            if (jaccardSimilarity(target, source) >= threshold) {
                matchFound = true;
                break; // Stop comparing after the first match
            }
        }
        if (matchFound) matches++;
    }

    return totalTargetNgrams == 0 ? 0.0 : (float(matches) / totalTargetNgrams) * 100; 
}

// Function to filter out common words
vector<string> filterCommonWords(const vector<string> &tokens, const vector<string> &commonWords) {
    vector<string> filteredTokens;
    for (const string &token : tokens) {
        bool isCommon = false;
        for (const string &commonWord : commonWords) {
            if (token == commonWord) {
                isCommon = true;
                break;
            }
        }
        if (!isCommon) {
            filteredTokens.push_back(token);
        }
    }
    return filteredTokens;
}

void displayMenu() {
    cout << "======== MENU ========\n";
    cout << "1. Analyze Plagiarism\n";
    cout << "2. Set N-gram Size\n";
    cout << "3. Set Similarity Threshold\n";
    cout << "4. Choose Files\n";
    cout << "5. Exit\n";
    cout << "======================\n";
    cout << "Enter your choice: ";
}

void PD_menu() {
    int n = 3; // Default N-gram size
    float threshold = 0.8; // Default similarity threshold
    string sourceFile = "source.txt";
    string targetFile = "target.txt";

    while (true) {
        displayMenu();

        int choice;
        cin >> choice;

        if (choice == 1) {
            // Read source and target files
            string sourceText = readFile(sourceFile);
            string targetText = readFile(targetFile);

            if (sourceText.empty() || targetText.empty()) {
                cout << "Error reading files. Please check the file paths.\n";
                continue;
            }

            // Define common words
            vector<string> commonWords = {"the", "is", "a", "an", "and", "or", "in", "on", "at", "this", "that", "with", "to", "for", "of"};

            // Tokenize text and filter common words
            vector<string> sourceTokens = filterCommonWords(tokenize(sourceText), commonWords);
            vector<string> targetTokens = filterCommonWords(tokenize(targetText), commonWords);

            // Generate N-grams
            list<string> sourceNgrams = generateNgrams(sourceTokens, n);
            list<string> targetNgrams = generateNgrams(targetTokens, n);

            // Create hash map for source N-grams
            HashMap sourceMap;
            for (const string& ngram : sourceNgrams) {
                sourceMap.insert(ngram);
            }

            // Calculate plagiarism percentage
            float plagiarismPercentage = calculatePlagiarism(sourceMap, targetNgrams, threshold);
            cout << "Plagiarism Percentage: " << plagiarismPercentage << "%\n";

        } else if (choice == 2) {
            cout << "Enter new N-gram size: ";
            cin >> n;
            if (n <= 0) {
                cout << "Invalid N-gram size. Must be greater than 0.\n";
                n = 3; // Reset to default
            }

        } else if (choice == 3) {
            cout << "Enter new similarity threshold (0.0 to 1.0): ";
            cin >> threshold;
            if (threshold < 0.0 || threshold > 1.0) {
                cout << "Invalid threshold. Must be between 0.0 and 1.0.\n";
                threshold = 0.8; // Reset to default
            }

        } else if (choice == 4) {
            cout << "Enter path to source file: ";
            cin >> sourceFile;
            cout << "Enter path to target file: ";
            cin >> targetFile;
            
            // Test file paths
            string testSource = readFile(sourceFile);
            string testTarget = readFile(targetFile);

            if (testSource.empty() || testTarget.empty()) {
                cout << "Error reading files. Reverting to previous file paths.\n";
            } else {
                cout << "Files successfully updated.\n";
            }

        } else if (choice == 5) {
            cout << "Exiting program. Goodbye!\n";
            break;

        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    PD_menu();
    return 0;
}


#endif // PLAGIARISM_DETECTOR_H