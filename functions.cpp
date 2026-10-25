#include <iostream>
#include <cstdint>
#include <fstream>
#include <utility>
#include <string>
#include <cassert>

#include "header.h"

#define max_min_t std::pair<size_t, size_t> 

//Функции проверки
//Существование файла
void file_exists(const std::string& filename){
    std::ifstream fin(filename);
    if (!fin.good()){
        throw "File not exists";
    }
}

//Проверка на пустоту
bool is_empty(const std::string& filename){
    std::ifstream file(filename);
    file.seekg(0, std::ios::end);
    return file.tellg() == 0;
}

//Проверка на открытие(ifstream)
void open_input_file(std::ifstream& fin, const std::string& filename){
    fin.open(filename);
    if (!fin.is_open()){
        throw "Can't open file"; 
    }
    if (fin.fail()){
        throw "Error with open file";
    }

    std::cout << "File succesfully opened\n";
}

//Проверка на открытие(fstream)
void open_input_file(std::fstream& fin, const std::string& filename){
    fin.open(filename);
    if (!fin.is_open()){
        throw "Can't open file"; 
    }
    if (fin.fail()){
        throw "Error with open file";
    }

    std::cout << "File succesfully opened";
}

//найти слово макс\мин длины в строке, вернуть длину
max_min_t get_mx_mn_len(const std::string& str, const std::string& delims){
    size_t mx_len = 0;
    size_t mn_len = str.length();

    size_t start = 0;
    size_t end = 0;

    size_t wrd_len = 0;
    size_t len = str.length();

    while (end < len){
        end = str.find_first_of(delims, start);
        if (end == std::string::npos) break;

        wrd_len = end - start - 1;

        if (wrd_len > mx_len){
            mx_len = wrd_len;
        }

        if (wrd_len < mn_len){
            mn_len = wrd_len;
        }

        start = str.find_first_not_of(delims, end);
        if (start == std::string::npos) break;
    }

    if (end == std::string::npos){
        wrd_len = len - 1 - start;
        if (wrd_len > mx_len){
            mx_len = wrd_len;
        }

        if (wrd_len < mn_len){
            mn_len = wrd_len;
        }
    }


    max_min_t buff{mx_len, mn_len};
    return buff;

}

//найти слово макисамальной|минимальной длины, вернуть индекс строки
max_min_t get_mx_mn_num(const std::string& filename, const std::string& delims){
    file_exists(filename);
    if (is_empty(filename)){
        throw "File is empty";
    }

    std::ifstream fin;
    open_input_file(fin, filename);


    size_t mx_idx = 0;
    size_t mn_idx = 0;

    size_t mx_len = 0;
    size_t mn_len = 0;

    size_t counter = 0;
    max_min_t buff{0, 0};

    std::string line;

    while(std::getline(fin, line)){
        buff = get_mx_mn_len(line, delims);
        if (counter == 0){
            mn_len = line.length();
        }

        if (buff.first > mx_len){
            mx_len = buff.first;
            mx_idx = counter;
        }

        if (buff.second < mn_len){
            mn_len = buff.second;
            mn_idx = counter;
        }

        ++counter;
    }

    buff.first = mx_idx;
    buff.second = mn_idx;

    fin.close();

    return buff;
}

void swap_chars(std::fstream& fst, 
                std::streamoff pos1, 
                std::streamoff pos2){
    if (pos1 == pos2) return;

    fst.clear();

    fst.seekg(pos1, std::ios::beg);
    char c1;
    if (!fst.get(c1)) throw "Index Error";


    fst.seekg(pos2, std::ios::beg);
    char c2;
    if (!fst.get(c2)) throw "Index Error";


    fst.seekp(pos1, std::ios::beg);
    fst.put(c2);
    if (!fst) throw "Index Error";


    fst.seekp(pos2, std::ios::beg);
    fst.put(c1);
    if (!fst) throw "Index Error";

    fst.clear();

}

void reverse_file(std::fstream& fst, size_t start, size_t length){
    size_t med = length / 2;
    for (size_t i = 0; i < med; ++i){
        swap_chars(fst, start + i, length + start - 1 - i);
    }
}

//Функция для swap 2-х строк в файле
void swap_strings(const std::string& filename, size_t idx1, size_t idx2){
    file_exists(filename);
    if (is_empty(filename)){
        throw "File is empty";
    }

    std::fstream fst(filename, std::ios::in | std::ios::out | std::ios::binary);
    
    if (!fst.is_open()){
        throw "Can't open file";
    }
    if (fst.fail()){
        throw "Error with open file";
    }

    if (idx1 > idx2){
        std::swap(idx1, idx2);
    }

    size_t pos1 = 0;
    size_t pos2 = 0;
    size_t pos = 0;

    size_t counter = 0;

    std::string line1;
    std::string line2;

    std::string line;

    while (std::getline(fst, line)){
        

        if (counter == idx1){
            line1 = line;
            pos1 = pos;
        }

        if (counter == idx2){
            line2 = line;
            pos2 = pos;
        }

        pos += line.length() + 1;
        ++counter;
    }

    reverse_file(fst, pos1, pos2 - pos1 + line2.length());
    reverse_file(fst, pos1, line2.length());
    pos2 = pos2 - line1.length() + line2.length();
    reverse_file(fst, pos2, line1.length());
    reverse_file(fst, pos1 + line2.length(), pos2 - pos1 - line2.length());

    fst.close();
}

