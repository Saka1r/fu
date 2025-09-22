#ifndef HELPER_HPP
#define HELPER_HPP

#include <print>

inline void help()
{
    std::println("fu commands: ");
    std::println("init: - Initilization repo");
    std::println("add [FLAG]: - This command updates the index using the current content");
    std::println("commit - This command updates the HEAD using content in index");
}

#endif /*HELPER*/
