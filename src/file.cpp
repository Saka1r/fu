#include <fstream>
#include <string>
#include "include/file.hpp"

#include <iostream>
#include <print>
#include <sstream>

std::string read_file(const std::string& target) {
    std::ifstream file(target, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "The file could not be opened" << std::endl;
        return ""; // Возрат пустой строки в случаии ошибки!
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}

std::string read_blob(const std::string& name_blob) {
    std::string path = ".fu/blobs/" + name_blob;
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open blob file: " + path);
    }
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}


int write_blob(std::string name_blob, std::string content_blob) {
    
    std::string path = ".fu/blobs/" + name_blob;

    std::ofstream file(path, std::ios::binary);
    std::string text = content_blob;
    if (!file.is_open())
        return 1;

    file.write(content_blob.data(), content_blob.size());

    file.close();
    return 0;
}

int write_blob_index(std::string name_file, std::string name_blob) {
   
    std::ifstream file_read(".fu/index", std::ios::binary);
    if (!file_read.is_open()) {
        std::cerr << "The file could not be opened" << std::endl;
        return 1; 
    }

    std::stringstream buffer;
    buffer << file_read.rdbuf();
    file_read.close();


    std::ofstream file_write(".fu/index", std::ios::binary);
    std::string text = buffer.str() + "\n" + name_file + " " + name_blob;

    if (!file_write.is_open())
        return 1;
    if (file_write.is_open()){
        file_write << text;
    }
    file_write.close();

    return 0;
}

int write_commit_head(std::string name_commit)
{
    std::ofstream file_write(".fu/HEAD", std::ios::binary);

    if (!file_write.is_open())
        return 1;
    if (file_write.is_open()){
        file_write << name_commit;
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
        file_write << content;
    }

    file_write.close();
    auto result = write_commit_head(name_commit);
    if (result == 1)
        std::println("Error write commit in HEAD");
    return 0; 
}

int write_commit_list(std::string name_commit) {
   
    std::ifstream file_read(".fu/LIST", std::ios::binary);
    if (!file_read.is_open()) {
        std::cerr << "The file could not be opened" << std::endl;
        return 1; 
    }

    std::stringstream buffer;
    buffer << file_read.rdbuf();
    file_read.close();


    std::ofstream file_write(".fu/LIST", std::ios::binary);

    std::string text = buffer.str() + "\n" + name_commit;

    if (!file_write.is_open())
        return 1;
    if (file_write.is_open()){
        file_write << text;
    }
    file_write.close();

    return 0;
}

int overwrite_index(std::string content)
{
    std::ofstream file_write(".fu/index", std::ios::binary);

    if (!file_write.is_open())
        return 1;
    if (file_write.is_open()){
        file_write << content;
    }
    file_write.close();

    return 0;
}

int overwrite_file(std::string target, std::string content)
{
    std::ofstream file_write(target, std::ios::binary); // Открываем файл в бинарном режиме

    if (!file_write.is_open()) {
        return 1; 
    }

    file_write << content; 
    file_write.close(); 

    return 0; 
}