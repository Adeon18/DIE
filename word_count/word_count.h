//
// Created by iamthewalrus on 3/27/22.
//

#ifndef TEMPLATE_WORD_COUNT_H
#define TEMPLATE_WORD_COUNT_H

#include <unordered_map>
#include <mutex>

void count_words(const std::string & contents, std::unordered_map<std::string, size_t> & global_map, std::mutex & m);

#endif //TEMPLATE_WORD_COUNT_H
