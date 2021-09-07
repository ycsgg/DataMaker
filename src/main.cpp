#include "../include/Compare/source.hpp"
#include "../include/datamaker.hpp"
#include <iostream>
using namespace std;
int main() {
    auto exec = Source("std.cpp").compile();
    FileIO::Output out("data");
    generator::Generator<int> gen;
    for (int i = 1; i <= 10; i++) {
        int n = gen.nextRange(100, 60000);
        int m = gen.nextRange(n, min(1ll * n * (n - 1) / 2, 100000ll));

        auto G = RandomGraph::randomDAG(n, m);

        out << n << " " << m << '\n';
        out << Formatter::GraphFormatter::Format(G, 
                                                output_type = RANDOM,
                                                no_weight = true
                                                );
        exec.run(out.finish());
    }
}