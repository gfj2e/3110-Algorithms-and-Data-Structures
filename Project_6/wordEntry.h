#ifndef WORDENTRY_H
#define WORDENTRY_H
#include <string>
#include <list>
using namespace std;

struct wordEntry {
    string word;            // Storing word
    int frequency = 0;      // Stores frequency of word 
    list<int> lineNum;      // Store line num
    int lastLine = 0;       // And last line num
 string Key() const;
};

#endif