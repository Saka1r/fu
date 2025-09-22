#include <fstream>
#include <string>
#include "include/file.hpp"

#include <iostream>
#include <print>
#include <sstream>

std::string read_file(const std::string& target) {
    std::ifstream file(target);
    if (!file.is_open()) {
        std::cerr << "The file could not be opened" << std::endl;
        return ""; // Возрат пустой строки в случаии ошибки!
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}

int write_blob(std::string name_blob, std::string content_blob) {
    
    std::string path = ".fu/blobs/" + name_blob;

    std::ofstream file;
    file.open(path);
    std::string text = "blob " + content_blob;
    if (!file.is_open())
        return 1;
    if (file.is_open()){
        file << text << std::endl;
    }
    file.close();
    return 0;
}

int write_blob_index(std::string name_file, std::string name_blob) {
   
    std::ifstream file_read(".fu/index");
    if (!file_read.is_open()) {
        std::cerr << "The file could not be opened" << std::endl;
        return 1; 
    }

    std::stringstream buffer;
    buffer << file_read.rdbuf();
    file_read.close();


    std::ofstream file_write;
    file_write.open(".fu/index");
    std::string text = buffer.str() + "\n" + name_file + " " + name_blob;

    if (!file_write.is_open())
        return 1;
    if (file_write.is_open()){
        file_write << text << std::endl;
    }
    file_write.close();

    return 0;
}

int write_commit_head(std::string name_commit)
{
    std::ofstream file_write;
    file_write.open(".fu/HEAD");

    if (!file_write.is_open())
        return 1;
    if (file_write.is_open()){
        file_write << name_commit << std::endl;
    }

    file_write.close();
    return 0; 
}

int write_commit(std::string name_commit, std::string content)
{

    std::string path = ".fu/commits/" + name_commit;

    std::ofstream file_write;
    file_write.open(path);

    if (!file_write.is_open())
        return 1;
    if (file_write.is_open()){
        file_write << content << std::endl;
    }

    file_write.close();
    auto result = write_commit_head(name_commit);
    if (result == 1)
        std::println("Error write commit in HEAD");
    return 0; 
}

