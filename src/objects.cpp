#include <cstdio>
#include <iostream>
#include <print>
#include <string>
#include <vector>
#include "zlib/zlib.h"

#include "include/objects.hpp"
#include "include/sha1.hpp"
#include "include/file.hpp"

std::string compressString(const std::string& str) {
    uLongf compressedSize = compressBound(str.size());
    std::string compressedData(compressedSize, '\0');

    if (compress(reinterpret_cast<Bytef*>(&compressedData[0]), &compressedSize,
                 reinterpret_cast<const Bytef*>(str.data()), str.size()) != Z_OK) {
        throw std::runtime_error("Compression failed");
    }

    compressedData.resize(compressedSize); // Уменьшаем размер до фактического размера
    return compressedData;
}

std::string decompressString(const std::string& compressedStr) {
    uLongf decompressedSize = compressedStr.size() * 4; // Предполагаем, что разжатый размер не превышает 4x
    std::string decompressedData(decompressedSize, '\0');

    while (uncompress(reinterpret_cast<Bytef*>(&decompressedData[0]), &decompressedSize,
        reinterpret_cast<const Bytef*>(compressedStr.data()), compressedStr.size()) == Z_BUF_ERROR) {
        decompressedSize *= 2; // Увеличиваем размер буфера
        decompressedData.resize(decompressedSize);
    }

    return decompressedData;
}

int create_blob(std::vector<std::string> file_text)
{
    std::string combinedText;
    for (const auto& text : file_text) {
        combinedText += text + "\n"; // Объединяем текст с разделителем
    }
    std::string content = compressString(combinedText); // Сжимаем объединенный текст
    std::println("{}", content);
    
    SHA1 checksum;
    checksum.update(content);
    auto name_blob = checksum.final();
    auto result = write_blob(name_blob, content);
    return 0;
}
int create_tree(std::vector<std::string> blobs);
int create_commit(std::vector<std::string> trees);
