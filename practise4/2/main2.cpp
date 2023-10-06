#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

const int ALPHABET_SIZE = 256;

void precomputeBadCharacterShift(const string &pattern, vector<int> &badCharacterShift) {
    int patternLength = pattern.length();

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        badCharacterShift[i] = patternLength;
    }

    for (int i = 0; i < patternLength - 1; i++) {
        badCharacterShift[static_cast<int>(pattern[i])] = patternLength - 1 - i;
    }
}

void precomputeGoodSuffixShift(const string &pattern, vector<int> &goodSuffixShift) {
    int patternLength = pattern.length();
    vector<int> suffixLength(patternLength, 0);

    for (int i = 0; i < patternLength - 1; i++) {
        int j = i;
        int k = 0;
        while (j >= 0 && pattern[j] == pattern[patternLength - 1 - k]) {
            j--;
            k++;
            suffixLength[k] = j + 1;
        }
    }

    for (int i = 0; i < patternLength; i++) {
        goodSuffixShift[i] = patternLength;
    }

    for (int i = patternLength - 1; i >= 0; i--) {
        if (suffixLength[i] == i + 1) {
            for (int j = 0; j < patternLength - 1 - i; j++) {
                if (goodSuffixShift[j] == patternLength) {
                    goodSuffixShift[j] = patternLength - 1 - i;
                }
            }
        }
    }

    for (int i = 0; i < patternLength - 1; i++) {
        goodSuffixShift[patternLength - 1 - suffixLength[i]] = patternLength - 1 - i;
    }
}

void searchTurboBoyerMoore(const string &text, const string &pattern) {
    int textLength = text.length();
    int patternLength = pattern.length();
    vector<int> badCharacterShift(ALPHABET_SIZE, patternLength);
    vector<int> goodSuffixShift(patternLength, patternLength);

    precomputeBadCharacterShift(pattern, badCharacterShift);
    precomputeGoodSuffixShift(pattern, goodSuffixShift);

    int i = 0;

    while (i <= textLength - patternLength) {
        int j = patternLength - 1;

        while (j >= 0 && pattern[j] == text[i + j]) {
            j--;
        }

        if (j < 0) {
            cout << "Найдено вхождение строки. Индекс: " << i << endl;
            i += goodSuffixShift[0];
        } else {
            i += max(badCharacterShift[static_cast<int>(text[i + j])] - j, goodSuffixShift[j]);
        }
    }
}


int main() {
    SetConsoleOutputCP(CP_UTF8);

    ifstream inputFile("C:\\Users\\paths\\CLionProjects\\siaod_practise_4_1\\windows-1251.txt");

    if (!inputFile) {
        cout << "Ошибка открытия файла!" << endl;
        return 1;
    }

    string pattern;
    getline(inputFile, pattern);

    string text;
    getline(inputFile, text);

    inputFile.close();

    searchTurboBoyerMoore(text, pattern);

    return 0;
}