// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <thread>
#include <array>
#include <unordered_map>
#include "options_parser.h"
#include "../include/mt_deque.hpp"
#include "../include/mt_unordered_map_t.h"

void die() {
    std::cout << "DIE" << std::endl;
}

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


    std::unordered_map<std::string, int> map1{{"A", 1}, {"B", 2}};
    std::unordered_map<std::string, int> map2{{"B", 2}, {"C", 2}};

    std::thread t2(&mt_unordered_map_t<std::string , int>::merge, &mt_um_t, map1);
    std::thread t1(&mt_unordered_map_t<std::string , int>::merge, &mt_um_t, map2);

    t2.join();
    t1.join();


    std::string arr[3] = {"Die", "Dead", "Depress"};

//    dead(mt_um_t, "Depress");

    std::cout << mt_um_t.size() << std::endl;

    for (const auto & item: mt_um_t) {
        std::cout << item.first << " " << item.second << std::endl;
    }

    mt_um_t.clear();



	return 0;
}
