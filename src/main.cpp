// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <deque>
#include <string>
#include <thread>
#include <iostream>
#include <filesystem>
#include "options_parser.hpp"
#include "../mt_deque/mt_deque.hpp"
#include "../word_count/word_count.hpp"
#include "../toml_parser/toml_parser.hpp"
#include "../list_and_read/list_and_read.hpp"
#include "../mt_unordered_map/mt_unordered_map_t.hpp"

int main(int argc, char* argv[]) {
    command_line_options_t command_line_options{argc, argv};

    toml_parser::config_t config;
    switch (read_config(command_line_options.get_config_file(), config)) {
    case toml_parser::STATUS_SYNTAX_ERROR:
        exit(EXIT_FAILURE);
        break;
    case toml_parser::STATUS_OPEN_ERROR:
        std::cout << "Config file open error" << std::endl;
        exit(EXIT_FAILURE);
        break;
    default:
        break;
    }

    mt_deque_t<std::filesystem::path> mt_d_filenames;
    mt_deque_t<std::string> mt_d_file_contents;
    mt_unordered_map_t<std::string, size_t> global_map;

    std::thread file_list_thread(add_files_to_queue, std::ref(mt_d_filenames), config.indir);
    std::thread file_read_thread(read_files_from_deque, std::ref(mt_d_filenames), std::ref(mt_d_file_contents));

    std::vector<std::thread> file_index_thread_v;
    for (size_t i = 0; i < config.indexing_threads; i++) {
        file_index_thread_v.emplace_back(index_files_from_deque, std::ref(mt_d_file_contents), std::ref(global_map));
    }

    file_list_thread.join();
    file_read_thread.join();

    for (size_t i = 0; i < config.indexing_threads; i++) {
        file_index_thread_v[i].join();
    }

    // for (const auto& [word, count] : global_map) {
    //     std::cout << word << " " << count << std::endl;
    // }

    auto smth = global_map.begin();
    for (size_t i = 0; i < 10; i++) {
        std::cout << smth->first << " " << smth->second << std::endl;
        ++smth;
    }
    

	return 0;
}
