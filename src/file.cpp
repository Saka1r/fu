#include <fstream>
#include <string>
#include "include/file.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string read_file(const std::string& target) {
    std::ifstream file(target);
    if (!file.is_open()) {
        std::cerr << "The file could not be opened" << std::endl;
        return ""; // Возрат пустой строки в случаии ошибки!
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}

int write_blob(std::string name_blob, std::string content_blob) {
    std::ofstream file;
    file.open(".fu/index");
    std::string text = name_blob + " " + content_blob;
    if (!file.is_open())
        return 1;
    if (file.is_open()){
        file << text << std::endl;
    }
    file.close();
    return 0;
}
