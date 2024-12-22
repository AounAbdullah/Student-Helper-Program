#ifndef PLAGIARISM_DETECTOR_H
#define PLAGIARISM_DETECTOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <ctime>
#include <iomanip>
#include <sys/stat.h>

#ifdef _WIN32
    #include <direct.h>
#endif

using namespace std;

// Structures for storing match and report information
struct MatchInfo {
    string sourceText;
    string targetText;
    float similarity;
    int lineNumber;
};

struct ReportDetails {
    string timestamp;
    string sourceFile;
    string targetFile;
    float plagiarismPercentage;
    vector<MatchInfo> matches;
};

const int HASH_SIZE = 1000;

// HashMap implementation
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
    for (int i = 0; i < HASH_SIZE; i++) {  // Using 'i' instead of undefined 'idx'
        Node* node = table[i];
        while (node) {
            keys.push_back(node->key);
            node = node->next;
        }
    }
    return keys;
}

    ~HashMap() {
        for (int i = 0; i < HASH_SIZE; i++) {
            Node* current = table[i];
            while (current) {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }
    }
};

// Utility functions
int customMax(int a, int b) {
    return (a > b) ? a : b;
}

int customMin(int a, int b) {
    return (a < b) ? a : b;
}

string getCurrentTimestamp() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << setfill('0') 
       << setw(4) << 1900 + ltm->tm_year << "-"
       << setw(2) << 1 + ltm->tm_mon << "-"
       << setw(2) << ltm->tm_mday << " "
       << setw(2) << ltm->tm_hour << ":"
       << setw(2) << ltm->tm_min << ":"
       << setw(2) << ltm->tm_sec;
    return ss.str();
}

