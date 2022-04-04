// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef _LIST_AND_READ_HPP
#define _LIST_AND_READ_HPP

#include "../time_measurer/time_measurer.hpp"
#include "../mt_deque/mt_deque.hpp"
#include "../include/limits.hpp"
#include <filesystem>
#include <fstream>
#include <deque>
#include <array>

namespace fs = std::filesystem;
typedef std::deque<char, std::allocator<char> > chardeque;

namespace list_and_read {
    void add_files_to_queue(
        mt_deque::mt_deque_t<fs::path>& mt_d_filenames, const std::string &indir,
        time_measurer::mt_time_summmator_t &time_sum
    ) {

        auto measure_start = time_measurer::get_current_time_fenced();
        for (auto const& dir_entry : fs::recursive_directory_iterator(indir)) {
            if (!dir_entry.path().empty()) mt_d_filenames.push_front(dir_entry.path());

            measure_start = time_measurer::get_current_time_fenced();
        }
        time_sum.add_time(time_measurer::get_current_time_fenced() - measure_start);
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

    std::string read_file_fast(std::ifstream& fs_in) {
        auto const start_pos = fs_in.tellg();
        fs_in.ignore(std::numeric_limits<std::streamsize>::max());
        auto const char_count = fs_in.gcount();
        fs_in.seekg(start_pos);
        auto s = std::string(char_count, char{});
        fs_in.read(&s[0], s.size());
        return s;
    }

    void read_files_from_deque(
        mt_deque::mt_deque_t<fs::path>& mt_d_filenames, mt_deque::mt_deque_t<std::string>& mt_d_file_contents,
        time_measurer::mt_time_summmator_t &time_sum
    ) {
        auto measure_start = time_measurer::get_current_time_fenced();
        while (true) {
            auto file_path = mt_d_filenames.pop_back();

            [[unlikely]] if (file_path.empty()) {
                mt_d_filenames.push_front(fs::path(""));
                break;
            }

            std::ifstream fs_in;
            fs_in.open(file_path, std::ifstream::in);
            if (!(fs_in.is_open())) {
                // ignore unopenable files
                continue;
            }

            std::string file_contents_str = read_file_fast(fs_in);

            if (!file_contents_str.empty() && file_contents_str.size() <= size_limits::FILE_SIZE_LIMIT_BYTES)
                mt_d_file_contents.push_front(file_contents_str);

            fs_in.close();
        }
        time_sum.add_time(time_measurer::get_current_time_fenced() - measure_start);
        mt_d_file_contents.push_front("");
    }
}

#endif // _LIST_AND_READ_HPP