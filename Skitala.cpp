#include "Skitala.h"
#include <string>
#include <iostream>

// Функция шифрования методом Скиталы
std::string SkitalaEncoded(const std::string& text, int height) {
    std::string newtext = "";
    // Вычисляем ширину матрицы (количество столбцов)
    size_t width = (text.size() - 1) / height + 1;

    // Заполняем зашифрованный текст по столбцам
    for (size_t j = 0; j < width; ++j) {
        for (size_t i = 0; i < height; ++i) {
            // Если символ существует в исходном тексте - добавляем его
            if (i * width + j < text.size()) {
                newtext += text[i * width + j];
            }
            // Иначе заполняем символом '*'
            else {
                newtext += '*';
            }
        }
    }
    return newtext;
}

// Функция дешифрования метода Скиталы
std::string SkitalaDecoded(const std::string& text, int height) {
    std::string newtext = "";
    std::string temp_text = text; // Рабочая копия зашифрованного текста

    // Процесс обратного преобразования матрицы
    while (temp_text != "") {
        size_t i = 0;
        while (i < temp_text.size()) {
            // Пропускаем символы-заполнители
            if (temp_text[i] == '*') {
                temp_text.erase(i, 1);
            }
            else {
                // Добавляем символ в результат
                newtext += temp_text[i];
                temp_text.erase(i, 1);
            }

            // Корректируем шаг для чтения по строкам
            if (i + height - 1 >= temp_text.size()) {
                i = 0;
                if (height > 1) {
                    height--; // Уменьшаем высоту 
                }
                else {
                    break;
                }
            }
            else {
                i += height - 1; // Переходим к следующему символу в строке
            }
        }
    }
    return newtext;
}