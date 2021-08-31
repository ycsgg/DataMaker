#include "basic_graph.hpp"
#include "random_tree.hpp"
#include <assert.h>

namespace RandomGraph {
/**
 * n 个节点 m 条边的无向连通图
 * */
Graph::Graph randomConnectedUndirectedGraph(int n, int m) {
    assert(m > n);
    auto graph = Graph::Graph(RandomTree::randomTree(n));
    m -= n - 1;
    
    return graph;
}
} // namespace RandomGraph