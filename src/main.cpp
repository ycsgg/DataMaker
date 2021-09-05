// #include "../include/datamaker.hpp"
#include "../include/datamaker.hpp"
// #include "testlib.h"
#include <iostream>
using namespace std;
int main() {
    FileIO::Output out("test");
    for (int i = 1; i <= 5; i++) {
        auto res = RandomGraph::randomConnectedUndirectedGraph(
            10000, 10001, hasWeight = true, weightRange = make_pair(1, 100));
        auto rres = Formatter::GraphFormatter::Format(
            Graph::Graph<int>(res), output_type = RANDOM, no_weight = false);
        out << rres;
        out.next();
    }
}