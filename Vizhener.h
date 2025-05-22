#ifndef Vizhener_H
#define Vizhener_H
#include<string>


int keycode(char s);

std::string VizhenerEncode(std::string text, std::string key);

std::string VizhenerDecode(std::string text, std::string key);

#endif