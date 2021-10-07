#pragma once
#include "../Base/named_type.hpp"
#include "../Generator/generator.hpp"
#include "./graph_args.hpp"
#include "basic_graph.hpp"

namespace RandomTree {
using namespace GraphArgs;
/**
 * @file random_tree.hpp
 * @brief 并查集
 * @author YCS_GG(ycs_gg@outlook.com)
 */
struct _dsu {
    std::vector<int> fa;
    explicit _dsu(int n) : fa(n + 1) {
        for (int i = 1; i <= n; i++) {
            fa[i] = i;
        }
    }
    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }
    void merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) {
            fa[x] = y;
        }
    }
};

/**
 * @file random_tree.hpp
 * @fn UnrootedTree randomTree(int n, Args... args)
 * @param n 树的节点数量
 * @param args 放置具名参数
 * @return 一个 n 个节点的带权树，按照图的方式储存
 * @brief 生成大小为 n 的无根带权树
 * 可指定 \n
 * hasWeight : \n
 * True -> 有边权 \n
 * False -> 无边权 (默认) \n
 * weightRange : \n
 * pair<int,int> -> 边权的上下界 (默认(0,0)) \n
 * 生成一个大小为 n 的无根带权树 \n
 * 原理是随机一条边检查是否在一个连通块里，若不连通则加上 \n
 * 可以证明每棵树被生成是等概率的 期望高度是 sqrt{2 * Pi * n} \n
 * 期望连边次数是 (n ln n) / 2 \n
 * 期望复杂度 O(n ln n) \n
 * @author YCS_GG(ycs_gg@outlook.com)
 * */
using UnrootedTree = graph::Graph<int>;
template <typename... Args>
UnrootedTree randomTree(int n, Args... args) {
    using namespace generator;
    pair<int, int> _weightRange = std::make_pair(0, 0);
    { // init
        auto _args_tuple = std::make_tuple(std::forward<Args>(args)...);
        bool _judge = getval<hasWeightType>(_args_tuple, false);
        if (_judge) {
            _weightRange = getval<weightRangeType>(_args_tuple, {0, 0});
        }
    }
    UnrootedTree tr(n);
    _dsu dsu(n);
    auto gen = Generator<int>(1, n);
    int cnt = n;
    int tot = 0;
    while (cnt != 1) {
        int x = gen.next();
        int y = gen.next();
        tot += 2;
        if (dsu.find(x) != dsu.find(y)) {
            tr.add(x, y,
                   gen.nextRange(_weightRange.first, _weightRange.second));
            dsu.merge(x, y);
            cnt--;
        }
    }
    return tr;
}
/**
 * @file random_tree.hpp
 * @fn graph::Tree<int> randomTreeLog(int n, Args... args)
 * @param n 树的节点数量
 * @param args 放置具名参数
 * @return 一个 n 个节点的带权树，按照父子关系存储
 * @brief 生成大小为 n 的有根带权树，根为 1 
 * 可指定 \n
 * hasWeight : \n
 * True -> 有边权 \n
 * False -> 无边权 (默认) \n
 * weightRange : \n
 * pair<int,int> -> 边权的上下界 (默认(0,0)) \n
 * 原理是随机每个点 i 的父亲为 [1,i) 中的一个数 \n
 * 期望高度为 O(log n) \n
 * 复杂度 O(n) \n
 * @author YCS_GG(ycs_gg@outlook.com)
 * */

template <typename... Args>
graph::Tree<int> randomTreeLog(int n, Args... args) {
    using namespace generator;
    pair<int, int> _weightRange = std::make_pair(0, 0);
    { // init
        auto _args_tuple = std::make_tuple(std::forward<Args>(args)...);
        bool _judge = getval<hasWeightType>(_args_tuple, false);
        if (_judge) {
            _weightRange = getval<weightRangeType>(_args_tuple, {0, 0});
        }
    }
    graph::Tree tr(n);
    auto gen = Generator<int>();
    for (int i = 2; i <= n; i++) {
        tr.add(gen.nextRange(1, i - 1), i,
               gen.nextRange(_weightRange.first, _weightRange.second));
    }
    return tr;
}
} // namespace RandomTree
