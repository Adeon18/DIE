// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <thread>
#include <array>
#include "options_parser.h"
#include "../include/mt_deque.hpp"
#include "../include/mt_unordered_map_t.h"

int main(int argv, char* argc[]) {

    mt_deque_t<int> mt_d;

//    std::thread t2(&mt_deque_t<int>::push_back, &mt_d, 2);
//    std::thread t3(&mt_deque_t<int>::push_back, &mt_d, 3);
//    std::thread t1(&mt_deque_t<int>::push_back, &mt_d, 1);
//
//    std::thread t4(&mt_deque_t<int>::pop_back, &mt_d);
//    t2.join();
//    t3.join();
//    t1.join();
//    t4.join();

    // IT FUCKING WORKS!!!!!!!

//    for (int i = 0; i < 1000000; i++) {
//        mt_d.push_back(i);
//    }
//
//    auto size = mt_d.size();
//    std::cout << "size: " << size << std::endl;
//    for (size_t i = 0; i < size; i++) {
//        std::cout << mt_d.pop_back() << std::endl;
//    }

    mt_unordered_map_t<std::string , int> mt_um_t;

    std::thread t2(&mt_unordered_map_t<std::string , int>::insert, &mt_um_t, std::pair<std::string, int>("Die", 2));
    std::thread t3(&mt_unordered_map_t<std::string , int>::insert, &mt_um_t, std::pair<std::string, int>("Dead", 3));
    std::thread t1(&mt_unordered_map_t<std::string , int>::insert, &mt_um_t, std::pair<std::string, int>("Depress", 1));
    std::thread t4(&mt_unordered_map_t<std::string , int>::erase, &mt_um_t, "Depress");

    t2.join();
    t1.join();
    t3.join();
    t4.join();

    std::string arr[3] = {"Die", "Dead", "Depress"};

    mt_um_t["Depress"]++;

    std::cout << mt_um_t.size() << std::endl;

    for (const auto & item: mt_um_t) {
        std::cout << item.first << " " << item.second << std::endl;
    }

    mt_um_t.clear();



	return 0;
}
