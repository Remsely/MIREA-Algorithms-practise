#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <windows.h>
#include <fstream>

using namespace std;

// Структура для представления узла в дереве Хаффмана
struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode *left;
    HuffmanNode *right;

    HuffmanNode(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

// Функция для сравнения узлов при использовании очереди с приоритетом
struct CompareNodes {
    bool operator()(HuffmanNode *left, HuffmanNode *right) {
        return left->frequency > right->frequency;
    }
};

// Функция для построения дерева Хаффмана и возврата корня дерева
HuffmanNode *buildHuffmanTree(const string &text) {
    unordered_map<char, int> frequencyMap;
    for (char c: text)
        frequencyMap[c]++;

    priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareNodes> minHeap;
    for (const auto &pair: frequencyMap)
        minHeap.push(new HuffmanNode(pair.first, pair.second));

    while (minHeap.size() > 1) {
        HuffmanNode *left = minHeap.top();
        minHeap.pop();
        HuffmanNode *right = minHeap.top();
        minHeap.pop();

        int combinedFrequency = left->frequency + right->frequency;
        auto *newNode = new HuffmanNode('\0', combinedFrequency);
        newNode->left = left;
        newNode->right = right;
        minHeap.push(newNode);
    }

    for (const auto &pair: frequencyMap)
        cout << pair.first << " : " << pair.second << endl;

    return minHeap.top();
}

// Рекурсивная функция для создания кодов Хаффмана
void generateHuffmanCodes(HuffmanNode *root, const string &currentCode, unordered_map<char, string> &codes) {
    if (!root)
        return;

    if (root->data != '\0')
        codes[root->data] = currentCode;

    generateHuffmanCodes(root->left, currentCode + "0", codes);
    generateHuffmanCodes(root->right, currentCode + "1", codes);
}

// Функция для кодирования строки с использованием кодов Хаффмана
string encodeHuffman(const string &text) {
    HuffmanNode *root = buildHuffmanTree(text);
    unordered_map<char, string> codes;
    generateHuffmanCodes(root, "", codes);

    string encodedText;
    for (char c: text)
        encodedText += codes[c];

    return encodedText;
}

string encodeHuffmanGoodView(const string &text) {
    HuffmanNode *root = buildHuffmanTree(text);
    unordered_map<char, string> codes;
    generateHuffmanCodes(root, "", codes);

    string encodedText;
    for (char c: text)
        encodedText += codes[c] + " ";

    return encodedText;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    ifstream file(R"(C:\Users\paths\CLionProjects\siaod_practise_7\inputHuffman.txt)");

    string inputString;
    double inputSize;
    double encodedSize;

    if (file.is_open()) {
        getline(file, inputString);

        file.seekg(0, ios::end);
        inputSize = file.tellg() * 8;
        file.seekg(0, ios::beg);

        cout << inputSize << endl;
        file.close();
    } else {
        std::cerr << "Can not read file!" << std::endl;
        return 1;
    }

    string encodedStringGoodView = encodeHuffmanGoodView(inputString);
    string encodedString = encodeHuffman(inputString);

    encodedSize = encodedString.length();

    cout << "Your name: " << inputString << std::endl;
    cout << "Your encoded name: " << encodedStringGoodView << std::endl;

    double compressionRatio = inputSize / encodedSize;

    cout << "Коэффициент сжатия: " << compressionRatio << endl;
    
    return 0;
}
