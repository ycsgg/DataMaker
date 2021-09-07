#pragma once
#include "../Generator/common_generator.hpp"
#include "../Graph/basic_graph.hpp"
#include "./format_args.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace Formatter {

namespace GraphFormatter {

using namespace FormatterArgs;

/**
 * @file graph_format.hpp
 * @fn std::string Format(const graph::Graph<T> G, Args... args)
 * @brief 将图转换为可输出的字符串
 * 格式为 n 行，每行为 "u v w" \n
 * 可指定 \n
 * output_type : \n
 * RANDOM -> 随机输出 \n
 * ORDER -> 按 1 ~ n 的顺序输出 (默认) \n
 * no_weight : \n
 * True -> 不输出边权 \n
 * False -> 输出边权 (默认) \n
 * @param G 图
 * @param args 放置具名参数
 * @return std::string 返回的字符串
 */
template <typename T, typename... Args>
std::string Format(const graph::Graph<T> G, Args... args) {
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
    auto it = result.end();
    result.erase(--it);
    return result;
}
} // namespace GraphFormatter

} // namespace Formatter