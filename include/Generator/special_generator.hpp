#pragma once
#include "../basic_random.hpp"
#include "basic_generator.hpp"
#include "common_generator.hpp"
#include <algorithm>

// only for Integer
template <typename T>
class SpecialGenerator {
    private:
    Generator<T> gen;

    public:
    SpecialGenerator() : gen() {
    }
    /**
     * 将整数 n 划分为 m 个非负整数之和
     * */
    vector<T> SumPartition(T n, int m) {
        if (m <= 0) {
            throw "m must be postive";
        }
        vector<T> result(m);
        if (m == 1) {
            result[0] = n;
            return result;
        }
        auto &&res = gen.nextRange(0, n, m - 1);
        std::sort(res.begin(), res.end());
        result[0] = res[0];
        for (int i = 1; i < res.size(); i++) {
            result[i] = res[i] - res[i - 1];
        }
        result[m - 1] = n - res[m - 2];
        return result;
    }
    /**
     * 将整数 n 划分为 m 个正整数之和
     * */
    vector<T> SumPartitionPostive(T n, int m) {
        if (m <= 0) {
            throw "m must be postive";
        }
        if (m > n) {
            throw "m must be less than n";
        }
        vector<T> result(m);
        if (m == 1) {
            result[0] = n;
            return result;
        }
        auto &&res = Random::getRandom().distinct(1, n - 1, m - 1);
        std::sort(res.begin(), res.end());
        result[0] = res[0];
        for (int i = 1; i < res.size(); i++) {
            result[i] = res[i] - res[i - 1];
        }
        result[m - 1] = n - res[m - 2];
        return result;
    }
};