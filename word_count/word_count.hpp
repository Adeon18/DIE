//
// Created by iamthewalrus on 3/27/22.
//

#ifndef TEMPLATE_WORD_COUNT_H
#define TEMPLATE_WORD_COUNT_H

#include <mutex>
#include <deque>
#include <unordered_map>
#include "../mt_deque/mt_deque.hpp"
#include "../mt_unordered_map/mt_unordered_map_t.hpp"

void count_words(const std::string & contents, mt_unordered_map_t<std::string, size_t> & global_map);
void index_files_from_deque(mt_deque_t<std::string>& mt_d_file_contents, mt_unordered_map_t<std::string, size_t>& global_map);
void write_sorted_map_to_file(mt_unordered_map_t<std::string, size_t>& global_map, std::function<bool(std::pair<std::string, size_t> & word1, std::pair<std::string, size_t> & word2)> f, const std::string & file_path);
void write_map_sorted_by_key(mt_unordered_map_t<std::string, size_t>& global_map, const std::string & file_path);
void write_map_sorted_by_value(mt_unordered_map_t<std::string, size_t>& global_map, const std::string & file_path);

#endif //TEMPLATE_WORD_COUNT_H
