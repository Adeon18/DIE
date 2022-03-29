//
// Created by iamthewalrus on 3/27/22.
//

#include <deque>
#include <mutex>
#include <vector>
#include <cctype>
#include <string>
#include <cstring>
#include <functional>
#include "word_count.hpp"
#include "../mt_deque/mt_deque.hpp"
#include "../mt_unordered_map/mt_unordered_map_t.hpp"

void count_words(const std::string & contents, mt_unordered_map_t<std::string, size_t>& global_map) {
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
                std::remove_if(str.begin(), str.end(), [](char c){ return !(::isalpha(c)); }),
                str.end());
        ++local_map[str];
    }

    global_map.merge(local_map);
}

void index_files_from_deque(mt_deque_t<std::string>& mt_d_file_contents, mt_unordered_map_t<std::string, size_t>& global_map) {
    while (true) {
        auto file_contents = mt_d_file_contents.pop_back();

        if (file_contents.empty()) {
            mt_d_file_contents.push_front("");
            break;
        }

        count_words(file_contents, global_map);
    }
}
