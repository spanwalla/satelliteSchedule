//
// Created by wwwod on 18.11.2023.
//

#include "Parser.h"

Parser::Parser(const std::string& filename): file(filename), parsed(0) {
    using namespace std::string_literals;
    if (!file.is_open())
        throw std::runtime_error("Unable to open "s + filename);
}

Parser::~Parser() {
    file.close();
}

std::string Parser::parseLine() {
    std::string result;
    if (!std::getline(file, result))
        throw std::invalid_argument("Unable to read file.");
    ++parsed;
    return Parser::trim(result);
}

std::string Parser::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n");

    if (start == std::string::npos)
        return "";

    size_t end = str.find_last_not_of(" \t\n");

    return str.substr(start, end - start + 1);
}
