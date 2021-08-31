#include "../include/datamaker.hpp"
#include "testlib.h"
#include <iostream>
using namespace std;
int cnt[101];
int main() {
    ios::sync_with_stdio(0);
    cout.tie(0);
    auto &&res = RandomTree::randomTree(1000);
    for (int i = 1; i <= 100; i++) {
        for(auto v : res.edge[i]){
            cout << i << " " << v << '\n';
        }
    }
}