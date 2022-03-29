//
// Created by iamthewalrus on 3/27/22.
//

#include <deque>
#include <mutex>
#include <vector>
#include <cctype>
#include <string>
#include <fstream>
#include <cstring>
#include <iostream>
#include <functional>
#include "word_count.hpp"
#include "../mt_deque/mt_deque.hpp"
#include "../include/exit_codes.hpp"
#include <boost/algorithm/string.hpp>
#include "../mt_unordered_map/mt_unordered_map_t.hpp"

namespace word_count {
    /*
    * Count individual words in a string, merge their count with the global map
    */
    void count_words(const std::string & contents, mt_unordered_map::mt_unordered_map_t<std::string, size_t>& global_map) {
        std::unordered_map<std::string, size_t> local_map;
        auto first = std::cbegin(contents);
        std::string delims = "\n\t\r\f ";

        while (first != std::cend(contents)) {
            const auto second = std::find_first_of(first,
                                                std::cend(contents),
                                                std::cbegin(delims),
                                                std::cend(delims));

            if (first != second) {
                std::string str(first, second);
                boost::trim_if(str, [](char c) { return !std::isalpha(c); });
                std::transform(str.begin(), str.end(), str.begin(),
                        [](char c){ return std::tolower(c); });
                ++local_map[str];
            }

            if (second == std::cend(contents)) break;
            first = std::next(second);
        }

        local_map.erase("");

        global_map.merge(local_map);
    }

    void index_files_from_deque(mt_deque::mt_deque_t<std::string>& mt_d_file_contents, mt_unordered_map::mt_unordered_map_t<std::string, size_t>& global_map) {
        while (true) {
            auto file_contents = mt_d_file_contents.pop_back();

            if (file_contents.empty()) {
                mt_d_file_contents.push_front("");
                break;
            }

            count_words(file_contents, global_map);
        }
    }

    /*
    * Write mt_unordered_map to file sorted alphabetically by key.
    */
    void write_map_sorted_by_key(mt_unordered_map::mt_unordered_map_t<std::string, size_t>& global_map, const std::string & file_path) {
        write_sorted_map_to_file(global_map,
                                [](std::pair<std::string, size_t> & word1, std::pair<std::string, size_t> & word2){
                                            return word1.first.compare(word2.first) < 0;
                                        },
                                file_path);
    }

    /*
    * Write mt_unordered_map to file sorted by value.
    */
    void write_map_sorted_by_value(mt_unordered_map::mt_unordered_map_t<std::string, size_t>& global_map, const std::string & file_path) {
        write_sorted_map_to_file(global_map,
                                [](std::pair<std::string, size_t> & word1, std::pair<std::string, size_t> & word2){
                                            return word1.second > word2.second;
                                        },
                                file_path);
    }

    /*
    * Write mt_unordered_map to file sorted by condition set with function f.
    */
    void write_sorted_map_to_file(mt_unordered_map::mt_unordered_map_t<std::string, size_t>& global_map,
                                std::function<bool(std::pair<std::string, size_t> & word1, std::pair<std::string, size_t> & word2)> f,
                                const std::string & file_path) {
        std::vector<std::pair<std::string, size_t>> words(global_map.begin(), global_map.end());
        // TODO: Possibly make begin() and end() const
        std::sort(words.begin(), words.end(), f);

        std::ofstream output_file{file_path, std::ios::out};
        if (!output_file) {
            std::cerr << "Error opening output file" << std::endl;
            exit(ERROR_OPENING_FILE);
        }

        for (const auto & word: words) {
            output_file << word.first << " " << word.second << std::endl;
            if (output_file.fail()) {
                std::cerr << "Error writing to output file";
                exit(ERROR_WRITING_TO_FILE);
            }
        }
    }
}