#include <cstring>
#include <print>
#include "include/init.hpp"
#include "include/add.hpp"
#include "include/helper.hpp"

int main(int argc, char* argv[])
{
    if(argc >= 2){
        if(strcmp(argv[1], "init") == 0)
            init_repo();
        else{
            std::println("Unknown team: {}", argv[1]);
            help();
        }
    }
    else{
        help();
    }
    
    return 0;
}