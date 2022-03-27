#ifndef _LIST_AND_READ_HPP
#define _LIST_AND_READ_HPP

#include <filesystem>

namespace fs = std::filesystem;

void add_files_to_queue(mt_deque_t<fs::path>& mt_d, std::string indir) {
    for (auto const& dir_entry : fs::recursive_directory_iterator(indir)) {
        mt_d.push_back(dir_entry.path());
    }
}

#endif // _LIST_AND_READ_HPP