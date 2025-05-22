#include <iostream>
#include <fstream>
#include <string>
#include "Vernam.h"
#include "Skitala.h"
#include "Vizhener.h"

using namespace std;

// Функция проверки пароля
bool checkPassword() {
    string password;
    cout << "Введите пароль: ";
    getline(cin, password);
    return password == "password"; // Пароль по умолчанию
}

// Функция вывода главного меню
void printMainMenu() {
    cout << "\n======= Главное меню =======" << endl;
    cout << "1. Создать новый файл" << endl;
    cout << "2. Вывести текст из файла" << endl;
    cout << "3. Выход" << endl;
    cout << "============================" << endl;
    cout << "Ваш выбор: ";
}

void displayFile() {
    string fileName;
    cout << "Введите имя файла: ";
    getline(cin, fileName);

    ifstream file(fileName);
    if (file.is_open()) {
        string EncodingInfo; // Информация о методе шифрования
        getline(file, EncodingInfo); 

        string EncodedText;
        string line;
        while (getline(file, line)) {
            if (!EncodedText.empty()) {
                EncodedText += "\n"; 
            }
            EncodedText += line;
        }
        file.close();

        cout << "Зашифрованный текст:" << endl;
        cout << EncodedText << endl;

        cout << "\nДешифровать?" << endl;
        cout << "1. Да" << endl;
        cout << "2. Нет" << endl;
        int choice;
        cin >> choice;
        cin.ignore(); // Очистка буфера ввода

        if (choice == 1) {
            string DecodedText;
            if (EncodingInfo.find("vernam:") == 0) {
                unsigned int key = stoi(EncodingInfo.substr(7));
                DecodedText = VernamDecoded(EncodedText, key);
            }
            else if (EncodingInfo.find("vigenere:") == 0) {
                string key = EncodingInfo.substr(9); // Извлекаем ключ 
               // cout << "Используемый ключ:" << key  << endl; 
                DecodedText = VizhenerDecode(EncodedText, key);
            }
            else if (EncodingInfo.find("skitala:") == 0) {
                int height = stoi(EncodingInfo.substr(8)); // Извлекаем высоту
                DecodedText = SkitalaDecoded(EncodedText, height);
            }
            else {
                cout << "Неверный метод шифрования!" << endl;
                return;
            }

            cout << "Дешифрованный текст:" << endl;
            cout << DecodedText << endl;
        }
    }
    else {
        cout << "Ошибка: файл не существует или не может быть открыт!" << endl;
    }
}

// Функция создания файла
void createFile() {
    string fileName, text;
    cout << "Введите название файла: ";
    getline(cin, fileName);

    cout << "Введите текст: ";
    getline(cin, text);

    cout << "\nЗашифровать?" << endl;
    cout << "1. Да" << endl;
    cout << "2. Нет" << endl;
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        cout << "\nВыберите метод шифрования:" << endl;
        cout << "1. Шифр Вернама" << endl;
        cout << "2. Шифр Скитала" << endl;
        cout << "3. Шифр Виженера" << endl;
        int method;
        cin >> method;
        cin.ignore();

        string EncodedText;
        string EncodingInfo; // Информация о методе шифрования

        switch (method) {
        case 1: { // Вернам
            unsigned int key;
            while (true) {
                cout << "Введите ключ ";
                if (cin >> key) {
                    cin.ignore(); // очистка буфера
                    break;
                }
                else {
                    cout << "Ошибка: введите целое число." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }

            EncodingInfo = "vernam:" + to_string(key);
            EncodedText = VernamEncoded(text, key);
            break;
        }

        //case 1: { // Цезарь
        //    int shift;
        //    while (true) {
        //        cout << "Введите сдвиг: ";
        //        if (cin >> shift) {
        //            cin.ignore(); // Очистка буфера ввода
        //            break;
        //        }
        //        else {
        //            cout << "Напишите число: " << endl;
        //            cin.clear();
        //            cin.ignore(); 
        //        }
        //    }

        //    EncodingInfo = "caesar:" + to_string(shift);
        //    EncodedText = caesarEncoded(text, shift);
        //    break;
        //}

        case 2: { // Скитала
            int height;
            bool validInput = false;
            while (!validInput) {
                cout << "Введите количество строк: ";
                cin >> height;
                cin.ignore();

                if (height <= 0) {
                    cout << "Количество строк должно быть положительным числом. Попробуйте еще раз." << endl;
                }
                else if (height > text.length()) {
                    cout << "Количество строк не может быть больше чем длина текста ("
                        << text.length() << "). Введите еще раз." << endl;
                }
                else {
                    validInput = true;
                }
            }

            EncodingInfo = "skitala:" + to_string(height);
            EncodedText = SkitalaEncoded(text, height);
            break;
        }
        case 3: { // Виженер
            string key;
            while (true) {
                cout << "Введите ключ-слово (только буквы, без цифр): ";
                getline(cin, key);

                bool hasDigit = false;
                for (char c : key) {
                    if (c >= '0' && c <= '9') {  // Если нашли цифру
                        hasDigit = true;
                        break;
                    }
                }

                if (hasDigit) {
                    cout << "Ошибка: ключ не должен содержать цифры!\n";
                }
                else if (key.empty()) {
                    cout << "Ошибка: ключ не может быть пустым!\n";
                }
                else {
                    break;  // Ключ корректен
                }
            }

            EncodingInfo = "vigenere:" + key;
            EncodedText = VizhenerEncode(text, key);
            break;
        }
        default:
            cout << "Неверный метод!" << endl;
            return;
        }

        // Запись в файл
        ofstream file(fileName);
        file << EncodingInfo << endl << EncodedText;
        cout << "Файл успешно сохранен!" << endl;
    }
    //    else {
    //        exit(0);
    //        // Запись в файл без шифрования
    //        /*ofstream file(fileName);
    //        file << text; 
    //        cout << "Файл успешно сохранен!" << endl;*/
    //    }
}

int main() {
    setlocale(LC_ALL, "ru");
    if (!checkPassword()) {
        cout << "Неверный пароль! Выход из программы." << endl;
        return 1;
    }

    while (true) {
        printMainMenu();
        int choice;
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
        case 1:
            createFile();
            break;
        case 2:
            displayFile();
            break;
        case 3:
            cout << "Выход из программы." << endl;
            return 0;
        default:
            cout << "Неверный выбор! Попробуйте снова." << endl;
        }
    }
}