string readFile(const string &filename) {
    ifstream file(filename);
    if(!file.is_open()) {
        cout << "Error! Could not open File " << filename << endl;
        return "";
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

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

int getLineNumber(const string& text, const string& phrase) {
    istringstream stream(text);
    string line;
    int lineNum = 1;
    
    while (getline(stream, line)) {
        if (line.find(phrase) != string::npos) {
            return lineNum;
        }
        lineNum++;
    }
    return -1;
}

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

// Analysis functions
bool isVowel(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

void analyzeTextComplexity(const string& text) {
    int words = 0, sentences = 0, syllables = 0;
    string word;
    istringstream stream(text);
    
    while (stream >> word) {
        words++;
        int wordSyllables = 0;
        bool prevVowel = false;
        
        for (size_t i = 0; i < word.length(); i++) {
            bool currentVowel = isVowel(word[i]);
            if (currentVowel && !prevVowel) {
                wordSyllables++;
            }
            prevVowel = currentVowel;
        }
        
        syllables += customMax(1, wordSyllables);
        if (word.find('.') != string::npos || word.find('!') != string::npos || 
            word.find('?') != string::npos) {
            sentences++;
        }
    }
    
    float score = 206.835 - 1.015 * (float(words) / customMax(1, sentences)) 
                        - 84.6 * (float(syllables) / customMax(1, words));
                        
    cout << "\nText Complexity Analysis:\n";
    cout << "Words: " << words << "\n";
    cout << "Sentences: " << sentences << "\n";
    cout << "Syllables: " << syllables << "\n";
    cout << "Flesch Reading Ease Score: " << score << "\n";
    cout << "Interpretation: ";
    if (score > 90) cout << "Very Easy to Read\n";
    else if (score > 80) cout << "Easy to Read\n";
    else if (score > 70) cout << "Fairly Easy to Read\n";
    else if (score > 60) cout << "Standard\n";
    else if (score > 50) cout << "Fairly Difficult\n";
    else cout << "Difficult to Read\n";
}

string replaceChar(const string& str, char find, char replace) {
    string result = str;
    for(size_t i = 0; i < result.length(); i++) {
        if(result[i] == find) {
            result[i] = replace;
        }
    }
    return result;
}

void generateReport(const ReportDetails& report) {
    // Create reports directory if it doesn't exist
    string dirPath = "reports";
    #ifdef _WIN32
        _mkdir(dirPath.c_str());
    #else
        mkdir(dirPath.c_str(), 0777);
    #endif

    // Generate filename with directory path
    string timestamp = replaceChar(report.timestamp, ':', '_');
    string filename = dirPath + "/plagiarism_report_" + timestamp + ".txt";
    
    ofstream reportFile(filename);
    
    if (!reportFile.is_open()) {
        cout << "Error: Could not create report file at " << filename << "\n";
        cout << "Please check if you have write permissions in the directory.\n";
        return;
    }
    
    try {
        reportFile << "=== Plagiarism Detection Report ===\n";
        reportFile << "Generated on: " << report.timestamp << "\n\n";
        reportFile << "Source file: " << report.sourceFile << "\n";
        reportFile << "Target file: " << report.targetFile << "\n";
        reportFile << "Overall plagiarism percentage: " << fixed << setprecision(2) 
                   << report.plagiarismPercentage << "%\n\n";
        
        reportFile << "Detailed matches:\n";
        reportFile << "----------------\n";
        
        if (report.matches.empty()) {
            reportFile << "No significant matches found.\n";
        } else {
            for (size_t i = 0; i < report.matches.size(); i++) {
                const MatchInfo& match = report.matches[i];
                reportFile << "\nMatch " << (i + 1) << ":\n";
                reportFile << "Line " << match.lineNumber << ":\n";
                reportFile << "Source text: \"" << match.sourceText << "\"\n";
                reportFile << "Target text: \"" << match.targetText << "\"\n";
                reportFile << "Similarity: " << fixed << setprecision(2) 
                          << (match.similarity * 100) << "%\n";
            }
        }
        
        reportFile.close();
        cout << "Report successfully generated: " << filename << endl;
        
    } catch (const exception& e) {
        cout << "Error while writing report: " << e.what() << endl;
        reportFile.close();
        remove(filename.c_str()); // Delete incomplete file
    }
}

ReportDetails calculatePlagiarismWithDetails(
    const string& sourceText, const string& targetText,
    HashMap& sourceMap, const list<string>& targetNgrams,
    const string& sourceFileName, const string& targetFileName,  // Add these parameters
    float threshold = 0.8) {
    
    ReportDetails report;
    report.timestamp = getCurrentTimestamp();
    report.sourceFile = sourceFileName;  // Use actual file names
    report.targetFile = targetFileName;
    
    // Rest of the function remains the same
    int matches = 0;
    vector<string> sourceKeys = sourceMap.getAllKeys();
    
    for (const auto& target : targetNgrams) {
        for (size_t i = 0; i < sourceKeys.size(); i++) {
            const string& source = sourceKeys[i];
            float similarity = jaccardSimilarity(target, source);
            if (similarity >= threshold) {
                matches++;
                MatchInfo match;
                match.sourceText = source;
                match.targetText = target;
                match.similarity = similarity;
                match.lineNumber = getLineNumber(targetText, target);
                report.matches.push_back(match);
                break;
            }
        }
    }
    
    report.plagiarismPercentage = targetNgrams.empty() ? 0.0 : 
        (float(matches) / targetNgrams.size()) * 100;
    
    return report;
}

// Menu functions
void Options() {
    cout << "\n======== PLAGIARISM DETECTOR ========\n";
    cout << "1. Analyze Plagiarism\n";
    cout << "2. Set N-gram Size\n";
    cout << "3. Set Similarity Threshold\n";
    cout << "4. Choose Files\n";
    cout << "5. Generate Detailed Report\n";
    cout << "6. Analyze Text Complexity\n";
    cout << "7. Exit\n";
    cout << "===================================\n";
    cout << "Enter your choice: ";
}

void PD_menu() {
    int n = 3;
    float threshold = 0.8;
    string sourceFile = "source.txt";
    string targetFile = "target.txt";
    ReportDetails lastReport;

    // Expanded list of common words to filter out
    vector<string> commonWords = {
        // Articles
        "a", "an", "the",
        
        // Conjunctions
        "and", "but", "or", "nor", "for", "yet", "so",
        
        // Prepositions
        "in", "on", "at", "to", "for", "with", "by", "from", "up", "down", 
        "into", "onto", "upon", "under", "below", "above", "across", "through",
        "between", "among", "around", "before", "after", "during", "within",
        
        // Pronouns
        "i", "you", "he", "she", "it", "we", "they", 
        "me", "him", "her", "us", "them",
        "my", "your", "his", "her", "its", "our", "their",
        "mine", "yours", "hers", "ours", "theirs",
        "this", "that", "these", "those",
        "who", "whom", "whose", "which", "what",
        
        // Be verbs and auxiliaries
        "am", "is", "are", "was", "were", "be", "been", "being",
        "have", "has", "had", "do", "does", "did",
        "can", "could", "will", "would", "shall", "should", "may", "might",
        "must", "ought",
        
        // Common adverbs
        "very", "really", "quite", "rather", "too", "so", "just",
        "now", "then", "here", "there", "when", "where", "why", "how",
        "again", "ever", "far", "forward", "back", "once", "here", "there",
        "always", "never", "sometimes", "often", "rarely",
        
        // Numbers and quantities
        "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
        "first", "second", "third", "fourth", "fifth",
        "many", "much", "more", "most", "some", "any", "few", "several", "all",
        
        // Other common words
        "like", "as", "than", "about", "over", "under", "same", "different",
        "such", "no", "yes", "not", "only", "also", "then", "than",
        "well", "way", "even", "out", "in", "if", "about", "between"
    };

    while (true) {
        Options();
        int choice;
        cin >> choice;

        if (choice == 1) {
            string sourceText = readFile(sourceFile);
            string targetText = readFile(targetFile);

            if (sourceText.empty() || targetText.empty()) {
                cout << "Error reading files. Please check the file paths.\n";
                continue;
            }

            vector<string> sourceTokens = filterCommonWords(tokenize(sourceText), commonWords);
            vector<string> targetTokens = filterCommonWords(tokenize(targetText), commonWords);

            list<string> sourceNgrams = generateNgrams(sourceTokens, n);
            list<string> targetNgrams = generateNgrams(targetTokens, n);

            HashMap sourceMap;
            for (const string& ngram : sourceNgrams) {
                sourceMap.insert(ngram);
            }

            lastReport = calculatePlagiarismWithDetails(
                sourceText, targetText, 
                sourceMap, targetNgrams,
                sourceFile, targetFile,  // Pass the actual file names
                threshold
            );
            cout << "Plagiarism Percentage: " << fixed << setprecision(2) 
                 << lastReport.plagiarismPercentage << "%\n";

        } else if (choice == 2) {
            cout << "Enter new N-gram size: ";
            cin >> n;
            if (n <= 0) {
                cout << "Invalid N-gram size. Must be greater than 0.\n";
                n = 3;
            }

        } else if (choice == 3) {
            cout << "Enter new similarity threshold (0.0 to 1.0): ";
            cin >> threshold;
            if (threshold < 0.0 || threshold > 1.0) {
                cout << "Invalid threshold. Must be between 0.0 and 1.0.\n";
                threshold = 0.8;
            }

        } else if (choice == 4) {
            cin.ignore(); // Clear the input buffer
            cout << "Enter path to source file: ";
            getline(cin, sourceFile);
            cout << "Enter path to target file: ";
            getline(cin, targetFile);
            
            string testSource = readFile(sourceFile);
            string testTarget = readFile(targetFile);

            if (testSource.empty() || testTarget.empty()) {
                cout << "Error reading files. Reverting to previous file paths.\n";
                sourceFile = "source.txt";
                targetFile = "target.txt";
            } else {
                cout << "Files successfully updated.\n";
            }

        } else if (choice == 5) {
            if (lastReport.matches.empty()) {
                cout << "Please run plagiarism analysis first (Option 1).\n";
            } else {
                generateReport(lastReport);
            }

        } else if (choice == 6) {
            cout << "Select text to analyze:\n";
            cout << "1. Source file\n";
            cout << "2. Target file\n";
            int textChoice;
            cin >> textChoice;
            
            string text;
            if (textChoice == 1) {
                text = readFile(sourceFile);
            } else if (textChoice == 2) {
                text = readFile(targetFile);
            } else {
                cout << "Invalid choice.\n";
                continue;
            }
            
            if (!text.empty()) {
                analyzeTextComplexity(text);
            }

        } else if (choice == 7) {
            cout << "Exiting program. Goodbye!\n";
            break;

        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    cout << "Welcome to Plagiarism Detector!\n";
    PD_menu();
    return 0;
}

#endif // PLAGIARISM_DETECTOR_H