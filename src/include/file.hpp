#ifndef FILE_HPP
#define FILE_HPP

#include <string>

std::string read_file(const std::string& name_file);
int write_blob(std::string name_blob, std::string content);
int write_blob_index(std::string name_blob, std::string content);
int write_commit(std::string name_commit, std::string content);

#endif /*FILE_HPP*/
