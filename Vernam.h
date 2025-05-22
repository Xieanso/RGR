#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string VernamEncoded(const string& text, unsigned int key);
string VernamDecoded(const string& encoded, unsigned int key);
