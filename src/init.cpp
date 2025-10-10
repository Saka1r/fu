#include <fstream>
#include <iostream>
#include <filesystem>

void create_commit_list_file()
{
    std::ofstream file;
    file.open(".fu/LIST");
    if(file.is_open()){
        file << "" << std::endl;
    }
    file.close();

}

void create_head_file()
{
    std::ofstream file;
    file.open(".fu/HEAD");
    if(file.is_open()){
        file << "" << std::endl;
    }
    file.close();

}

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
        std::cout << "The repository is already initialized" << std::endl;
        return result;
    }
    else {
        std::filesystem::create_directory(".fu/blobs");
        std::filesystem::create_directory(".fu/commits");
        //std::filesystem::create_directory(".fu/user");

        std::cout << "Create Repo XD" << std::endl;
        return result;
    }
}

void init_repo()
{
    auto result = create_repo_dir();
    if (result == 1){
        create_index_file();
        create_head_file();
        create_commit_list_file();
    }
}
