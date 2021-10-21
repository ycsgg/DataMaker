#include "../include/Compare/source.hpp"
#include "../include/datamaker.hpp"
#include <iostream>
using namespace std;
bool vis[1005];
int tot;
void dfs(int x, graph::Graph<int> G) {
    tot++;
    vis[x] = true;
    for (auto e : G.edge[x]) {
        auto v = e.v;
        cout << x << " -> " << v << endl;
        if (vis[v]) {
            continue;
        }
        dfs(v, G);
    }
}
int main() {
    //    auto exec = Source("std.cpp").compile();
    //    FileIO::Output out("data");
    //    generator::Generator<int> gen;
    //    for (int i = 1; i <= 10; i++) {
    //        int n = gen.nextRange(100, 60000);
    //        int m = gen.nextRange(n, min(1ll * n * (n - 1) / 2, 100000ll));
    //
    //        auto G = RandomGraph::randomDAG(n, m);
    //
    //        out << n << " " << m << '\n';
    //        out << Formatter::GraphFormatter::Format(G,
    //                                                output_type = RANDOM,
    //                                                no_weight = true
    //                                                );
    //        exec.run(out.finish());
    //    }
    auto Tr = RandomTree::randomTree(10000000);
    // cout << Tr;
    // cout << Formatter::GraphFormatter::Format(graph::Graph(Tr)) << '\n';
    // graph::Tree<int> R = graph::PrufertoTree(graph::TreetoPrufer(Tr));
    // cout << Formatter::GraphFormatter::Format(graph::Graph(R)) << '\n';
    // cout << Formatter::SeqFormatter::Format(graph::toPrufer(Tr));
}