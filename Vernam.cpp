#include <iostream>
#include <string>
#include <cstdlib> // Äëÿ srand è rand

using namespace std;

// Ôóíêöèÿ øèôðîâàíèÿ Âåðíàìîì ñ êëþ÷îì (seed)
string VernamEncoded(const string& text, unsigned int key) {
    string encoded;
    srand(key); // Èíèöèàëèçàöèÿ ãåíåðàòîðà ñëó÷àéíûõ ÷èñåë êëþ÷îì
    for (char ch : text) {
        char k = rand() % 256;
        encoded += ch ^ k;
    }
    return encoded;
}

// Ôóíêöèÿ äåøèôðîâêè Âåðíàìîì ñ êëþ÷îì (seed)
string VernamDecoded(const string& encoded, unsigned int key) {
    string decoded;
    srand(key); // Èíèöèàëèçàöèÿ ãåíåðàòîðà òåì æå êëþ÷îì
    for (char ch : encoded) {
        char k = rand() % 256;
        decoded += ch ^ k;
    }
    return decoded;
}



