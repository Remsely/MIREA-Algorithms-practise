#include <iostream>
#include <windows.h>
#include "HashTable.h"

void printMenu(){
    cout << "-----------------------------" << endl;
    cout << "Выберите действие:" << endl;
    cout << "1 - Добавить запись в таблицу;" << endl;
    cout << "2 - Удалить запись из таблицы;" << endl;
    cout << "3 - Найти запись в таблице;" << endl;
    cout << "4 - Вывести все записи;" << endl;
    cout << "0 - Выход." << endl;
    cout << "-----------------------------" << endl;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    HashTable phoneBook;
    phoneBook.insert("+79151981661", "Лазурная, 16к4");
    phoneBook.insert("+79163062984", "Проезд Одоевского, 7к3");
    phoneBook.insert("+74954225868", "Шоссейная, 5");

    int userChoice;
    string phoneNumber, address;
    bool isWorking = true;
    while (isWorking){
        printMenu();
        cin >> userChoice;
        switch (userChoice) {
            case 1:
                cout << "Введите номер телефона:";
                cin >> phoneNumber;
                cout << "Введите адрес:";
                cin.ignore();
                getline(cin, address);
                phoneBook.insert(phoneNumber, address);
                break;
            case 2:
                cout << "Введите номер телефона:";
                cin >> phoneNumber;
                phoneBook.remove(phoneNumber);
                break;
            case 3:
                cout << "Введите номер телефона:";
                cin >> phoneNumber;
                Entry *entry;
                entry = phoneBook.search(phoneNumber);
                if(entry != nullptr)
                    cout << "Номер телефона: " << entry->phoneNumber << " | Адрес: " << entry->address << endl;
                break;
            case 4:
                phoneBook.display();
                break;
            case 0:
                isWorking = false;
                cout << "Завершение работы программы...";
                break;
            default:
                cout << "Такая команда не поддерживается!" << endl;
                break;
        }
    }
    return 0;
}
