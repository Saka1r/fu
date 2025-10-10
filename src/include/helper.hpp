#ifndef HELPER_HPP
#define HELPER_HPP

#include <iostream>

inline void help()
{
    std::cout << "fu commands: " << std::endl;
    std::cout << "init: - Initilization repo" << std::endl;
    std::cout << "add [FLAG]: - This command updates the index using the current content" << std::endl;
    std::cout << "commit - This command updates the HEAD using content in index" << std::endl;
    std::cout << "back [FLAG] - This command allows you to roll back to the previous commit" << std::endl;
}

#endif /*HELPER*/
