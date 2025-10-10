#ifndef FILE_HPP
#define FILE_HPP

#include <string>

std::string read_file(const std::string& name_file);
std::string read_blob(const std::string& name_file);
int write_blob(std::string name_blob, std::string content);
int write_blob_index(std::string name_blob, std::string content);
int write_commit(std::string name_commit, std::string content);
int write_commit_list(std::string name_commit); 
int write_commit_head(std::string name_commit);
int overwrite_index(std::string content);
int overwrite_file(std::string target, std::string content);
#endif /*FILE_HPP*/
