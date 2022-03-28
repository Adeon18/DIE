// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <deque>
#include <thread>
#include <iostream>
#include <filesystem>
#include "options_parser.h"
#include "../mt_deque/mt_deque.hpp"
#include "../list_and_read/list_and_read.hpp"

namespace fs = std::filesystem;

typedef std::deque<char, std::allocator<char> > chardeque;

int main() {
    std::string indir = "data/to_index";
    std::string out_by_a = "data/res_a.txt";
    std::string out_by_n = "data/res_n.txt";
    int indexing_threads = 5;

    mt_deque_t<std::filesystem::path> mt_d_filenames;
    mt_deque_t<chardeque> mt_d_file_contents;

    std::thread file_list_thread(add_files_to_queue, std::ref(mt_d_filenames), indir);
    std::thread file_read_thread(add_files_to_queue, std::ref(mt_d_filenames), std::ref(mt_d_file_contents));

    file_list_thread.join();
    file_read_thread.join();

	return 0;
}
