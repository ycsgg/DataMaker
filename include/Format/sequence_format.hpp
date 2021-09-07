#pragma once
#include "./format_args.hpp"
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
namespace Formatter {
namespace SeqFormatter {
using namespace Formatter::FormatterArgs;
template <typename T, typename... Args>
std::string Format(const std::vector<T> vec, Args... args) {
    OutputType _output_type = ORDER;
    char _delimeter = ' ';
    { //init
        auto _args_tuple = std::make_tuple(std::forward<Args>(args)...);
        _output_type = getval<output_typeType>(_args_tuple, ORDER);
        _delimeter = getval<delimeterType>(_args_tuple, ' ');
    }
    if (_output_type == RANDOM) {
        std::random_shuffle(vec.begin(), vec.end());
    }
    std::string result;
    for (auto v : vec) {
        result.append(std::to_string(v) + _delimeter);
    }
    auto it = result.end();
    result.erase(--it);
    return result;
}
} // namespace SeqFormatter
} // namespace Formatter