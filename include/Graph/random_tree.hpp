#pragma once
#include "../Generator/generator.hpp"
#include "basic_graph.hpp"

namespace RandomTree {
struct _dsu {
    std::vector<int> fa;
    _dsu(int n) : fa(n + 1) {
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
 * 生成一个大小为 n 的无根树
 * 原理是随机一条边检查是否在一个连通块里，若不连通则加上
 * 可以证明每棵树被生成是等概率的 期望高度是 sqrt{2 * Pi * n}
 * 期望连边次数是 (n ln n) / 2
 * 复杂度 O(n ln n)
 * */
using UnrootedTree = Graph::Graph;
UnrootedTree randomTree(int n) {
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
            tr.add(x, y);
            dsu.merge(x, y);
            cnt--;
        }
    }
    return tr;
}
/**
 * 生成一个大小为 n 的有根树，根为 1
 * 原理是随机每个点 i 的父亲为 [1,i) 中的一个数
 * 期望高度为 log n
 * 复杂度 O(n)
 * */
Graph::Tree randomTreeLog(int n) {
    Graph::Tree tr(n);
    auto gen = Generator<int>();
    for (int i = 2; i <= n; i++) {
        tr.add(gen.nextRange(1, i), i);
    }
    return tr;
}
} // namespace RandomTree