#include "../include/datamaker.hpp"
// #include "testlib.h"
#include <iostream>
using namespace std;
int main() {
    FileIO::Output out("test");
    for (int i = 1; i <= 1; i++) {
        out << 10000 << " " << 10001 << '\n';
        auto res = RandomGraph::randomDAG(10000, 10001, hasWeight = false,
                                          weightRange = make_pair(1, 100));
        out << Formatter::GraphFormatter::Format(
            Graph::Graph<int>(res),
            output_type = RANDOM,
            no_weight = true
        );
        out.next();
    }
}