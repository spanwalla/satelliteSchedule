//
// Created by wwwod on 18.11.2023.
//

#ifndef SATELLITESCHEDULE_PARSER_H
#define SATELLITESCHEDULE_PARSER_H

#include <stdexcept>
#include <string>
#include <fstream>

class Parser {
public:
    explicit Parser(const std::string& filename);
    ~Parser();
    std::string parseLine();
private:
    std::ifstream file;
    int parsed;

    static std::string trim(const std::string& str); // убрать пробелы, табуляцию и перенос строк по краям строки
};


#endif //SATELLITESCHEDULE_PARSER_H
