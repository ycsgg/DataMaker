#include "../include/Compare/source.hpp"
#include "../include/datamaker.hpp"
// #include "testlib.h"
#include <iostream>
using namespace std;
int main() {
    auto exe = Source("test.cpp").compile();
    FileIO::Output out("q");
    generator::Generator<int> gen;
    for (int i = 1; i <= 2; i++) {
        out << gen.nextRange(1, 1000) << " " << gen.nextRange(1, 1000);
        exe.run(out.finish());
    }
}