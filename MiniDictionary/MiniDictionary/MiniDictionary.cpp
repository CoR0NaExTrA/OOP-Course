#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

void loadDictionary(const string& filename, unordered_map<string, string>& dictionary) {
    ifstream file(filename);
    if (!file) return; // Если файл отсутствует, считаем словарь пустым
    string key, value;
    while (getline(file, key) && getline(file, value)) {
        dictionary[toLowerCase(key)] = value;
    }
}

void saveDictionary(const string& filename, const unordered_map<string, string>& dictionary) {
    ofstream file(filename);
    for (const auto& [key, value] : dictionary) {
        file << key << '\n' << value << '\n';
    }
}

int main(int argc, char* argv[]) {
    string dictionaryFile;
    if (argc >= 2) {
        dictionaryFile = argv[1];
    }
    else {
        dictionaryFile = "default_dictionary.txt"; // Используем файл по умолчанию
    }

    unordered_map<string, string> dictionary;
    bool fileExists = ifstream(dictionaryFile).good();
    loadDictionary(dictionaryFile, dictionary);

    string input;
    bool modified = false;

    cout << "Enter a word or phrase to translate (or '...' to exit):" << endl;
    while (getline(cin, input)) {
        if (input == "...") break;

        string lowerInput = toLowerCase(input);
        if (dictionary.find(lowerInput) != dictionary.end()) {
            cout << "Translation: " << dictionary[lowerInput] << endl;
        }
        else {
            cout << "Translation not found. Enter translation: ";
            string translation;
            getline(cin, translation);
            if (!translation.empty()) {
                dictionary[lowerInput] = translation;
                modified = true;
            }
        }
        cout << "Enter next word or phrase: " << endl;
    }

    if (modified || !fileExists) {
        cout << "Save changes to dictionary? (yes/no): ";
        string response;
        getline(cin, response);
        if (response == "yes") {
            saveDictionary(dictionaryFile, dictionary);
            cout << "Dictionary saved." << endl;
        }
    }

    return 0;
}
