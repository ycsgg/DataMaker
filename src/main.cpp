#include "../include/datamaker.hpp"
#include "testlib.h"
#include <iostream>
using namespace std;
int cnt[101];
int main() {
    ios::sync_with_stdio(0);
    cout.tie(0);
    PairGenerator<int, int> pgen(make_pair(1, 5), make_pair(10, 8), true);
    vector<pair<int, int>> res;
    for (int i = 0; i < 100; i++) {
        res.push_back(pgen.next());
        cout << res.back().first << " " << res.back().second << endl;
        assert(res.back().first != res.back().second);
    }
}