#include <string>
#include <filesystem>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include <cstring>

#include "include/file.hpp"
#include "include/objects.hpp"
#include "include/sha1.hpp"
/*TODO
 * Нормально написать эту функцию и отформатировать... 
 * */
int check_add(std::string target, std::vector<std::string> target_text)
{

    // Открытие файла index
    std::ifstream indexFile(".fu/index");
    if (!indexFile.is_open()) {
        std::cerr << "Fatal open file: " << ".fu/index" << std::endl;
        return 1;
    }

    // Хранение соответствия между файлами и блобами
    std::unordered_map<std::string, std::string> fileBlobMap;
    std::string line;

    // Чтение содержимого файла index
    while (std::getline(indexFile, line)) {
        // Предполагаем, что формат строки: "file blob"
        size_t spacePos = line.find(' ');
        if (spacePos != std::string::npos) {
            std::string fileName = line.substr(0, spacePos);
            std::string blobHash = line.substr(spacePos + 1);
            fileBlobMap[fileName] = blobHash; // Сохраняем соответствие
        }
    }

    // Закрытие файла
    indexFile.close();

    // Пример: поиск блоба по имени файла
    std::string searchFileName = target; // Укажите имя файла для поиска
    auto it = fileBlobMap.find(searchFileName);
    if (it != fileBlobMap.end()) {
        //std::cout << "file and blob " << searchFileName << ": " << it->second << std::endl;
        
        std::string blob = it->second;
        std::string content = compress_blob(target_text);
        SHA1 checksum;
        checksum.update(content);
        std::string new_blob = checksum.final();
        if(blob == new_blob)
            return 1;
        else
        {
            std::string indexPath = ".fu/index";

            write_blob(new_blob, content);

            // Проверка существования файла index
            if (!std::filesystem::exists(indexPath)) {
                std::cerr << "File don't search: " << indexPath << std::endl;
                return 1;
            }

            std::ifstream indexFile(indexPath);
            if (!indexFile.is_open()) {
                std::cerr << "Fatal open file: " << indexPath << std::endl;
                return 1;
            }

            // Чтение содержимого файла и замена строки
            std::stringstream buffer;
            std::string line;
            std::string oldFileName = searchFileName;
            std::string newBlob = new_blob; 
            bool found = false;

            while (std::getline(indexFile, line)) {
                if (line.find(oldFileName) != std::string::npos) {
                // Заменяем строку с oldFileName на новую
                line = oldFileName + " " + newBlob;
                found = true;
                }   
            buffer << line << std::endl; // Сохраняем строку в буфер
            }
            
            indexFile.close();

            // Если файл был найден и изменён, записываем изменения обратно
            if (found) {
                std::ofstream outFile(indexPath);
                if (!outFile.is_open()) {
                std::cerr << "Fatal open file for write: " << indexPath << std::endl;
                return 1;
                }
            outFile << buffer.str(); // Записываем обновлённое содержимое
            outFile.close();
            }
            return 2;
        }}
    else {
        std::cout << "file " << searchFileName << " add to index" << std::endl;
        return 0;
    }
}

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
        std::cout << "Unknown: file does not exist" << std::endl;
        return 3;}
    return 4; 
}

void add(std::string target)
{
    int out = inspect_file_or_dir(target);
    if(out == 0){
        std::vector<std::string> text;
        std::string result = read_file(target);
        text.push_back(result);
        auto out = check_add(target, text);
        if (out == 0){
            auto s = create_blob(text, target, 0);
        }
        else if (out == 1){
            std::cout << "The new version of the file has already been registered" << std::endl;
        }
        else if (out == 2){
            std::cout << "The new version of the file add in index" << std::endl;
        }
   }
}
