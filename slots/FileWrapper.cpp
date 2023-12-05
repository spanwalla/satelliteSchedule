//
// Created by wwwod on 18.11.2023.
//

#include "FileWrapper.h"

FileWrapper::FileWrapper(const std::string& filename, std::ios_base::openmode mode) : file(filename, mode) {
    using namespace std::string_literals;
    if (!file.is_open())
        throw std::runtime_error("Unable to open "s + filename);
}

FileWrapper::~FileWrapper() {
    file.close();
}

void FileWrapper::write(const Slot& object){
    file << "\n[" << object.interval.first << ", " << object.interval.second << "] Actions: ";
    for (int i = 0; i < object.chosen_actions.size(); ++i) {
        file << "Satellite-KinoSat_" << object.chosen_actions[i].first;
        if (object.chosen_actions[i].second.empty())
            file << " shooting." << std::endl;
        else
            file << " transfers to " << object.chosen_actions[i].second << "." << std::endl;
    }
}

std::string FileWrapper::readLine() {
    std::string result;
    if (std::getline(file, result))
        return FileWrapper::trim(result);
    else if (!end())
        throw std::invalid_argument("Unable to read file.");
    return "";
}

std::string FileWrapper::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n");

    if (start == std::string::npos)
        return "";

    size_t end = str.find_last_not_of(" \t\n");

    return str.substr(start, end - start + 1);
}

bool FileWrapper::end() {
    return file.eof();
}