//
// Created by iamthewalrus on 3/27/22.
//

#include "word_count.h"
#include <unordered_map>
#include <string>
#include <cstring>
#include <mutex>
#include <vector>
#include <cctype>
#include <functional>

void count_words(const std::string & contents, std::unordered_map<std::string, size_t> & global_map, std::mutex & m) {
    std::unordered_map<std::string, size_t> local_map;
    const char* delims = "\n\t\r\f ";
    char* token = std::strtok(const_cast<char*>(contents.c_str()), delims);

    std::vector<const char*> split_string_vector;
    while (token != nullptr) {
        split_string_vector.push_back(token);
        token = std::strtok(nullptr, delims);
    }

    for (const auto cstr: split_string_vector) {
        std::string str{cstr};
        str.erase(
                std::remove_if(str.begin(), str.end(), std::not1(std::ptr_fun(::isalpha))),
                str.end());
        ++local_map[str];
    }

    m.lock();
    for (const auto & item: local_map) {
        global_map[item.first] += item.second;
    }
    m.unlock();
}