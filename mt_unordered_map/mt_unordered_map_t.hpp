#ifndef TEMPLATE_MT_UNORDERED_MAP_T_H
#define TEMPLATE_MT_UNORDERED_MAP_T_H

#include <unordered_map>
#include <iostream>
#include <mutex>
#include <iterator>
#include <condition_variable>

template<typename K, typename V>
class mt_unordered_map_t{
public:
    mt_unordered_map_t() = default;
    ~mt_unordered_map_t() = default;
    mt_unordered_map_t(const mt_unordered_map_t&) = delete;
    mt_unordered_map_t& operator=(const mt_unordered_map_t&) = delete;

    void insert(std::pair<K, V> pair);
    void erase(const K& key);
    void clear() noexcept;
    void merge(const std::unordered_map<K, V> &map);
    // These functions are for iteration, they are protected by unique lock, but SHOUDN'T BE USED in multiple threads
    typename std::unordered_map<K, V>::iterator begin() noexcept;
    typename std::unordered_map<K, V>::iterator end() noexcept;

    size_t size(); // Not to be called inside here because no recursive mutex here

private:
    std::unordered_map<K, V> unordered_map_m;
    std::mutex mux_m;
    std::condition_variable cv_empty_m;
};

template<typename K, typename V>
void mt_unordered_map_t<K, V>::insert(std::pair<K, V> pair) {
    std::unique_lock<std::mutex> lock(mux_m);
    unordered_map_m.insert(pair);
#ifdef UNORDERED_MAP_DEBUG
    std::cout << "insert:: Size(after call, pairs): " <<  unordered_map_m.size() << std::endl;
#endif
}

template<typename K, typename V>
void mt_unordered_map_t<K, V>::erase(const K &key) {
    std::unique_lock<std::mutex> lock(mux_m);
    unordered_map_m.erase(key);
#ifdef UNORDERED_MAP_DEBUG
    std::cout << "erase:: Size(after call, pairs): " <<  unordered_map_m.size() << "; Key: " << key << std::endl;
#endif
}

template<typename K, typename V>
void mt_unordered_map_t<K, V>::clear() noexcept {
    std::unique_lock<std::mutex> lock(mux_m);
    unordered_map_m.clear();
#ifdef UNORDERED_MAP_DEBUG
    std::cout << "clear:: Size(after call, pairs): " <<  unordered_map_m.size() << std::endl;
#endif
}

template<typename K, typename V>
typename std::unordered_map<K, V>::iterator mt_unordered_map_t<K, V>::begin() noexcept {
    std::unique_lock<std::mutex> lock(mux_m);
    return unordered_map_m.begin();
}

template<typename K, typename V>
typename std::unordered_map<K, V>::iterator mt_unordered_map_t<K, V>::end() noexcept {
    std::unique_lock<std::mutex> lock(mux_m);
    return unordered_map_m.end();
}

template<typename K, typename V>
size_t mt_unordered_map_t<K, V>::size() {
    std::unique_lock<std::mutex> lock(mux_m);
    return unordered_map_m.size();
}

template<typename K, typename V>
void mt_unordered_map_t<K, V>::merge(const std::unordered_map<K, V> &map) {
    std::unique_lock<std::mutex> lock(mux_m);

    for (const auto & item: map) {
        unordered_map_m[item.first] += item.second;
    }
}

#endif //TEMPLATE_MT_UNORDERED_MAP_T_H
