#include <cstring>
#include <print>
#include <iostream>

#include "include/init.hpp"
#include "include/add.hpp"
#include "include/helper.hpp"
#include "include/commit.hpp"
#include "include/back.hpp"

std::string read_all_input() {
    std::string input;
    std::string line;

    // Считываем строки до конца ввода
    while (std::getline(std::cin, line)) {
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
            std::println("No [FLAG] specified for add command.");
            help();
        }
    }
    else if (strcmp(argv[1], "commit") == 0) {
        std::string user_message;
        std::print("Message: ");
        user_message = read_all_input();
        commit(user_message);
    }
    else if (strcmp(argv[1], "back") == 0) {
        if (argc >= 3) {
            roll_back(argv[2]);
        } else {
            std::println("No [FLAG] specified for back command.");
            help();
        }
    }
    else {
        std::println("Unknown command: {}", argv[1]);
        help();}
    } else {
        std::println("Insufficient arguments.");
        help();}
    
    return 0;
}
