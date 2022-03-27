#ifndef TEMPLATE_MT_UNORDERED_MAP_T_H
#define TEMPLATE_MT_UNORDERED_MAP_T_H

#include <unordered_map>
#include <iostream>
#include <mutex>
#include <condition_variable>

template<typename K, typename V>
class mt_unordered_map_t{
public:
    mt_unordered_map_t() = default;
    ~mt_unordered_map_t() = default;
    mt_unordered_map_t(const mt_unordered_map_t&) = delete;
    mt_unordered_map_t& operator=(const mt_unordered_map_t&) = delete;
    // TODO: Write these functions
    void insert(std::pair<K, V>);
    void erase(const K& key);
    // TODO: What is noexcept?
    void clear() noexcept;
    V& operator[](const K& key);

private:
    std::unordered_map<K, V> map_m;
    std::mutex mux_m;
    std::condition_variable cv_empty_m;
};

#endif //TEMPLATE_MT_UNORDERED_MAP_T_H
