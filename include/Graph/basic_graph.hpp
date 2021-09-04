#pragma once
#include <vector>
using std::vector;
namespace Graph {
/**
 * 默认从 1 标号
 * */
template <typename T>
struct Graph;
template <typename T>
struct Tree;
/**
 * 默认从 1 标号的有根带权树
 * 储存每个点的父亲与权值
 * */
template <typename T = int>
struct Tree {
    struct Node {
        int fa;
        T w;
    };
    vector<Node> fa;
    Tree(int n) : fa(n + 1) {
    }
    void add(int _fa, int i, T w = T()) {
        fa[i].fa = _fa;
        fa[i].w = w;
    }
};
/**
 * 默认从 1 标号
 * */
template <typename T = int>
struct Graph {
    struct Node {
        int v;
        T w;
    };
    vector<vector<Node>> edge;
    Graph(int n) : edge(n + 1) {
    }
    Graph(const Tree<T> &tr) : edge(tr.fa.size()) {
        int n = tr.fa.size() - 1;
        for (int i = 1; i <= n; i++) {
            if (tr.fa[i].fa != 0)
                edge[i].push_back({tr.fa[i].fa, tr.fa[i].w});
        }
    }
    void add(int u, int v, T w = T()) {
        edge[u].emplace_back(Node{v, w});
    }
};
} // namespace Graph