#include <fstream>
#include <print>
#include <string>
#include <vector>
#include "include/file.hpp"

int read_file(std::string name_file){

    std::string line;
    std::vector<std::string> text;

    std::ifstream file(name_file);
    if(file.is_open()){
        while(std::getline(file, line)){
            text.push_back(line);
        }
        file.close();
    } else
        std::println("The file clout not be opened");
    
    return 0;
}
int write_file();
