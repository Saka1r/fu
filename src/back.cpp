#include "include/back.hpp"
#include "include/file.hpp"
#include "include/decoder.hpp"

#include <string>
#include <sstream>
#include <map>
#include <print>
#include <iostream>

std::string read_commit(std::string name_commit)
{
    std::string path = ".fu/commits/" + name_commit;
    auto content = read_file(path);
    std::istringstream input(content);
    std::ostringstream output;
    std::string line;

    while (std::getline(input, line)) {
        // Пропускаем строки с commit и message
        if (line.starts_with("commit") || line.starts_with("message")) {
            continue;
        }

        // Записываем оставшиеся строки в выходной поток
        output << line << std::endl;
    }

    std::string result = output.str(); // Получаем результат в виде строки
    return result; 
}

void back_files()
{
    std::string content = read_file(".fu/index");
    //std::cout << "Content of .fu/index: " << content << std::endl;

    std::map<std::string, std::string> key_value;
    std::istringstream stream(content);
    std::string line;

    while (std::getline(stream, line)) {
        std::istringstream iss(line);
        std::string key, value;

        // Извлекаем ключ и значение, разделенные пробелом
        if (iss >> key >> value) {
            key_value[key] = value; // Сохраняем в map
        }
    }

    // Выводим ключи и значения 
    for (const auto& [key, value] : key_value) {
        //std::cout << "Key: " << key << ", Value: " << value << std::endl;
        std::string blob_content = read_blob(value);
        std::string _content = decompress_string(blob_content);
        int result = overwrite_file(key, _content);
        if (result != 0) {
            std::cerr << "Error writing to file: " << key << std::endl;
        }
    }

}

void test()
{
    std::string originalData = "This is a test string for compression.";
    std::string compressedData = compress_string(originalData);
    std::cout << "Compressed data size: " << compressedData.size() << std::endl;

    int writeResult = write_blob("test_blob", compressedData);
    if (writeResult != 0) {
        std::cerr << "Error writing blob." << std::endl;
    }

    std::string readData = read_blob("test_blob");
    std::cout << "Read data size: " << readData.size() << std::endl;

    std::string decompressedData = decompress_string(readData);
    std::cout << "Decompressed data: " << decompressedData << std::endl;

}

void roll_back(std::string name_commit)
{
    write_commit_head(name_commit);
    auto content = read_commit(name_commit);
    int result = overwrite_index(content);
    if (result == 1){
        std::print("Error overwrite index");}
    else {
        back_files();}

}
