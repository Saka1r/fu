#include <cstring>
#include <iostream>

#include "include/init.hpp"
#include "include/add.hpp"
#include "include/helper.hpp"
#include "include/commit.hpp"
#include "include/back.hpp"

std::string read_all_input() {
    std::string input;
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) 
            break;
        input += line + " ";
    }

    return input;
}

int main(int argc, char* argv[])
{
    if (argc >= 2) {
    if (strcmp(argv[1], "init") == 0) {
        init_repo();
    } 
    else if (strcmp(argv[1], "add") == 0) {
        if (argc >= 3) {
            add(argv[2]);
        } else {
            std::cout << "No [FLAG] specified for add command." << std::endl;
            help();
        }
    }
    else if (strcmp(argv[1], "commit") == 0) {
        std::string user_message;
        std::cout << "Message: ";
        user_message = read_all_input();
        commit(user_message);
    }
    else if (strcmp(argv[1], "back") == 0) {
        if (argc >= 3) {
            roll_back(argv[2]);
        } else {
            std::cout << "No [FLAG] specified for back command.";
            help();
        }
    }
    else {
        std::cout << "Unknown command: ", argv[1];
        help();}
    } else {
        std::cout << "Insufficient arguments." << std::endl;
        help();}
    
    return 0;
}
