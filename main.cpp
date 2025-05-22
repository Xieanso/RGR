#include <iostream>
#include <fstream>
#include <string>
#include "Vernam.h"
#include "Skitala.h"
#include "Vizhener.h"

using namespace std;

// ������� �������� ������
bool checkPassword() {
    string password;
    cout << "������� ������: ";
    getline(cin, password);
    return password == "password"; // ������ �� ���������
}

// ������� ������ �������� ����
void printMainMenu() {
    cout << "\n======= ������� ���� =======" << endl;
    cout << "1. ������� ����� ����" << endl;
    cout << "2. ������� ����� �� �����" << endl;
    cout << "3. �����" << endl;
    cout << "============================" << endl;
    cout << "��� �����: ";
}

void displayFile() {
    string fileName;
    cout << "������� ��� �����: ";
    getline(cin, fileName);

    ifstream file(fileName);
    if (file.is_open()) {
        string EncodingInfo; // ���������� � ������ ����������
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

        cout << "������������� �����:" << endl;
        cout << EncodedText << endl;

        cout << "\n�����������?" << endl;
        cout << "1. ��" << endl;
        cout << "2. ���" << endl;
        int choice;
        cin >> choice;
        cin.ignore(); // ������� ������ �����

        if (choice == 1) {
            string DecodedText;
            if (EncodingInfo.find("vernam:") == 0) {
                unsigned int key = stoi(EncodingInfo.substr(7));
                DecodedText = VernamDecoded(EncodedText, key);
            }
            else if (EncodingInfo.find("vigenere:") == 0) {
                string key = EncodingInfo.substr(9); // ��������� ���� 
               // cout << "������������ ����:" << key  << endl; 
                DecodedText = VizhenerDecode(EncodedText, key);
            }
            else if (EncodingInfo.find("skitala:") == 0) {
                int height = stoi(EncodingInfo.substr(8)); // ��������� ������
                DecodedText = SkitalaDecoded(EncodedText, height);
            }
            else {
                cout << "�������� ����� ����������!" << endl;
                return;
            }

            cout << "������������� �����:" << endl;
            cout << DecodedText << endl;
        }
    }
    else {
        cout << "������: ���� �� ���������� ��� �� ����� ���� ������!" << endl;
    }
}

// ������� �������� �����
void createFile() {
    string fileName, text;
    cout << "������� �������� �����: ";
    getline(cin, fileName);

    cout << "������� �����: ";
    getline(cin, text);

    cout << "\n�����������?" << endl;
    cout << "1. ��" << endl;
    cout << "2. ���" << endl;
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        cout << "\n�������� ����� ����������:" << endl;
        cout << "1. ���� �������" << endl;
        cout << "2. ���� �������" << endl;
        cout << "3. ���� ��������" << endl;
        int method;
        cin >> method;
        cin.ignore();

        string EncodedText;
        string EncodingInfo; // ���������� � ������ ����������

        switch (method) {
        case 1: { // ������
            unsigned int key;
            while (true) {
                cout << "������� ���� ";
                if (cin >> key) {
                    cin.ignore(); // ������� ������
                    break;
                }
                else {
                    cout << "������: ������� ����� �����." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
            }

            EncodingInfo = "vernam:" + to_string(key);
            EncodedText = VernamEncoded(text, key);
            break;
        }

        //case 1: { // ������
        //    int shift;
        //    while (true) {
        //        cout << "������� �����: ";
        //        if (cin >> shift) {
        //            cin.ignore(); // ������� ������ �����
        //            break;
        //        }
        //        else {
        //            cout << "�������� �����: " << endl;
        //            cin.clear();
        //            cin.ignore(); 
        //        }
        //    }

        //    EncodingInfo = "caesar:" + to_string(shift);
        //    EncodedText = caesarEncoded(text, shift);
        //    break;
        //}

        case 2: { // �������
            int height;
            bool validInput = false;
            while (!validInput) {
                cout << "������� ���������� �����: ";
                cin >> height;
                cin.ignore();

                if (height <= 0) {
                    cout << "���������� ����� ������ ���� ������������� ������. ���������� ��� ���." << endl;
                }
                else if (height > text.length()) {
                    cout << "���������� ����� �� ����� ���� ������ ��� ����� ������ ("
                        << text.length() << "). ������� ��� ���." << endl;
                }
                else {
                    validInput = true;
                }
            }

            EncodingInfo = "skitala:" + to_string(height);
            EncodedText = SkitalaEncoded(text, height);
            break;
        }
        case 3: { // �������
            string key;
            while (true) {
                cout << "������� ����-����� (������ �����, ��� ����): ";
                getline(cin, key);

                bool hasDigit = false;
                for (char c : key) {
                    if (c >= '0' && c <= '9') {  // ���� ����� �����
                        hasDigit = true;
                        break;
                    }
                }

                if (hasDigit) {
                    cout << "������: ���� �� ������ ��������� �����!\n";
                }
                else if (key.empty()) {
                    cout << "������: ���� �� ����� ���� ������!\n";
                }
                else {
                    break;  // ���� ���������
                }
            }

            EncodingInfo = "vigenere:" + key;
            EncodedText = VizhenerEncode(text, key);
            break;
        }
        default:
            cout << "�������� �����!" << endl;
            return;
        }

        // ������ � ����
        ofstream file(fileName);
        file << EncodingInfo << endl << EncodedText;
        cout << "���� ������� ��������!" << endl;
    }
    //    else {
    //        exit(0);
    //        // ������ � ���� ��� ����������
    //        /*ofstream file(fileName);
    //        file << text; 
    //        cout << "���� ������� ��������!" << endl;*/
    //    }
}

int main() {
    setlocale(LC_ALL, "ru");
    if (!checkPassword()) {
        cout << "�������� ������! ����� �� ���������." << endl;
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
            cout << "����� �� ���������." << endl;
            return 0;
        default:
            cout << "�������� �����! ���������� �����." << endl;
        }
    }
}

