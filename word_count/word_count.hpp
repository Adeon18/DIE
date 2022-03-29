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

void count_words(const std::string & contents, std::unordered_map<std::string, size_t> & global_map, std::mutex & m);
void index_files_from_deque(mt_deque_t<std::string>& mt_d_file_contents, mt_unordered_map_t<std::string, size_t>& global_map);

#endif //TEMPLATE_WORD_COUNT_H
