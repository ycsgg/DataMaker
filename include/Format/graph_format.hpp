#pragma once
#include "../Base/named_type.hpp"
#include "../Generator/common_generator.hpp"
#include "../Graph/basic_graph.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace Formatter {

namespace FormatterArgs {
enum OutputType {
    RANDOM,
    ORDER,
};
registerNamedType(output_type, OutputType);

registerNamedType(no_weight, bool);


} // namespace FormatterArgs

namespace GraphFormatter {

using namespace FormatterArgs;

template <typename T, typename... Args>
std::string Format(const Graph::Graph<T> G, Args... args) {
    OutputType _output_type = ORDER;
    bool _no_weight = false;
    { // init
        auto _args_tuple = std::make_tuple(std::forward<Args>(args)...);
        _output_type = getval<output_typeType>(_args_tuple, ORDER);
        _no_weight = getval<no_weightType>(_args_tuple, false);
    }
    std::string result;
    int n = G.edge.size() - 1;
    if (_no_weight) {
        std::vector<std::pair<int, int>> edgelist;
        for (int i = 1; i <= n; i++) {
            for (auto e : G.edge[i]) {
                int v = e.v;
                edgelist.push_back(std::make_pair(i, v));
            }
        }
        if (_output_type == RANDOM) {
            std::random_shuffle(edgelist.begin(), edgelist.end());
        }
        for (auto p : edgelist) {
            auto edge =
                std::to_string(p.first) + " " + std::to_string(p.second) + '\n';
            result.append(edge);
        }
    } else {
        std::vector<std::tuple<int, int, T>> edgelist;
        for (int i = 1; i <= n; i++) {
            for (auto e : G.edge[i]) {
                int v = e.v;
                T w = e.w;
                edgelist.push_back(std::make_tuple(i, e.v, e.w));
            }
        }
        if (_output_type == RANDOM) {
            std::random_shuffle(edgelist.begin(), edgelist.end());
        }
        for (auto p : edgelist) {
            auto edge = std::to_string(std::get<0>(p)) + " " +
                        std::to_string(std::get<1>(p)) + ' ' +
                        std::to_string(std::get<2>(p)) + '\n';
            result.append(edge);
        }
    }
    return result;
}
} // namespace GraphFormatter

} // namespace Formatter