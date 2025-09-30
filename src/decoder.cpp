#include "include/decoder.hpp"
#include "zlib/zlib.h"
#include "sha1.h"

#include <string>
#include <iostream>

std::string compress_string(const std::string& str) {
    uLongf compressedSize = compressBound(str.size());
    std::string compressedData(compressedSize, '\0');

    if (compress(reinterpret_cast<Bytef*>(&compressedData[0]), &compressedSize,
                 reinterpret_cast<const Bytef*>(str.data()), str.size()) != Z_OK) {
        throw std::runtime_error("Compression failed");
    }

    compressedData.resize(compressedSize); // Уменьшаем размер до фактического размера
    return compressedData;
}

std::string decompress_string(const std::string& compressedStr) {
    uLongf decompressed_size = compressedStr.size() * 4; // Начальный размер
    std::string decompressed_data(decompressed_size, '\0');

    int result = uncompress(reinterpret_cast<Bytef*>(&decompressed_data[0]), &decompressed_size,
                            reinterpret_cast<const Bytef*>(compressedStr.data()), compressedStr.size());

    // Если буфер недостаточен, увеличиваем его размер и пробуем снова
    while (result == Z_BUF_ERROR) {
        decompressed_size *= 2; // Увеличиваем размер буфера
        decompressed_data.resize(decompressed_size);
        result = uncompress(reinterpret_cast<Bytef*>(&decompressed_data[0]), &decompressed_size,
                            reinterpret_cast<const Bytef*>(compressedStr.data()), compressedStr.size());
    }

    if (result != Z_OK) {
        throw std::runtime_error("Decompression failed with error code: " + std::to_string(result));
    }

    decompressed_data.resize(decompressed_size); // Уменьшаем размер до фактического размера
    return decompressed_data;
}
