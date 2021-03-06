#pragma once
#include "./graph_args.hpp"
#include "basic_graph.hpp"
#include "random_tree.hpp"
#include <map>

namespace RandomGraph {
using namespace GraphArgs;
/**
 * @file random_graph.hpp
 * @fn graph::Graph<int> randomConnectedUndirectedGraph(int n, int m, Args... args)
 * @param n 图的节点个数
 * @param m 图的边数
 * @param args 放置具名参数
 * @return 一个带边权的图
 * @brief 生成 n 个点,m 条边的无向连通图
 * 可指定 \n
 * selfLoop : \n
 * True -> 允许自环 \n
 * False -> 不允许自环 (默认) \n
 * repeatedEdge : \n
 * True -> 允许重边 \n
 * False -> 不允许自环 (默认) \n
 * hasWeight :
 * True -> 有权
 * False -> 无权 (默认)
 * weightRange : 
 * pair<int,int> -> 边权上下界，仅 hasWeight 为 True 时生效
 * @author YCS_GG(ycs_gg@outlook.com)
 * */
template <typename... Args>
graph::Graph<int> randomConnectedUndirectedGraph(int n, int m, Args... args) {
    using namespace generator;
    if (m < n - 1) {
        throw StringException("m is too small");
    }
    pair<int, int> _weightRange = std::make_pair(0, 0);
    bool _selfLoop;
    bool _repeatedEdge;
    bool _judge;
    { // init
        auto _args_tuple = std::make_tuple(std::forward<Args>(args)...);
        _judge = getval<hasWeightType>(_args_tuple, false);
        if (_judge) {
            _weightRange = getval<weightRangeType>(_args_tuple, {0, 0});
        }
        _selfLoop = getval<selfLoopType>(_args_tuple, false);
        _repeatedEdge = getval<repeatedEdgeType>(_args_tuple, false);
    }

    auto graph = graph::Graph(RandomTree::randomTree(
        n, hasWeight = _judge, weightRange = _weightRange));

    m -= n - 1;
    if (m + n - 1 > 1ll * n * (n - 1) / 2 && (!_repeatedEdge || !_selfLoop)) {
        throw StringException("m is too large");
    }

    PairGenerator<int, int> pgen(!_selfLoop);
    Generator<int> w_gen;
    std::map<pair<int, int>, bool> _vis;
    for (int i = 1; i <= n; i++) {
        for (auto e : graph.edge[i]) {
            int v = e.v;
            _vis[std::make_pair(i, v)] = _vis[std::make_pair(v, i)] = true;
        }
    }
    while (m--) {
        if (_repeatedEdge) {
            auto edge = pgen.nextRange({1, 1}, {n, n});
            auto w = w_gen.nextRange(_weightRange.first, _weightRange.second);
            graph.add(edge.first, edge.second, w);
        } else {
            auto edge = pgen.nextRange({1, 1}, {n, n});
            while (_vis.count(edge)) {
                edge = pgen.nextRange({1, 1}, {n, n});
            }
            _vis[edge] = true;
            _vis[{edge.second, edge.first}] = true;
            auto w = w_gen.nextRange(_weightRange.first, _weightRange.second);
            graph.add(edge.first, edge.second, w);
        }
    }
    return graph;
}
/**
 * @file random_graph.hpp
 * @fn graph::Graph<int> randomConnectedDirectedGraph(int n, int m, Args... args)
 * @param n 图的节点个数
 * @param m 图的边数
 * @param args 放置具名参数
 * @return 一个带边权的图
 * @brief 生成 n 个点,m 条边的有向弱连通图
 * 可指定 \n
 * selfLoop : \n
 * True -> 允许自环 \n
 * False -> 不允许自环 (默认) \n
 * repeatedEdge : \n
 * True -> 允许重边 \n
 * False -> 不允许重边 (默认) \n
 * hasWeight :
 * True -> 有权
 * False -> 无权 (默认)
 * weightRange : 
 * pair<int,int> -> 边权上下界，仅 hasWeight 为 True 时生效
 * @author YCS_GG(ycs_gg@outlook.com)
 * */
template <typename... Args>
graph::Graph<int> randomConnectedDirectedGraph(int n, int m, Args... args) {
    using namespace generator;
    if (m < n - 1) {
        throw StringException("m is too small");
    }
    pair<int, int> _weightRange = std::make_pair(0, 0);
    bool _selfLoop;
    bool _repeatedEdge;
    bool _judge;
    { // init
        auto _args_tuple = std::make_tuple(std::forward<Args>(args)...);
        _judge = getval<hasWeightType>(_args_tuple, false);
        if (_judge) {
            _weightRange = getval<weightRangeType>(_args_tuple, {0, 0});
        }
        _selfLoop = getval<selfLoopType>(_args_tuple, false);
        _repeatedEdge = getval<repeatedEdgeType>(_args_tuple, false);
    }

    auto graph = graph::Graph(RandomTree::randomTree(
        n, hasWeight = _judge, weightRange = _weightRange));

    m -= n - 1;
    if (m + n - 1 > 1ll * n * (n - 1) / 2 && (!_repeatedEdge || !_selfLoop)) {
        throw StringException("m is too large");
    }

    PairGenerator<int, int> pgen(!_selfLoop);
    Generator<int> w_gen;
    std::map<pair<int, int>, bool> _vis;
    for (int i = 1; i <= n; i++) {
        for (auto e : graph.edge[i]) {
            int v = e.v;
            _vis[std::make_pair(i, v)] = true;
        }
    }
    while (m--) {
        if (_repeatedEdge) {
            auto edge = pgen.nextRange({1, 1}, {n, n});
            auto w = w_gen.nextRange(_weightRange.first, _weightRange.second);
            graph.add(edge.first, edge.second, w);
        } else {
            auto edge = pgen.nextRange({1, 1}, {n, n});
            while (_vis.count(edge)) {
                edge = pgen.nextRange({1, 1}, {n, n});
            }
            _vis[edge] = true;
            auto w = w_gen.nextRange(_weightRange.first, _weightRange.second);
            graph.add(edge.first, edge.second, w);
        }
    }
    return graph;
}
/**
 * @file random_graph.hpp
 * @fn graph::Graph<int> randomDAG(int n, int m, Args... args)
 * @param n 图的节点个数
 * @param m 图的边数
 * @param args 放置具名参数
 * @return 一个带边权的有向无环图
 * @brief 生成 n 个点,m 条边的有向无环图
 * 可指定 \n
 * hasWeight :
 * True -> 有权
 * False -> 无权 (默认)
 * weightRange : 
 * pair<int,int> -> 边权上下界，仅 hasWeight 为 True 时生效
 * @author YCS_GG(ycs_gg@outlook.com)
 * */
template <typename... Args>
graph::Graph<int> randomDAG(int n, int m, Args... args) {
    using namespace generator;
    if (m > 1ll * n * (n - 1) / 2) {
        throw StringException("m is too large");
    }
    graph::Graph graph(n);
    pair<int, int> _weightRange = std::make_pair(0, 0);
    { // init
        auto _args_tuple = std::make_tuple(std::forward<Args>(args)...);
        bool _judge = getval<hasWeightType>(_args_tuple, false);
        if (_judge) {
            _weightRange = getval<weightRangeType>(_args_tuple, {0, 0});
        }
    }
    auto &&p = random_d::Random::getRandom().perm(n);
    Generator<int> gen;
    Generator<int> w_gen;
    std::map<pair<int, int>, bool> _vis;
    for (int i = 1; i <= m; i++) {
        int x = gen.nextRange(1, n - 1);
        int y = gen.nextRange(x + 1, n);
        while (_vis.count(std::make_pair(x, y))) {
            x = gen.nextRange(1, n - 1);
            y = gen.nextRange(x + 1, n);
        }
        _vis[std::make_pair(x, y)] = true;
        auto w = w_gen.nextRange(_weightRange.first, _weightRange.second);
        graph.add(p[x - 1], p[y - 1], w);
    }
    return graph;
}
/**
 * @file random_graph.hpp
 * @fn graph::Graph<int> randomNormalGraph(int n, int m, Args... args)
 * @param n 图的节点个数
 * @param m 图的边数
 * @param args 放置具名参数
 * @return 一个带边权的图
 * @brief 生成 n 个点,m 条边的无向图
 * 可指定 \n
 * selfLoop : \n
 * True -> 允许自环 \n
 * False -> 不允许自环 (默认) \n
 * repeatedEdge : \n
 * True -> 允许重边 \n
 * False -> 不允许重边 (默认) \n
 * hasWeight :
 * True -> 有权
 * False -> 无权 (默认)
 * weightRange : 
 * pair<int,int> -> 边权上下界，仅 hasWeight 为 True 时生效
 * @author YCS_GG(ycs_gg@outlook.com)
 * */
template <typename... Args>
graph::Graph<int> randomNormalGraph(int n, int m, Args... args) {
    using namespace generator;

    pair<int, int> _weightRange = std::make_pair(0, 0);
    bool _selfLoop;
    bool _repeatedEdge;
    bool _judge;
    { // init
        auto _args_tuple = std::make_tuple(std::forward<Args>(args)...);
        _judge = getval<hasWeightType>(_args_tuple, false);
        if (_judge) {
            _weightRange = getval<weightRangeType>(_args_tuple, {0, 0});
        }
        _selfLoop = getval<selfLoopType>(_args_tuple, false);
        _repeatedEdge = getval<repeatedEdgeType>(_args_tuple, false);
    }
    if (m > 1ll * n * (n - 1) / 2 && (!_repeatedEdge || !_selfLoop)) {
        throw StringException("m is too large");
    }
    graph::Graph graph(n);
    PairGenerator<int, int> pgen(!_selfLoop);
    Generator<int> w_gen;
    std::map<pair<int, int>, bool> _vis;
    while (m--) {
        if (_repeatedEdge) {
            auto edge = pgen.nextRange({1, 1}, {n, n});
            auto w = w_gen.nextRange(_weightRange.first, _weightRange.second);
            graph.add(edge.first, edge.second, w);
        } else {
            auto edge = pgen.nextRange({1, 1}, {n, n});
            while (_vis.count(edge)) {
                edge = pgen.nextRange({1, 1}, {n, n});
            }
            _vis[edge] = true;
            _vis[{edge.second, edge.first}] = true;
            auto w = w_gen.nextRange(_weightRange.first, _weightRange.second);
            graph.add(edge.first, edge.second, w);
        }
    }
    return graph;
}
/**
 * @file random_graph.hpp
 * @fn graph::Graph<int> randomNormalDirectedGraph(int n, int m, Args... args)
 * @param n 图的节点个数
 * @param m 图的边数
 * @param args 放置具名参数
 * @return 一个带边权的图
 * @brief 生成 n 个点,m 条边的有向图
 * 可指定 \n
 * selfLoop : \n
 * True -> 允许自环 \n
 * False -> 不允许自环 (默认) \n
 * repeatedEdge : \n
 * True -> 允许重边 \n
 * False -> 不允许自环 (默认) \n
 * hasWeight :
 * True -> 有权
 * False -> 无权 (默认)
 * weightRange : 
 * pair<int,int> -> 边权上下界，仅 hasWeight 为 True 时生效
 * @author YCS_GG(ycs_gg@outlook.com)
 * */
template <typename... Args>
graph::Graph<int> randomNormalDirectedGraph(int n, int m, Args... args) {
    using namespace generator;

    pair<int, int> _weightRange = std::make_pair(0, 0);
    bool _selfLoop;
    bool _repeatedEdge;
    bool _judge;
    { // init
        auto _args_tuple = std::make_tuple(std::forward<Args>(args)...);
        _judge = getval<hasWeightType>(_args_tuple, false);
        if (_judge) {
            _weightRange = getval<weightRangeType>(_args_tuple, {0, 0});
        }
        _selfLoop = getval<selfLoopType>(_args_tuple, false);
        _repeatedEdge = getval<repeatedEdgeType>(_args_tuple, false);
    }
    if (m > 1ll * n * (n - 1) / 2 && (!_repeatedEdge || !_selfLoop)) {
        throw StringException("m is too large");
    }
    graph::Graph graph(n);

    PairGenerator<int, int> pgen(!_selfLoop);
    Generator<int> w_gen;
    std::map<pair<int, int>, bool> _vis;
    while (m--) {
        if (_repeatedEdge) {
            auto edge = pgen.nextRange({1, 1}, {n, n});
            auto w = w_gen.nextRange(_weightRange.first, _weightRange.second);
            graph.add(edge.first, edge.second, w);
        } else {
            auto edge = pgen.nextRange({1, 1}, {n, n});
            while (_vis.count(edge)) {
                edge = pgen.nextRange({1, 1}, {n, n});
            }
            _vis[edge] = true;
            auto w = w_gen.nextRange(_weightRange.first, _weightRange.second);
            graph.add(edge.first, edge.second, w);
        }
    }
    return graph;
}
} // namespace RandomGraph
