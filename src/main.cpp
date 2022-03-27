// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <thread>
#include <iostream>
#include <filesystem>
#include "options_parser.h"
#include "../include/mt_deque.hpp"
#include "../list_and_read/list_and_read.hpp"

int main() {
    std::string indir = "data/to_index";
    std::string out_by_a = "data/res_a.txt";
    std::string out_by_n = "data/res_n.txt";
    int indexing_threads = 5;

    mt_deque_t<std::filesystem::path> mt_d;

    add_files_to_queue(mt_d, indir);

    // mt_deque_t<int> mt_d;

    // std::thread t2(&mt_deque_t<int>::push_back, &mt_d, 2);
    // std::thread t3(&mt_deque_t<int>::push_front, &mt_d, 3);
    // std::thread t1(&mt_deque_t<int>::push_back, &mt_d, 1);

    // t2.join();
    // t3.join();
    // t1.join();

    // // IT FUCKING WORKS!!!!!!!

    // auto size = mt_d.size();
    // for (size_t i = 0; i < size; i++) {
    //     std::cout << mt_d.pop_back() << std::endl;
    // }

	return 0;
}
