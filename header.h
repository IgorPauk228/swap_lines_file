#include <iostream>
#include <cstdint>
#include <fstream>
#include <utility>

#include <string>

#ifndef LABA_H
#define LABA_H

#define max_min_t std::pair<size_t, size_t> 

//Функции проверки
//Существование файла
void file_exists(const std::string& filename);

//Проверка на пустоту
bool is_empty(const std::string& filename);

//Проверка на открытие(ifstream)
void open_input_file(std::ifstream& fin, const std::string& filename);

//Проверка на открытие(fstream)
void open_input_file(std::fstream& fin, const std::string& filename);

//найти слово макс\мин длины в строке, вернуть индекс
max_min_t get_mx_mn_len(const std::string& str, const std::string& delims);

//найти слово макисамальной длины, вернуть индекс строки
max_min_t get_mx_mn_num(const std::string& filename, const std::string& delims);

//Функция свапа 2-х символов в файле
void swap_chars(std::fstream& fst, 
                std::streamoff pos1, 
                std::streamoff pos2);

//Функция реверса файла с позиции старт, определенной длины
void reverse_file(std::fstream& fst, size_t start, size_t length);

//Функция для swap 2-х строк в файле
void swap_strings(const std::string& filename, size_t idx1, size_t idx2);



#endif
