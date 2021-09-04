#pragma once
#include "basic_graph.hpp"
#include "random_tree.hpp"
#include <map>

namespace GraphArgs {
registerNamedType(selfLoop, bool);
registerNamedType(repeatedEdge, bool);
} // namespace GraphArgs

namespace RandomGraph {
using namespace GraphArgs;
/**
 * n 个节点 m 条边的无向连通带权图
 * 默认无重边自环
 * */
template <typename... Args>
Graph::Graph<int> randomConnectedUndirectedGraph(int n, int m, Args... args) {
    if (m < n - 1) {
        throw "m is too small";
    }
    pair<int, int> _weightRange = std::make_pair(0, 0);
    bool _selfLoop = false;
    bool _repeatedEdge = false;
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

    auto graph = Graph::Graph(RandomTree::randomTree(
        n, hasWeight = _judge, weightRange = _weightRange));

    m -= n - 1;

    PairGenerator<int, int> pgen(!_selfLoop);
    Generator<int> wgen;
    std::map<pair<int, int>, bool> _vis;
    for (int i = 1; i <= n; i++) {
        for (auto e : graph.edge[i]) {
            int v = e.v;
            _vis[std::make_pair(i, v)] = _vis[std::make_pair(v, i)] = 1;
        }
    }
    while (m--) {
        if (_repeatedEdge) {
            auto edge = pgen.nextRange({1, 1}, {n, n});
            auto w = wgen.nextRange(_weightRange.first, _weightRange.second);
            graph.add(edge.first, edge.second, w);
        } else {
            if (m + n - 1 > n * (n - 1) / 2) {
                throw "m is too large";
            }
            auto edge = pgen.nextRange({1, 1}, {n, n});
            while (_vis.count(edge)) {
                edge = pgen.nextRange({1, 1}, {n, n});
            }
            _vis[edge] = 1;
            _vis[{edge.second, edge.first}] = 1;
            auto w = wgen.nextRange(_weightRange.first, _weightRange.second);
            graph.add(edge.first, edge.second, w);
        }
    }
    return graph;
}
} // namespace RandomGraph