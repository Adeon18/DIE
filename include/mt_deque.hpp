// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef TEMPLATE_MT_DEQUE_HPP
#define TEMPLATE_MT_DEQUE_HPP

#include <deque>
#include <iostream>
#include <mutex>
#include <condition_variable>

template<typename T>
class mt_deque_t {
public:
    mt_deque_t() = default;
    ~mt_deque_t() = default;
    mt_deque_t(const mt_deque_t&) = delete;
    mt_deque_t& operator=(const mt_deque_t&) = delete;

    void push_back(const T &elem) {
        {
            std::unique_lock<std::mutex> lock(mux_m);

            while (deque_m.size() >= max_size) {
                cv_full_m.wait(lock);
            }
            deque_m.push_back(elem);
        }
        cv_empty_m.notify_one();
    }

    void push_front(const T& elem) {
        {
            std::unique_lock<std::mutex> lock(mux_m);

            while (deque_m.size() >= 2) {
                cv_full_m.wait(lock);
            }
            deque_m.push_front(elem);
        }
        cv_empty_m.notify_one();
    }

    T pop_front() {
        T front_el;
        {
            std::unique_lock<std::mutex> lock(mux_m);

            while (deque_m.empty()) {
                cv_empty_m.wait(lock);
            }
            front_el = deque_m.front();
            deque_m.pop_front();
        }
        cv_full_m.notify_one();

        return front_el;
    }

    T pop_back() {
        T back_el;
        {
            std::unique_lock<std::mutex> lock(mux_m);

            while (deque_m.empty()) {
                cv_empty_m.wait(lock);
            }
            back_el = deque_m.back();
            deque_m.pop_back();
        }
        cv_full_m.notify_one();

        return back_el;
    }

    // This is for debug
    size_t size() {
        std::unique_lock<std::mutex> lock(mux_m);
        return deque_m.size();
    }
private:
    std::deque<T> deque_m;
    std::mutex mux_m;
    std::condition_variable cv_empty_m, cv_full_m;
    static constexpr size_t max_size = 1000;
};

#endif //TEMPLATE_MT_DEQUE_HPP
