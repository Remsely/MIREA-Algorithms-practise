#ifndef SIAOD_PRACTISE_3_HASHTABLE_H
#define SIAOD_PRACTISE_3_HASHTABLE_H

#include <iostream>
#include <utility>

using namespace std;

class Entry{
public:
    string phoneNumber;
    string address;

    Entry(string  phone, string  addr) : phoneNumber(std::move(phone)), address(std::move(addr)) {}
};


class HashTable {
private:
    static const int TABLE_SIZE = 11;
    Entry* table[TABLE_SIZE]{};

    static int hashFunction(const string& key);
    static int quadraticProbe(int index, int attempt);

public:
    HashTable();

    void insert(const string& phone, const string& addr);
    void remove(const string& phone);
    Entry* search(const string& phone);
    void display();
};

#endif //SIAOD_PRACTISE_3_HASHTABLE_H
