#ifndef _LIST_AND_READ_HPP
#define _LIST_AND_READ_HPP

#include "../mt_deque/mt_deque.hpp"
#include <filesystem>
#include <fstream>
#include <deque>
#include <array>

namespace fs = std::filesystem;
typedef std::deque<char, std::allocator<char> > chardeque;

namespace list_and_read {
    void add_files_to_queue(mt_deque::mt_deque_t<fs::path>& mt_d_filenames, std::string indir) {
        for (auto const& dir_entry : fs::recursive_directory_iterator(indir)) {
            mt_d_filenames.push_front(dir_entry.path());
        }
        mt_d_filenames.push_front(fs::path(""));
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

    void read_files_from_deque(mt_deque::mt_deque_t<fs::path>& mt_d_filenames, mt_deque::mt_deque_t<std::string>& mt_d_file_contents) {
        while (true) {
            auto file_path = mt_d_filenames.pop_back();

            if (file_path.empty()) {
                mt_d_filenames.push_front(fs::path(""));
                break;
            }

            std::ifstream fs_in;
            fs_in.open(file_path, std::ifstream::in);
            if (!(fs_in.is_open())) {
                // ignore unopenable files
                continue;
            }

            chardeque file_contents = read_file_noseek(fs_in);
            std::string file_contents_str;
            file_contents_str.resize(file_contents.size());
            file_contents_str.assign(file_contents.begin(), file_contents.end());

            mt_d_file_contents.push_front(file_contents_str);

            fs_in.close();
        }
        mt_d_file_contents.push_front("");
    }
}

#endif // _LIST_AND_READ_HPP