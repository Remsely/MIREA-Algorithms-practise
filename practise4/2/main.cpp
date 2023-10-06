#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

bool isPunctuation(char c) {
    return std::ispunct(static_cast<unsigned char>(c));
}

vector<string> findWordsStartingWithSubstring(const string &text, const string &substring) {
    vector<string> result;
    string word;
    bool substrInWord = false;

    for (char c: text) {
        if (!isPunctuation(c) && c != ' ') {
            word += c;
            if (word == substring) {
                substrInWord = true;
            }
        } else {
            if (substrInWord)
                result.push_back(word);
            word.clear();
            substrInWord = false;
        }
    }
    if (substrInWord)
        result.push_back(word);
    return result;
}


int main() {
    SetConsoleOutputCP(CP_UTF8);

    string text, substring;
    cout << "Введите текст: " << endl;
    getline(cin, text);
    cout << "Введите начало слова, которое вам необходимо найти: " << endl;
    getline(cin, substring);

    vector<string> words = findWordsStartingWithSubstring(text, substring);

    if (!words.empty()) {
        cout << "Слова тексте, начинающиеся с " << substring << ": " << endl;
        for (const auto &word: words)
            cout << word << endl;
    } else {
        cout << "Слов, начинающихся с " << substring << ", нет в тексте! " << endl;
    }

    return 0;
}
