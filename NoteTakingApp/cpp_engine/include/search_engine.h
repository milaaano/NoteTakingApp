#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <vector>
#include <string>
#include <unordered_map>
#include "note.h"

using namespace std;

struct Posting {
    long long docId;
    long long frequency;
    long long firstOccurrence;
};

using InvertedIndex = unordered_map<string, unordered_map<long long, Posting>>;

string toLower(const string& s);

vector<string> splitWords(const string& s);

void buildInvertedIndex(const unordered_map<long long, Note>& notes, InvertedIndex& index);

string getSnippet(const string& content, const string& query, long long& firstOccurrence);

vector<Note> searchNotesWithIndex(const InvertedIndex& index, const unordered_map<long long, Note>& notes, const string& query);

#endif