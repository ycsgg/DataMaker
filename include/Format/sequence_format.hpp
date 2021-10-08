#pragma once
#include "./format_args.hpp"
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
namespace Formatter::SeqFormatter {
using namespace Formatter::FormatterArgs;
template <typename T, typename... Args>
std::string Format(const std::vector<T> vec, Args... args) {
    OutputType _output_type = ORDER;
    auto tmp = vec;
    char _delimiter = ' ';
    { //init
        auto _args_tuple = std::make_tuple(std::forward<Args>(args)...);
        _output_type = getval<output_typeType>(_args_tuple, ORDER);
        _delimiter = getval<delimeterType>(_args_tuple, ' ');
    }
    if (_output_type == RANDOM) {
        std::random_shuffle(tmp.begin(), tmp.end());
    }
    std::string result;
    for (auto v : tmp) {
        result.append(std::to_string(v) + _delimiter);
    }
    auto it = result.end();
    result.erase(--it);
    return result;
}
} // namespace Formatter