#include "include/commit.hpp"
#include "include/file.hpp"
#include "include/sha1.hpp"

#include <print>

void commit(std::string message)
{
    std::string file_text;
    std::string content;

    file_text = read_file(".fu/index");
    content = "commit\nmessage: " + message + "\n" + file_text;
    SHA1 hash;
    hash.update(content);
    auto name_file = hash.final();
    auto result = write_commit(name_file, content);
    if (result == 1)
        std::println("Error: failed to create a commit");
    else
        write_commit_list(name_file);
}
