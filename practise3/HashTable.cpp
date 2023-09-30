//
// Created by proko on 30.09.2023.
//

#include "HashTable.h"

HashTable::HashTable() {
    for(auto & el : table){
        el = nullptr;
    }
}

int HashTable::hashFunction(const string& key) {
    int hash = 0;
    for(char ch : key)
        hash += static_cast<int>(ch);
    return hash % TABLE_SIZE;
}

int HashTable::quadraticProbe(int index, int attempt) {
    return (index + attempt * attempt) % TABLE_SIZE;
}

void HashTable::insert(const string& phone, const string& addr) {
    int index = hashFunction(phone);
    int attempt = 0;

    while (table[index] != nullptr){
        attempt++;
        index = quadraticProbe(index, attempt);
    }
    table[index] = new Entry(phone, addr);
    cout << "Запись добавлена!" << endl;
}

void HashTable::remove(const string& phone) {
    int index = hashFunction(phone);
    int attempt = 0;

    while (table[index] != nullptr){
        if(table[index]->phoneNumber == phone){
            delete table[index];
            table[index] = nullptr;
            cout << "Запись удалена!" << endl;
            return;
        }
        attempt++;
        index = quadraticProbe(index, attempt);
    }
    cout << "Запись не найдена!" << endl;
}

Entry *HashTable::search(const string& phone) {
    int index = hashFunction(phone);
    int attempt = 0;

    while (table[index] != nullptr){
        if(table[index]->phoneNumber == phone){
            cout << "Запись найдена! " << endl;
            return table[index];
        }
        attempt++;
        index = quadraticProbe(index, attempt);
    }
    cout << "Запись не найдена! " << endl;
    return nullptr;
}

void HashTable::display() {
    for(auto & el : table){
        if (el != nullptr)
            cout << "Номер телефона: " << el->phoneNumber << " | Адрес: " << el->address << endl;
    }
}
