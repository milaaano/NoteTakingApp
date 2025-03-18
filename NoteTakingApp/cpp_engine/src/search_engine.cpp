#include "../include/search_engine.h"
#include <sstream>
#include <algorithm>
#include <cctype>
#include <vector>
#include <unordered_set>
#include <iostream>

using namespace std;

string toLower(const string& s) {
    string lowered;
    lowered.reserve(s.size());
    for (const char& ch : s) {
        if (ch >= 'A' && ch <= 'Z') {
            lowered.push_back(ch + 32);
        } else {
            lowered.push_back(ch);
        }
        
    }
    return lowered;
}

vector<string> splitWords(const string& s) {
    istringstream iss(s);
    vector<string> tokens;
    string cur;
    while (iss >> cur) {
        tokens.push_back(cur);
    }
    return tokens;
}

string getSnippet(const string& content, const string& query, long long& firOcc) {
    string lower_content = toLower(content);
    string lower_query = toLower(query);
    vector<string> tokenized_content = splitWords(lower_content);
    vector<string> snippet_vec;
    long long l = firOcc, r = firOcc + 1;
    while (r < tokenized_content.size() && l >= 0 && snippet_vec.size() < 10) {
        if (l >= 0) {
            snippet_vec.insert(snippet_vec.begin(), tokenized_content[l]);
            l--;
        }
        if (r < tokenized_content.size()) {
            snippet_vec.push_back(tokenized_content[r]);
            r++;
        }
    }
    while (snippet_vec.size() < 10 && r < tokenized_content.size()) {
        snippet_vec.push_back(tokenized_content[r]);
        r++;
    }
    while (snippet_vec.size() < 10 && l >= 0) {
        snippet_vec.insert(snippet_vec.begin(), tokenized_content[l]);
        l--;
    }
    string snippet = "";
    for (const string& token : snippet_vec) {
        snippet += token + " ";
    }
    return snippet;
}

// struct Posting {
//     long long docId;
//     long long frequency;
//     long long firstOccurrence;
// };

// in the future we can implement the same technique as in Makefile to update inverted index

void buildInvertedIndex(const unordered_map<long long, Note>& notes, InvertedIndex& index) {
    for (const auto& pair : notes) {
        Note note = pair.second;
        vector<string> cur_note = splitWords(toLower(note.content));
        for (long long i = 0; i < (long long)cur_note.size(); i++) {
            string token = cur_note[i];
            if (index.count(token) == 0 || index[token].count(note.id) == 0) {
                Posting cur;
                cur.docId = note.id;
                cur.frequency = 1;
                cur.firstOccurrence = i;
                index[token][note.id] = cur;
            } else {
                index[token][note.id].frequency++;
            }
        }
    }
}

// using InvertedIndex = std::unordered_map<std::string, std::unordered_map<long long, Posting>>;

vector<Note> searchNotesWithIndex(const InvertedIndex& index, const unordered_map<long long, Note>& notes, const string& query) {
    vector<Note> matches;
    vector<string> vec_with_flags = splitWords(toLower(query));
    vector<string> query_vec;
    bool is_or = false;
    if (vec_with_flags.empty()) {
        return matches;
    }
    for (const string& el : vec_with_flags) {
        if (el == "'or'") {
            is_or = true;
        } else {
            query_vec.push_back(el);
        }
    }

    unordered_map<long long, Note> matching_notes;
    unordered_map<long long, long long> countFound;
    
    for (const string& token : query_vec) {
        auto it = index.find(token);
        if (it != index.end()) {
            auto& PostingList = it->second;
            for (const auto& pair : PostingList) {
                Posting p = pair.second;
                matching_notes[p.docId] = notes.at(p.docId);
                matching_notes[p.docId].score += p.frequency;
                countFound[p.docId]++;
            }
        }
    }


    for (auto it = matching_notes.begin(); it != matching_notes.end(); it++) {
        Note cur_note = it->second;
        long long firOcc = -1;
        string tokenForSnippet;
        for (const string& token : query_vec) {
            auto tokenIt = index.find(token);
            if (tokenIt != index.end() && tokenIt->second.find(cur_note.id) != tokenIt->second.end()) {
                firOcc = tokenIt->second.at(cur_note.id).firstOccurrence;
                tokenForSnippet = token;
                break;
            }
        }

        cur_note.snippet = getSnippet(cur_note.content, tokenForSnippet, firOcc);

        if (is_or) {
            matches.push_back(cur_note);
        } else {
            if (countFound[cur_note.id] == query_vec.size()) {
                matches.push_back(cur_note);
            }
        }
    }
    
    sort(matches.begin(), matches.end(), [](const Note& a, const Note& b) {
        return a.score > b.score;
    });

    return matches;
}