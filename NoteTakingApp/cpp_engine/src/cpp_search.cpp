// MAIN FILE

#include <iostream>
#include <fstream>
#include <vector>
#include "../vendor/json.hpp"   // Ensure the path is correct.
#include "../include/note.h"
#include "../include/search_engine.h"

using namespace std;
using json = nlohmann::json;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Executed: " << argv[0] << " with not sufficient number of arguments" << endl;
        return 1;
    }
    string query = argv[1];
    string jsonPath = argv[2];

    ifstream inpFile(jsonPath);
    if (!inpFile) {
        cerr << "Can't open the JSON file:" << jsonPath << endl;
        return 1;
    }

    json notesData;
    // inpFile >> notesData;
    try {
        inpFile >> notesData;
    } catch (json::parse_error& e) {
        cerr << "Error parsing JSON file: " << e.what() << endl;
        return 1;
    }
    inpFile.close();

    unordered_map<long long, Note> notes;
    for (const auto& item : notesData) {
        Note cur_note;
        cur_note.id = item["id"];
        cur_note.content = item["content"];
        notes[cur_note.id] = cur_note;
    }

    InvertedIndex index;
    buildInvertedIndex(notes, index);

    vector<Note> matchingNotes = searchNotesWithIndex(index, notes, query);

    json output = json::array();
    for (const Note& note : matchingNotes) {
        json j;
        j["id"] = note.id;
        j["score"] = note.score;
        j["snippet"] = note.snippet;
        output.push_back(j);
    }
    cout << output.dump() << endl;

    return 0;
}