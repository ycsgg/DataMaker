#pragma once
#include <array>
#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <set>
#include <vector>
namespace random_d {
using std::vector;
using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;
using f32 = float;
using f64 = double;
using f80 = long double;
class Random {
    private:
    std::random_device rd; // Too Slow!
    u64 seed = 19260817ll * 71806291ll;
    u64 multiplier;
    u64 addend;
    u64 mask;
    Random() {
        for (i32 i = 1; i < 8; i++) {
            seed *= rd();
        }
        multiplier = 0x5DEECE66DLL;
        addend = 0xBLL;
        mask = (1LL << 48) - 1;
    }
    i64 nextBits(i32 bits) {
        if (bits <= 48) {
            seed = (seed * multiplier + addend) & mask;
            return (i64)(seed >> (48 - bits));
        } else {
            i32 lowerBitCount = (32);
            i64 left = (nextBits(31) << 32);
            i64 right = nextBits(lowerBitCount);
            return left ^ right;
        }
    }

    public:
    static Random &getRandom() {
        static Random rnd;
        return rnd;
    }
    /**
     * @brief 随机生成在 [0,n-1] 区间内的整数(int范围)
     * @param n 上限
     * @return 随机数
     */
    i32 next(i32 n) {
        if ((n & -n) == n) // n is a power of 2
            return (i32)((n * (i64)nextBits(31)) >> 31);
        const i64 limit = std::numeric_limits<i32>::max() / n * n;
        i64 bits;
        do {
            bits = nextBits(31);
        } while (bits >= limit);
        return i32(bits % n);
    }
    /**
     * @brief 随机生成在 [0,n-1] 区间内的整数(unsigned int范围)
     * @param n 上限
     * @return 随机数
     */
    u32 next(u32 n) {
        return (u32)next((i32)n);
    }
    /**
     * @brief 随机生成在 [0,n-1] 区间内的整数(long long范围)
     * @param n 上限
     * @return 随机数
     */
    i64 next(i64 n) {
        const i64 limit = std::numeric_limits<i64>::max() / n * n;
        i64 bits;
        do {
            bits = nextBits(63);
        } while (bits >= limit);
        return (bits % n);
    }
    /**
     * @brief 随机生成在 [0,n-1] 区间内的整数(unsigned long long范围)
     * @param n 上限
     * @return 随机数
     */
    u64 next(u64 n) {
        return (u64)next((i64)n);
    }
    /**
     * @brief 随机生成在 [0,1) 区间内的实数(double范围)
     * @param n 上限
     * @return 随机数
     */
    f64 next() {
        i64 left = ((i64)(nextBits(26)) << 27);
        i64 right = nextBits(27);
        return (double)(left + right) / (double)(1LL << 53);
    }
    /**
     * @brief 随机生成在 [0,n) 区间内的实数(double范围)
     * @param n 上限
     * @return 随机数
     */
    f64 next(f64 n) {
        return next() * n;
    }
    /**
     * @brief 随机生成 m 个在 [0,n) 的数
     *
     * @tparam T 随机数的类型，仅接受 整数 与 浮点数类型
     * @param n 上限
     * @param m 随机数个数
     * @return vector<T> 随机数列表
     */
    template <typename T>
    vector<T> next(T n, i32 m) {
        std::vector<T> res(m);
        for (T i = 0; i < m; i++) {
            res[i] = next(n);
        }
        return res;
    }
    /**
     * @brief 随机生成在区间 [a,b] 的数
     *
     * @tparam T 随机数的类型，仅接受 整数 与 浮点数类型
     * @param a 下界
     * @param b 上界
     * @return T 随机数
     */
    template <typename T>
    T nextRange(T a, T b) {
        return next(b - a + 1) + a;
    }
    /**
     * @brief 随机生成 m 个在 [a,b] 的数
     *
     * @tparam T 随机数的类型，仅接受 整数 与 浮点数类型
     * @param a 下界
     * @param b 上界
     * @param m 随机数个数
     * @return vector<T> 随机数列表
     */
    template <typename T>
    vector<T> nextRange(T a, T b, i32 m) {
        std::vector<T> res(m);
        for (i32 i = 0; i < m; i++) {
            res[i] = nextRange(a, b);
        }
        return res;
    }
    /**
     * @brief 带权随机 [0,n-1]
     * @brief 的整数，type越大越倾向于生成大数，越小越倾向于生成小数 (int范围)
     * @param n 上界
     * @param type 大小参数
     * @return 随机数
     */
    i32 wnext(i32 n, i32 type) {
        if (abs(type) < 32) {
            auto result = next(n, abs(type) + 1);
            auto res = result[0];
            for (auto i = 1; i <= type; i++) {
                res = std::max(res, result[i]);
            }
            for (auto i = 1; i <= -type; i++) {
                res = std::max(res, result[i]);
            }
            return res;
        } else {
            double p;
            if (type > 0) {
                p = std::pow(next() + 0.0, 1.0 / (type + 1));
            } else {
                p = 1 - std::pow(next() + 0.0, 1.0 / (-type + 1));
            }
            return i32(n * p);
        }
    }
    /**
     * @brief 带权随机 [0,n-1]
     * @brief 的整数，type越大越倾向于生成大数，越小越倾向于生成小数 (long
     * @brief long范围)
     * @param n 上界
     * @param type 大小参数
     * @return 随机数
     */
    i64 wnext(i64 n, i32 type) {
        if (abs(type) < 32) {
            vector<i64> result = next(n, abs(type) + 1);
            i64 res = result[0];
            for (auto i = 1; i <= type; i++) {
                res = std::max(res, result[i]);
            }
            for (auto i = 1; i <= -type; i++) {
                res = std::max(res, result[i]);
            }
            return res;
        } else {
            double p;
            if (type > 0)
                p = std::pow(next() + 0.0, 1.0 / (type + 1));
            else
                p = std::pow(next() + 0.0, -type + 1);
            return std::min(std::max((i64)(double(n) * p), 0ll), n - 1ll);
        }
    }
    /**
     * @brief 带权随机 [0,n-1]
     * @brief 的浮点数，type越大越倾向于生成大数，越小越倾向于生成小数
     * @brief (double范围)
     * @param n 上界
     * @param type 大小参数
     * @return 随机数
     */
    f64 wnext(f64 n, i32 type) {
        if (abs(type) < 32) {
            vector<f64> result = nextRange(0.0, 1.0, abs(type) + 1);
            f64 res = result[0];
            for (auto i = 1; i <= type; i++) {
                res = std::max(res, result[i]);
            }
            for (auto i = 1; i <= -type; i++) {
                res = std::max(res, result[i]);
            }
            return res;
        } else {
            double p;
            if (type > 0)
                p = std::pow(next() + 0.0, 1.0 / (type + 1));
            else
                p = std::pow(next() + 0.0, -type + 1);
            return n * p;
        }
    }
    template <typename T>
    T wnextRange(T a, T b, i32 type) {
        return wnext(b - a + 1, type) + a;
    }
    template <typename T>
    vector<T> wnext(T n, i32 type, i32 m) {
        vector<T> res(m);
        for (int i = 0; i < m; i++) {
            res[i] = wnext(n, type);
        }
        return res;
    }
    template <typename T>
    vector<T> wnextRange(T a, T b, i32 type, i32 m) {
        vector<T> res(m);
        for (int i = 0; i < m; i++) {
            res[i] = wnextRange(a, b, type);
        }
        return res;
    }
    /**
     * @brief 随机生成 1 ~ n 的排列
     * 
     * @param n 上界
     * @return std::vector<i32> 随机排列
     */
    std::vector<i32> perm(i32 n) {
        std::vector<i32> p(n);
        i32 current = 1;
        for (i32 i = 0; i < n; i++) {
            p[i] = current++;
        }
        if (n > 1)
            for (i32 i = 1; i < n; i++)
                std::swap(p[i], p[next(i + 1)]);
        return p;
    }
    /**
     * @brief 从容器(vector)中随机选一个元素
     * 
     * @tparam T 容器元素类型
     * @param Container 容器
     * @return T 元素
     */
    template <typename T>
    T choose(std::vector<T> Container) {
        return Container[nextRange(0, (int)Container.size())];
    }
    /**
     * @brief 从容器(array)中随机选一个元素
     *
     * @tparam T 容器元素类型
     * @tparam L array长度
     * @param Container 容器
     * @return T 元素
     */
    template <typename T, size_t L>
    T choose(std::array<T, L> Container) {
        return Container[nextRange(0, (int)L)];
    }
    /**
     * @brief 随机生成 [a,b] 区间的 n 个不同的数
     * 
     * @tparam T 数类型
     * @param a 下界
     * @param b 上界
     * @param n 个数
     * @return vector<T> 不同的随机数
     */
    template <typename T>
    vector<T> distinct(T a, T b, int n) {
        vector<T> res;
        if (n == 0) {
            return res;
        }
        int len = b - a + 1;
        if (len < n) {
            throw "Can't generate too much distinct numbers (b - a + 1 < n)";
        }
        res.reserve(n);
        double expected = 0.0;
        for (int i = 1; i <= n; i++)
            expected += double(len) / double(len - i + 1);
        if (expected < double(len)) {
            std::set<int> vals;
            while (vals.size() < n) {
                auto v = nextRange(a, b);
                auto result = vals.insert(v);
                if (result.second) {
                    res.push_back(v);
                }
            }
        } else {
            if (len > 1000000000) {
                throw "Can't generate too much distinct numbers ";
            }
            vector<int> p(Random::getRandom().perm(len));
            for (int i = 0; i < n; i++) {
                res.push_back(p[i] + a - 1);
            }
        }
        return res;
    }
    /**
     * @brief 随机抽取 n 个容器(vector)的元素
     * 
     * @tparam T 元素类型
     * @param Container 容器
     * @param n 个数
     * @return vector<T> 抽取的元素
     */
    template <typename T>
    vector<T> choose(std::vector<T> Container, int n) {
        auto res = distinct(0, (int)Container.size() - 1, n);
        vector<T> result;
        result.reserve(n);
        for (auto v : res) {
            result.push_back(Container[v]);
        }
        return result;
    }
    /**
     * @brief 随机抽取 n 个容器(array)的元素
     *
     * @tparam T 元素类型
     * @tparam L array长度
     * @param Container 容器
     * @param n 个数
     * @return vector<T> 抽取的元素
     */
    template <typename T, size_t L>
    vector<T> choose(std::array<T, L> Container, int n) {
        auto res = distinct(0, (int)L - 1, n);
        vector<T> result;
        result.reserve(n);
        for (auto v : res) {
            result.push_back(Container[v]);
        }
        return result;
    }
};
} // namespace random