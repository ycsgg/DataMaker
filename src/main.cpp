#include "../include/datamaker.hpp"
// #include "testlib.h"
#include <iostream>
using namespace std;
int cnt[5][101];
int main() {
    ios::sync_with_stdio(0);
    cout.tie(0);
    vector<int> g = {1, 2, 3, 4, 5, 6, 7, 8, 9, 50};
    SpecialGenerator<int> sgen;
    auto res = Random::getRandom().choose(g, 3);
    for (auto v : res) {
        cout << v << " ";
    }
}