#include <fstream>
#include <print>
#include <string>
#include <vector>
#include "include/file.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string read_file(const std::string& name_file) {
    std::ifstream file(name_file);
    if (!file.is_open()) {
        std::cerr << "The file could not be opened" << std::endl;
        return ""; // Возрат пустой строки в случаии ошибки!
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}

int write_file();
