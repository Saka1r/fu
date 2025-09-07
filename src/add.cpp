#include <print>
#include <string>
#include <filesystem>

void inspect_file_or_dir(std::string target)
{
    std::filesystem::path Path(target);

    if (std::filesystem::exists(Path)) {
        if (std::filesystem::is_directory(Path)){

        }
        else if (std::filesystem::is_regular_file(Path)){
        
        } else;

    } else 
        std::println("Unknown: file does not exist");
}

void add(std::string target)
{
    inspect_file_or_dir(target);

}