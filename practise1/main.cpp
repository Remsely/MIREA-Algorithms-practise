#include <iostream>
#include <windows.h>
#include <bitset>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstring>

using namespace std;

void taskOneA(){
    unsigned char x = 255; // 8-ми разрядное число
    unsigned char maska = 1; // 1 = 00000001 - 8-разрядная маска
    x = x & (~(maska<<4)); // Устанавливаем 5-ый бит в 0
    cout << (int) x; // Вывод результата в виде числа
}

void taskOneB(){
    unsigned char x = 255; // 8-ми разрядное число
    unsigned char maska = 1; // 1 = 00000001 - 8-разрядная маска
    x = x & (~(maska<<6)); // Устанавливаем 7-ый бит в 0
    cout << (int) x; // Вывод результата в виде числа
}

void taskOneV(){
    unsigned int x = 25;
    const int n = sizeof(int)*8; //=32 - количество разрядов в числе типа int
    unsigned maska = (1 << (n - 1)); //1 в старшем бите 32-разрядной сетки
    cout << "Начальный вид маски: " << bitset<n> (maska) << endl;
    cout << "Результат: ";
    for(int i = 1; i <= n; i++){ //32 раза - по количеству разрядов:
        cout << ((x & maska) >> (n - i));
        maska = maska >> 1; //смещение 1 в маске на разряд вправо
    }
    cout << endl;
}

void taskTwoA(){
    unsigned char bitArray = 0; // Битовый массив
    unsigned char maska = 1;
    int inputNumber; // Переменная для ввода чисел
    const int sizeOfChar = 8; // Кол-во бит, которое приходится на unsigned char

    vector<int> numbersArray;
    cout << "Введите числа (не больше 7) Для завершения ввода введите -1: " << endl;

    // Заполнение массива чисел
    while (true) {
        std::cin >> inputNumber;

        if (inputNumber == -1) {
            break;
        }
        numbersArray.push_back(inputNumber);
    }

    cout << "Изначальный массив: ";
    for(int el : numbersArray){
        cout << el << " ";
        bitArray = bitArray | (maska << el);
    }

    // Вывод набора чисел в битовой последовательности
    bitset<sizeOfChar> bitset(bitArray);
    cout << endl;
    cout << "Набор чисел в битовой последовательности: " << bitset << endl;

    // Вывод отсортированного массива
    cout << "Отсортированный массив: ";
    for(int i = 0; i < sizeOfChar; i++){
        if(bitset[i])
            cout << i << " ";
    }
}

void taskTwoB(){
    unsigned long long bitArray = 0; // Битовый массив
    unsigned long long maska = 1;
    int inputNumber; // Переменная для ввода чисел
    const int sizeOfUnsignedLongLong = 64; // Кол-во бит, которое приходится на unsigned long long

    vector<int> numbersArray;
    cout << "Введите числа (не больше 63) Для завершения ввода введите -1: " << endl;

    // Заполнение массива чисел
    while (true) {
        std::cin >> inputNumber;

        if (inputNumber == -1) {
            break;
        }
        numbersArray.push_back(inputNumber);
    }

    cout << "Изначальный массив: ";
    for(int el : numbersArray){
        cout << el << " ";
        bitArray = bitArray | (maska << el);
    }

    // Вывод набора чисел в битовой последовательности
    bitset<sizeOfUnsignedLongLong> bitset(bitArray);
    cout << endl;
    cout << "Набор чисел в битовой последовательности: " << bitset << endl;

    // Вывод отсортированного массива
    cout << "Отсортированный массив: ";
    for(int i = 0; i < sizeOfUnsignedLongLong; i++){
        if(bitset[i])
            cout << i << " ";
    }
}

void taskTwoV(){
    const int bitArrayLength = 8; // Длинна массива из char значений
    unsigned char bitArray[bitArrayLength]; // Битовый массив
    unsigned char maska = 1;
    int inputNumber;
    const int sizeOfUnsignedChar = 8; // Кол-во бит, которое приходится на unsigned char

    vector<int> numbersArray;
    cout << "Введите числа (не больше 63) Для завершения ввода введите -1: " << endl;

    // Заполнение массива чисел
    while (true) {
        std::cin >> inputNumber;

        if (inputNumber == -1) {
            break;
        }
        numbersArray.push_back(inputNumber);
    }

    cout << "Изначальный массив: ";
    for(int el : numbersArray){
        cout << el << " ";
        bitArray[el / sizeOfUnsignedChar] = bitArray[el / sizeOfUnsignedChar] | (maska << (el % sizeOfUnsignedChar));
    }

    // Вывод набора чисел в битовой последовательности
    cout << endl;
    cout << "Набор чисел в битовой последовательности: ";
    for (int i = bitArrayLength - 1; i >= 0; i--) {
        cout << bitset<sizeOfUnsignedChar>(bitArray[i]);
    }
    cout << endl;

    // Вывод отсортированного массива
    cout << "Отсортированный массив: ";
    for (int i = 0; i < bitArrayLength; i++) {
        bitset<sizeOfUnsignedChar> bitset(bitArray[i]);
        for(int j = 0; j < sizeOfUnsignedChar; j++){
            if(bitset[j])
                cout << j + i * sizeOfUnsignedChar << " ";
        }
    }
}

void taskThree(){
    unsigned int start_time =  clock();

    // Открытие файла для чтения
    ifstream inputFile("input.txt");
    if(!inputFile){
        cout << "Не удается открыть файл для чтения!";
        return;
    }

    // Открытие файла для записи
    ofstream outputFile("output.txt");
    if(!outputFile){
        cout << "Не удается открыть файл для записи!";
        return;
    }
    outputFile.clear();

    const int bitArrayLength = 1048576; // Длинна массива из char значений
    unsigned char bitArray[bitArrayLength]; // Битовый массив
    const int sizeOfUnsignedChar = 8; // Кол-во бит, которое приходится на unsigned char
    unsigned char maska = 1;

    std::memset(bitArray, 0, bitArrayLength);

    // Заполнение массива чисел
    vector<int> numbersArray;
    int num;
    while(inputFile >> num)
        numbersArray.push_back(num);

    inputFile.close();

    // Заполнение битового массива
    for(int el : numbersArray)
        bitArray[el / sizeOfUnsignedChar] = bitArray[el / sizeOfUnsignedChar] | (maska << (el % sizeOfUnsignedChar));


    // Запись результатов в файл
    for (int i = 0; i < bitArrayLength; i++) {
        bitset<sizeOfUnsignedChar> bitset(bitArray[i]);
        for(int j = 0; j < sizeOfUnsignedChar; j++){
            if(bitset[j] == 1)
                outputFile << j + i * sizeOfUnsignedChar << " ";
        }
    }

    outputFile.close();

    // Вывод результатов работы программы
    unsigned int end_time = clock();
    cout << "Время сортировки: " << end_time - start_time << " мс" << endl;
    cout << "Размер битового массива: " << sizeof(bitArray) / 1024 / 1024 << " Мбайт";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    taskThree();
    return 0;
}
