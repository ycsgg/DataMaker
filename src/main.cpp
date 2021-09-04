// #include "../include/datamaker.hpp"
#include "../include/datamaker.hpp"
// #include "testlib.h"
#include <iostream>
using namespace std;
int cnt[5][101];
int main() {
    ios::sync_with_stdio(0);
    cout.tie(0);
    // vector<int> g = {1, 2, 3, 4, 5, 6, 7, 8, 9, 50};
    // SpecialGenerator<int> sgen;
    // auto res = Random::getRandom().choose(g, 3);
    // for (auto v : res) {
    // cout << v << " ";
    // }
    // auto res = RandomGraph::randomConnectedUndirectedGraph(
    //     10, 10, hasWeight = true, weightRange = make_pair(1, 2),
    //     selfLoop = true);
    auto res = RandomTree::randomTreeLog(10);
    // for (int i = 1; i <= 10; i++) {
    //     for (auto e : res.edge[i]) {
    //         cout << i << " " << e.v << endl;
    //     }
    // }
    auto rres = Formatter::GraphFormatter::Format(Graph::Graph<int>(res), output_type = RANDOM,
                                                  no_weight = true);
    cout << rres << endl;
}