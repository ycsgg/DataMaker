#pragma once
#include <vector>
using std::vector;
namespace Graph {
/**
 * 默认从 1 标号
 * */
struct Graph;
template <typename T>
struct Graph_W;
struct Tree;
template <typename T>
struct Tree_W;
/**
 * 默认从 1 标号的有根树
 * 储存每个点的父亲
 * */
struct Tree {
    vector<int> fa;
    Tree(int n) : fa(n + 1) {
    }
    void add(int _fa, int i) {
        fa[i] = _fa;
    }
};
/**
 * 默认从 1 标号的有根带权树
 * 储存每个点的父亲与权值
 * */
template <typename T = int>
struct Tree_W {
    struct Node {
        int fa;
        T w;
    };
    vector<Node> fa;
    Tree_W(int n) : fa(n + 1) {
    }
    void add(int _fa, int i, T w) {
        fa[i].fa = _fa;
        fa[i].w = w;
    }
    Tree_W(const Tree &tr) : fa(tr.fa.size()) {
        int n = tr.fa.size() - 1;
        for (int i = 1; i <= n; i++) {
            if (tr.fa[i] != 0) {
                add(tr.fa[i], i, T());
            }
        }
    }
};
struct Graph {
    vector<vector<int>> edge;
    Graph(int n) : edge(n + 1) {
    }
    Graph(const Tree &tr) : edge(tr.fa.size()) {
        int n = tr.fa.size() - 1;
        for (int i = 1; i <= n; i++) {
            if (tr.fa[i] != 0)
                edge[i].push_back(tr.fa[i]);
        }
    }
    void add(int u, int v) {
        edge[u].emplace_back(v);
    }
};
/**
 * 默认从 1 标号
 * */
template <typename T = int>
struct Graph_W {
    struct Node {
        int v;
        T w;
    };
    vector<vector<Node>> edge;
    Graph_W(int n) : edge(n + 1) {
    }
    Graph_W(const Tree_W<T> &tr) : edge(tr.fa.size()) {
        int n = tr.fa.size() - 1;
        for (int i = 1; i <= n; i++) {
            if (tr.fa[i].v != 0)
                edge[i].push_back(tr.fa[i]);
        }
    }
    void add(int u, int v, T w) {
        edge[u].emplace_back(Node{v, w});
    }
};
} // namespace Graph