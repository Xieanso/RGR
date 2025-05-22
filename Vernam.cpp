#include <iostream>
#include <string>
#include <cstdlib> // Для srand и rand

using namespace std;

// Функция шифрования Вернамом с ключом (seed)
string VernamEncoded(const string& text, unsigned int key) {
    string encoded;
    srand(key); // Инициализация генератора случайных чисел ключом
    for (char ch : text) {
        char k = rand() % 256;
        encoded += ch ^ k;
    }
    return encoded;
}

// Функция дешифровки Вернамом с ключом (seed)
string VernamDecoded(const string& encoded, unsigned int key) {
    string decoded;
    srand(key); // Инициализация генератора тем же ключом
    for (char ch : encoded) {
        char k = rand() % 256;
        decoded += ch ^ k;
    }
    return decoded;
}



//#include <iostream>
//#include <string>
//#include <cstdlib> // Для srand и rand
//
//using namespace std;
//
//string Vernam_encoding(string& text) {
//    srand(0);
//    string key = "";
//    for (size_t i = 0; i < text.length(); ++i) {
//        key += (char)(rand() % 256);
//    }
//    string newtext = "";
//    for (size_t i = 0; i < text.length(); ++i) {
//        newtext += (text[i] ^ key[i]);
//    }
//    return newtext;
//}
//
//string Vernam_decoding(string& text) {
//    srand(0);
//    string key = "";
//    for (size_t i = 0; i < text.length(); ++i) {
//        key += (char)(rand() % 256);
//    }
//    string newtext = "";
//    for (size_t i = 0; i < text.length(); ++i) {
//        newtext += (text[i] ^ key[i]);
//    }
//    return newtext;
//}

//#include "Vernam.h"
//
//using namespace std;
//
//void Vernam_encoding(string& name) {
//	srand(0);
//	ifstream fout(name);
//	ofstream fin("Encoded.txt");
//	while (!fout.eof()) {
//		string text = "";
//		getline(fout, text);
//		string key = "";
//		int i = 0;
//		for (i = 0; text[i] != '\0'; i++) {
//			key += (char)(rand() % 255);
//		}
//		string newtext = "";
//		for (i = 0; text[i] != '\0'; i++) {
//			newtext += (text[i] ^ key[i]);
//		}
//		fin << newtext;
//		if (!fout.eof()) {
//			fin << endl;
//		}
//	}
//	fout.ignore();
//}
//
//void Vernam_decoding(string& name) {
//	srand(0);
//	ifstream fout(name);
//	ofstream fin("Decoded.txt");
//	while (!fout.eof()) {
//		string text = "";
//		getline(fout, text);
//		string key = "";
//		int i = 0;
//		for (i = 0; text[i] != '\0'; i++) {
//			key += (char)(rand() % 255);
//		}
//		string newtext = "";
//		for (i = 0; text[i] != '\0'; i++) {
//			newtext += (text[i] ^ key[i]);
//		}
//		fin << newtext;
//		if (!fout.eof()) {
//			fin << endl;
//		}
//	}
//	fout.ignore();
//}