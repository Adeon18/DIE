#ifndef _LIST_AND_READ_HPP
#define _LIST_AND_READ_HPP

#include "../include/mt_deque.hpp"
#include <filesystem>
#include <fstream>
#include <deque>

namespace fs = std::filesystem;

typedef std::deque<char, std::allocator<char> > chardeque;

void add_files_to_queue(mt_deque_t<fs::path>& mt_d, std::string indir) {
    for (auto const& dir_entry : fs::recursive_directory_iterator(indir)) {
        mt_d.push_back(dir_entry.path());
    }
    mt_d.push_back(fs::path(""));
}

chardeque read_file_noseek(std::ifstream& fs_in) {
    using std::begin;
    using std::end;

    // default buffer size of an ifstream
    auto constexpr chunk_size = std::size_t{BUFSIZ};

    auto container = std::deque<char>();

    auto chunk = std::array<char, chunk_size>{};

    while (
        fs_in.read(chunk.data(), chunk.size()) || fs_in.gcount()
    ) container.insert(
        end(container), begin(chunk), begin(chunk) + fs_in.gcount()
    );

    return container;
}

void read_files_from_deque(mt_deque_t<fs::path>& mt_d_filenames, mt_deque_t<chardeque>& mt_d_file_contents) {
    while (true) {
        auto file_path = mt_d_filenames.pop_back();

        if (file_path.empty()) {
            break;
        }

        std::ifstream fs_in;
        fs_in.open(file_path, std::ifstream::in);
        if (!(fs_in.is_open())) {
            // ignore unopenable files
            continue;
        }

        mt_d_file_contents.push_back(read_file_noseek(fs_in));

        fs_in.close();
    }

}

#endif // _LIST_AND_READ_HPP