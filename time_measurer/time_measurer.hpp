// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#ifndef _TIME_MEASURER_HPP
#define _TIME_MEASURER_HPP

#include <chrono>
#include <atomic>
#include "time_measurer.hpp"

namespace time_measurer {
    inline std::chrono::high_resolution_clock::time_point get_current_time_fenced()
    {
        std::atomic_thread_fence(std::memory_order_seq_cst);
        auto res_time = std::chrono::high_resolution_clock::now();
        std::atomic_thread_fence(std::memory_order_seq_cst);
        return res_time;
    }

    template<class D>
    inline long long to_us(const D& d)
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
    }
}

#endif  // _TIME_MEASURER_HPP
