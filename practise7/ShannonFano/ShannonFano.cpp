#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>

using namespace std;

struct Node {
    char character;
    double probability;
    string code;

    Node(int sym, double prob) : character(sym), probability(prob) {}
};

vector<Node *> nodes;
string inputStroke;
string codePhrase;

bool compareNodesProbabilities(const Node *n1, const Node *n2) {
    return n1->probability > n2->probability;
}

void createShannonFanoCodes(vector<Node *> &nodes, int start, int end) {
    if (start == end)
        return;

    int splitIndex = 0;
    double sumLeft;
    double sumRight;
    double minDifference = numeric_limits<double>::max();

    for (int i = start; i < end; ++i) {
        sumLeft = 0.0;
        sumRight = 0.0;

        for (int j = start; j <= i; ++j)
            sumLeft += nodes[j]->probability;

        for (int j = i + 1; j <= end; ++j)
            sumRight += nodes[j]->probability;

        double difference = abs(sumLeft - sumRight);

        if (difference == 0) {
            splitIndex = i;
            break;
        }

        if (difference < minDifference) {
            minDifference = difference;
            splitIndex = i;
        }
    }

    for (int i = start; i <= splitIndex; ++i)
        nodes[i]->code += "0";

    for (int i = splitIndex + 1; i <= end; ++i)
        nodes[i]->code += "1";

    createShannonFanoCodes(nodes, start, splitIndex);
    createShannonFanoCodes(nodes, splitIndex + 1, end);
}

void encodeShannonFano() {
    cout << "Enter a stroke:" << endl;
    getline(cin, inputStroke);

    map<char, int> characters;

    for (char ch: inputStroke)
        characters[ch] = characters[ch] + 1;

    for (const auto &pair: characters) {
        double b = double(pair.second) / inputStroke.size();
        nodes.push_back(new Node(pair.first, b));
        cout << pair.first << " : " << b << endl;
    }

    sort(nodes.begin(), nodes.end(), compareNodesProbabilities);

    createShannonFanoCodes(nodes, 0, nodes.size() - 1);

    for (char character: inputStroke) {
        for (Node *node: nodes) {
            if (node->character == character)
                codePhrase += node->code + " ";
        }
    }

    cout << "Result: " << codePhrase << endl;
}

void decodeShannonFano() {
    string decodedResult;
    string currentCode;

    for (char c: codePhrase) {
        if (c == ' ')
            continue;

        currentCode += c;

        for (Node *node: nodes) {
            if (currentCode == node->code) {
                decodedResult += node->character;
                currentCode = "";
                break;
            }
        }
    }

    std::cout << "Decoded result: " << decodedResult << std::endl;
}

int main() {
    encodeShannonFano();
    decodeShannonFano();
    return 0;
}