#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <random>

using namespace std;


struct Registration{
    int licenseNumber = -1;
    char name[20]{};
    char founder[20]{};
};

bool isInVector(const vector<int>& vector, int n){ // Функция, проверяющая есть ли число в векторе
    for(int el : vector)
        if(el == n)
            return true;
    return false;
}

void createBinaryFile(const string& fileName, int numRecords){
    // Инициализация всего необходимого для работы random
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(100000,999999);

    // Открытие текстового и бинарного файлов для записи
    ofstream file(fileName, ios::binary | ios::out);
    ofstream fileTxt(fileName + ".txt", ios::binary | ios::out);

    if(!file){
        cout << "Ошибка при открытии файла для бинарной записи!" << endl;
        return;
    }

    vector<int> licenseNumbers;
    for(int i = 0; i < numRecords; i++){ // Цикл, реализующий добавление запсисей в файл
        int n;

        while (true){ // Цикл, генерирующий уникальные номера лицезий
            n = dist(gen);
            if(!isInVector(licenseNumbers, n))
                break;
        }
        licenseNumbers.push_back(n);

        Registration record;
        record.licenseNumber = n;
        // Запись в массив char строк
        snprintf(record.name, sizeof(record.name), "Company %d", i);
        snprintf(record.founder, sizeof(record.founder), "Founder %d", i);

        // добавление записей в файл
        file.write(reinterpret_cast<char*>(&record), sizeof(Registration));
        fileTxt << record.licenseNumber << " " << record.name << " " << record.founder << endl;
    }

    file.close();
    fileTxt.close();
}

Registration linearSearch(const string& fileName, int key){ // Функция линейного поиска
    ifstream file(fileName, ios::binary | ios::in);

    if (!file){
        cout << "Ошибка при открытии файла для линейного поиска!" << endl;
        return Registration{-2, "", ""};
    }

    Registration record;
    while (file.read(reinterpret_cast<char*>(&record), sizeof (Registration))){
        if(record.licenseNumber == key){
            file.close();
            return record;
        }
    }

    file.close();
    return Registration{-1, "", ""};
}

Registration binarySearch(const string& fileName, int key){ // Функция бинарного поиска
    ifstream file(fileName, ios::binary | ios::in);

    if(!file){
        cout << "Ошибка при открытии файла для бинарного поиска!";
        return Registration{-2, "", ""};
    }

    file.seekg(0, ios::end);
    int fileSize = file.tellg();
    int numRecords = fileSize / sizeof(Registration);

    vector<Registration> records;

    file.seekg(0, ios::beg);

    Registration record;
    while (file.read(reinterpret_cast<char*>(&record), sizeof(Registration)))
        records.push_back(record);

    file.close();

    sort(records.begin(), records.end(), [](const Registration& a, const Registration& b){
        return a.licenseNumber < b.licenseNumber;
    });

    int left = 0;
    int right = numRecords - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (records[mid].licenseNumber == key){
            return records[mid];
        }

        if(records[mid].licenseNumber < key)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return Registration{-1, "", ""};
}


int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(100000,999999);

    SetConsoleOutputCP(CP_UTF8);
    string fileName;
    int numberOfRecords[] = {100, 1000, 10000};

    for (int num : numberOfRecords) {
        fileName = "Registration_l" + to_string(num) + ".bin";
        createBinaryFile(fileName, num);

        int key = dist(gen);

        unsigned int start_time = clock();
        Registration result = linearSearch(fileName, key);
        unsigned int end_time = clock();

        cout << "Линейный поиск в файле из " << num << " элементов:" << endl;
        if (result.licenseNumber != -1){
            cout << "Запись найдена |Номер лицензии - " << result.licenseNumber
            << "|Учредитель - " << result.founder << "|Название - " << result.name
            << "|Время выполнение поиска - " << end_time - start_time << "мс"  << endl;
        }
        else{
            cout << "Запись не найдена! Ключ - " << key << "|Время выполнение поиска - "
            << end_time - start_time << "мс"  << endl;
        }
    }

    cout << endl << endl;

    for (int num : numberOfRecords) {
        fileName = "Registration_b" + to_string(num) + ".bin";
        createBinaryFile(fileName, num);

        int key = dist(gen);

        unsigned int start_time = clock();
        Registration result = binarySearch(fileName, key);
        unsigned int end_time = clock();

        cout << "Бинарный поиск в файле из " << num << " элементов:" << endl;
        if (result.licenseNumber != -1){
            cout << "Запись найдена |Номер лицензии - " << result.licenseNumber
                 << "|Учредитель - " << result.founder << "|Название - " << result.name
                 << "|Время выполнение поиска - " << end_time - start_time << "мс" << endl;
        }
        else{
            cout << "Запись не найдена! Ключ - " << key << "|Время выполнение поиска - "
            << end_time - start_time << "мс" << endl;
        }
    }
    return 0;
}
