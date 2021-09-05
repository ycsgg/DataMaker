#pragma once
#include <fstream>
#include <sstream>
#include <string>

namespace FileIO {
class Output {
    private:
    std::fstream fp_io;
    std::string data_prefix;
    std::string data_suffix;
    int cur;

    public:
    explicit Output(const std::string &data_prefix)
        : data_prefix(data_prefix), data_suffix(".in") {
        cur = 0;
    }

    explicit Output(const std::string &data_prefix,
                    const std::string &data_suffix)
        : data_prefix(data_prefix), data_suffix(data_suffix) {
        cur = 0;
    }
    ~Output() {
        if (fp_io.is_open()) {
            fp_io.close();
        }
    }
    void next() {
        cur++;
        if (fp_io.is_open()) {
            fp_io.close();
        }
    }
    template <typename T>
    Output &operator<<(const T &s) {
        if (fp_io.is_open()) {
            fp_io << s;
        } else {
            fp_io.open(data_prefix + std::to_string(cur) + data_suffix,
                       std::ios::out);
            fp_io << s;
        }
        return *this;
    }
};
} // namespace FileIO