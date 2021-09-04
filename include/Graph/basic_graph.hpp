#pragma once
#include <vector>
using std::vector;
namespace Graph {
template <typename T>
struct Graph;
template <typename T>
struct Tree;
/**
 * @brief 储存每个点的父亲与权值的有根带权树
 * 默认从 1 标号
 */
template <typename T = int>
struct Tree {
    struct Node {
        int fa;
        T w;
    };
    vector<Node> fa;
    /**
     * @brief 创建一个新的 Tree 对象
     * 
     * @param n 树的大小
     */
    Tree(int n) : fa(n + 1) {
    }
    /**
     * @brief 加入一条新边
     * 
     * @param _fa 父节点
     * @param i 子节点
     * @param w 边权
     */
    void add(int _fa, int i, T w = T()) {
        fa[i].fa = _fa;
        fa[i].w = w;
    }
};
/**
 * @brief 按照边表的方式储存图
 * @tparam T 权值的类型
 * 默认从 1 标号
 */
template <typename T = int>
struct Graph {
    struct Node {
        int v;
        T w;
    };
    vector<vector<Node>> edge;
    /**
     * @brief 创建一个新的 Graph 对象
     * 
     * @param n 图的大小
     */
    Graph(int n) : edge(n + 1) {
    }
    /**
     * @brief 从树转化成图
     * 
     * @param tr 树
     */
    Graph(const Tree<T> &tr) : edge(tr.fa.size()) {
        int n = tr.fa.size() - 1;
        for (int i = 1; i <= n; i++) {
            if (tr.fa[i].fa != 0)
                edge[i].push_back({tr.fa[i].fa, tr.fa[i].w});
        }
    }
    /**
     * @brief 添加一条 u -> v 边权为 c 的有向边
     * 
     * @param u 起点
     * @param v 终点
     * @param w 边权
     */
    void add(int u, int v, T w = T()) {
        edge[u].emplace_back(Node{v, w});
    }
};
} // namespace Graph