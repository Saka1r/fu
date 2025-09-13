#include <print>
#include <string>
#include <filesystem>
#include "include/file.hpp"

int inspect_file_or_dir(std::string target)
{
    std::filesystem::path Path(target);

    if (std::filesystem::exists(Path)) {
        if (std::filesystem::is_directory(Path)){
            return 1;
        }
        else if (std::filesystem::is_regular_file(Path)){
            return 0;
        } else;

    } else{
        std::println("Unknown: file does not exist");
        return 3;}
    return 4; 
}

void add(std::string target)
{
    int out = inspect_file_or_dir(target);
    if(out == 0)
        std::string result = read_file(target);
}