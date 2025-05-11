// If Late, give pass #, describe reason
// Use pass #2, I got overwhelmed by other school work and had to use
// the late pass 

// Author: Garrett Johnson
// Project Description: Project 6 is about reading words from a file and then
// counting the number of words and lines they appear. The program then prints
// the words

#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
#include "bst.h"
#include "wordEntry.h"
using namespace std;

void ProcessFile(ifstream &file, vector<wordEntry> &wordArray);
void InsertWord(vector<wordEntry> &wordArray, BinarySearchTree &tree);
void PrintNode(wordEntry &data);

int main(void) {
    ifstream file;                                 
    string nameFile;
    BinarySearchTree tree;
    vector<wordEntry> wordArray;                        // A struct vector to store the information of each word

    cout << "Enter a file to be opened: ";
    cin >> nameFile;

    file.open(nameFile);
    if (!file) {
        cerr << "File could not be opened!\n";
        exit(1);
    }

    ProcessFile(file, wordArray);                       // A ReadFile function to read the words into the wordArray

    InsertWord(wordArray, tree);                        // Insert entries into the binary tree

    cout << "Word" << setw(20) << "Frequency" << setw(25) << "Occurs on Lines:\n";
    cout << setfill('-') << setw(52) << "\n";
    cout << setfill(' ');
    
    tree.InorderTraverse(PrintNode);                    // Print the contents of the binary tree in Inorder Traversal

    return 0;
}

/*
A void function that takes in a file and wordEntry array. It then reads a file line by line
using getline and then reads in the file using getline and processes each word using
an stringstream object. Each word's information is stored in that vector location. 
Word information including word, frequency, and line numbers
*/
void ProcessFile(ifstream &file, vector<wordEntry> &wordArray) {
    string line;
    int lineNumber = 0;                     // Track line number

    while (getline(file, line)) {           // Read the file line by line
        lineNumber++;                       // Increment line number for each new line
        stringstream iss(line);             // Stringstream object to read in words from line
        string word;                        // Word variable
        
        while (iss >> word) {               // Read line into each word 
            transform(word.begin(), word.end(), word.begin(), ::tolower);   // Convert word to lowercase
            
            word.erase (                                    // Remove non-alphabetic characters from the word
                    remove_if(word.begin(), word.end(),
                    [](unsigned char c) {
                        return !isalpha(c);
                    }),
            word.end()
            );

            wordEntry entry;                        // Create a new word entry
            entry.word = word;                      // Assign word
            entry.frequency++;                      // Store frequency
            entry.lineNum.push_back(lineNumber);    // Add line number
            entry.lastLine = lineNumber;            // Set last line to current line

            bool found = false;
            vector<wordEntry>::iterator iter;
            for (iter = wordArray.begin(); iter != wordArray.end(); iter++) {
                if (iter->word == entry.word) {                     // If the word is found 
                    iter->frequency++;                              // Increment frequency
                    if (iter->lastLine != entry.lastLine) {         // If it is a new line
                        iter->lastLine = entry.lastLine;            // Update the last line
                        iter->lineNum.push_back(entry.lastLine);    // Add the line number
                    }
                    found = true;                                   // Mark word as found
                }
            }
            if (!found) {                                           // If word is not found, add to the wordArray
                wordArray.push_back(entry);
            }
        }
    }
}

/*
A void function that takes the vector of wordEntries and a binary search tree. The function inserts
each wordEntry from the vector into the binary search tree. If insertion fails, print error message.
*/
void InsertWord(vector<wordEntry> &wordArray, BinarySearchTree &tree) {
    bool success = false;

    for (auto &entry : wordArray) {                                         // Iterate through each wordEntry in the wordArray
        tree.SearchTreeInsert(entry, success);                              // Insert word into binary search tree
        if (!success) {
            cerr << "Failed to insert word: " << entry.word << "\n";
        }
    }
}

/*
A void function that takes a wordEntry and prints the details
*/
void PrintNode(wordEntry &data) {
    cout << left << setw(13) << data.word   // Left align
    << right << setw(6) << data.frequency   // Print word and its freq
    << setw(15);    

    // Iterate through the list of line numbers
    list<int>::iterator iter;               
    for (iter = data.lineNum.begin(); iter != data.lineNum.end(); iter++) {
        cout << *iter << "";                           // Print current line number
        if (next(iter) != data.lineNum.end()) {        // If there are more line numbers, add comma seperation
            cout << ",";
        }
    }
    cout << "\n";
}