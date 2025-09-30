#include <string>
#include <vector>

#include "include/objects.hpp"
#include "include/sha1.hpp"
#include "include/file.hpp"
#include "include/decoder.hpp"

std::string compress_blob(std::vector<std::string> file_text)
{    
    std::string combinedText;

    for (const auto& text : file_text) {
        combinedText += text + "\n"; // Объединяем текст с разделителем
    }

    std::string content = compress_string(combinedText); // Сжимаем объединенный текст
    return content; 
}

int create_blob(std::vector<std::string> file_text, std::string name_file, int flag)
{
    std::string combinedText;

    for (const auto& text : file_text) {
        combinedText += text + "\n"; // Объединяем текст с разделителем
    }
    
    std::string content = compress_string(combinedText); // Сжимаем объединенный текст
 
    
    SHA1 checksum;
    checksum.update(content);
    
    auto name_blob = checksum.final();
    
    auto result = write_blob(name_blob, content);
    if (flag == 0)
        write_blob_index(name_file, name_blob);
    else 
        write_blob(name_blob, content);
    return 0;
}
int create_tree(std::vector<std::string> blobs);
