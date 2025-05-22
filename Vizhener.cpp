#include "Vizhener.h"
#include <iostream>
#include <string>

using namespace std;

string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// функция получения кода символа 
int keycode(char s) {
    s = toupper(s);
    for (int i = 0; i < alphabet.length(); i++) {
        if (s == alphabet[i]) return i;
    }
    return -1;   // возвращает - 1 для символов не из алфавита
}

string VizhenerEncode(string text, string key) {
    string code;
    for (int i = 0; i < text.length(); i++) {
        char c = text[i];
        char k = key[i % key.length()];

        // Преобразуем в заглавные
        c = toupper(c);
        k = toupper(k);

        int c_code = keycode(c);
        int k_code = keycode(k);

        if (c_code == -1 || k_code == -1) { 
            code += text[i];  
        }
        else {
            code += alphabet[(c_code + k_code) % alphabet.length()];
        }
    }
    return code;
}

string VizhenerDecode(string text, string key) {
    string code;
    for (int i = 0; i < text.length(); i++) {
        char c = text[i];
        char k = key[i % key.length()];

        c = toupper(c);
        k = toupper(k);

        int c_code = keycode(c);
        int k_code = keycode(k);

        if (c_code == -1 || k_code == -1) {  
            code += text[i];  
        }
        else {
            code += alphabet[(c_code - k_code + alphabet.length()) % alphabet.length()];
        }
    }
    return code;
}











//#include "Vizhener.h"
//#include <iostream>
//#include <string>
//
//using namespace std;
//
//string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//
//// функция получения кода символа
//int keycode(char s) {
//    for (int i = 0; i < alphabet.length(); i++) {
//        if (s == alphabet[i]) return i;
//    }
//    return 0;
//}
//
//string VizhenerEncode(string text, string key) {
//    string code;
//    for (int i = 0; i < text.length(); i++) {
//        char c = text[i];
//        char k = key[i % key.length()];
//
//        // Преобразуем в заглавные 
//        c = toupper(c);
//        k = toupper(k);
//
//        int c_code = keycode(c);
//        int k_code = keycode(k);
//
//        if (c_code == 0 || k_code == 0) {
//            // Обработка символов, отсутствующих в алфавите
//            code += c; // Просто добавляем исходный символ
//        }
//        else {
//            code += alphabet[(c_code + k_code) % alphabet.length()];
//        }
//    }
//    return code;
//}
//
//string VizhenerDecode(string text, string key) {
//    string code;
//    for (int i = 0; i < text.length(); i++) {
//        char c = text[i];
//        char k = key[i % key.length()];
//
//       
//        c = toupper(c);
//        k = toupper(k);
//
//        int c_code = keycode(c);
//        int k_code = keycode(k);
//
//        if (c_code == 0 || k_code == 0) {
//            
//            code += c; 
//        }
//        else {
//            code += alphabet[(c_code - k_code + alphabet.length()) % alphabet.length()];
//        }
//    }
//    return code;
//}