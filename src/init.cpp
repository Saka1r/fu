#include <fstream>
#include <print>
#include <filesystem>

void create_index_file()
{
    std::ofstream file;
    file.open(".fu/index");
    if(file.is_open()){
        file << "" << std::endl;
    }
    file.close();
}

bool create_repo_dir()
{
    auto result = std::filesystem::create_directory(".fu");
    if (result == false){
        std::println("The repository is already initialized");
        return result;
    }
    else {
        std::println("Create Repo XD");
        return result;
    }
}

void init_repo()
{
    auto result = create_repo_dir();
    if (result == 1){
        create_index_file();
    }
}