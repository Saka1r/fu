#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <string>
#include <vector>

int create_blob(std::vector<std::string> file_text, std::string name_file);
int create_tree(std::vector<std::string> blobs);
int create_commit(std::vector<std::string> trees);

#endif /*OBJECTS_HPP*/
