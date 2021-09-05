#include "./basic_graph.hpp"

namespace graph {
/**
 * @file graph_utils.hpp
 * @fn Graph<T> connect(const Graph<T> &A, const Graph<T> &B)
 * @brief 拼接两张图
 */
template <typename T>
Graph<T> connect(const Graph<T> &A, const Graph<T> &B) {
    int _siz1 = A.edge.size() - 1;
    int _siz2 = B.edge.size() - 1;
    Graph result(_siz1 + _siz2);
    for (int i = 1; i <= _siz1; i++) {
        for (auto e : A.edge[i]) {
            result.add(i, e.v, e.w);
        }
    }
    for (int i = 1; i <= _siz2; i++) {
        for (auto e : B.edge[i]) {
            result.add(i + _siz1, e.v + _siz1, e.w);
        }
    }
    return result;
}
/**
 * @file graph_utils.hpp
 * @fn Graph<T> mix(const Graph<T> &A, const Graph<T> &B)
 * @brief 合并两张图
 */
template <typename T>
Graph<T> mix(const Graph<T> &A, const Graph<T> &B) {
    int _siz1 = A.edge.size() - 1;
    int _siz2 = B.edge.size() - 1;
    Graph result(std::max(_siz1, _siz2));
    for (int i = 1; i <= _siz1; i++) {
        for (auto e : A.edge[i]) {
            result.add(i, e.v, e.w);
        }
    }
    for (int i = 1; i <= _siz2; i++) {
        for (auto e : B.edge[i]) {
            result.add(i, e.v, e.w);
        }
    }
    return result;
}
template <typename T>
Graph<T> Graph<T>::operator+(const Graph &G) {
    return connect(*this, G);
}
template <typename T>
Graph<T> Graph<T>::operator|(const Graph &G) {
    return mix(*this, G);
}
} // namespace graph