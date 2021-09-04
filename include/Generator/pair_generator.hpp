#pragma once
#include "basic_generator.hpp"
#include "common_generator.hpp"
using std::pair;
/**
 * @brief 生成一对 <T,E> 类型的随机数
 * 
 * @tparam T 类型参数1
 * @tparam E 类型参数2
 */
template <typename T, typename E>
class PairGenerator : public GeneratorImpl<pair<T, E>> {
    private:
    Generator<T> Tgen;
    Generator<E> Egen;
    bool _not_same;
    bool limit;
    pair<T, E> a, b;

    public:
    PairGenerator();
    PairGenerator(pair<T, E> a, pair<T, E> b);
    PairGenerator(bool _not_same);
    PairGenerator(pair<T, E> a, pair<T, E> b, bool same);
    void SetSame(bool same) {
        this->_not_same = same;
    }
    pair<T, E> next() override;
    pair<T, E> next(pair<T, E> n);
    pair<T, E> nextRange(pair<T, E> down, pair<T, E> up);
    vector<pair<T, E>> next(pair<T, E> n, int m);
    vector<pair<T, E>> nextRange(pair<T, E> down, pair<T, E> up, int m);
};
/**
 * @brief 创建一个新的 PairGenerator 对象
 */
template <typename T, typename E>
PairGenerator<T, E>::PairGenerator()
    : Tgen(), Egen(), _not_same(false), limit(false) {
}
/**
 * @brief 创建一个新的 PairGenerator 对象并指定上下界
 *
 * @param a 分别为 <T,E> 的下界
 * @param b 分别为 <T,E> 的上界
 */
template <typename T, typename E>
PairGenerator<T, E>::PairGenerator(pair<T, E> a, pair<T, E> b)
    : Tgen(a.first, b.first), Egen(a.second, b.second), _not_same(false),
      limit(true), a(a), b(b) {
}
/**
 * @brief 创建一个新的 PairGenerator 对象
 * 
 * @param _not_same 生成的一对数能否相同
 */
template <typename T, typename E>
PairGenerator<T, E>::PairGenerator(bool _not_same)
    : Tgen(), Egen(), _not_same(_not_same), limit(false) {
}
/**
 * @brief 创建一个新的 PairGenerator 对象并指定上下界
 *
 * @param a 分别为 <T,E> 的下界
 * @param b 分别为 <T,E> 的上界
 * @param same 生成的一对数能否相同
 */
template <typename T, typename E>
PairGenerator<T, E>::PairGenerator(pair<T, E> a, pair<T, E> b, bool _not_same)
    : Tgen(a.first, b.first), Egen(a.second, b.second), a(a), b(b), _not_same(_not_same),
      limit(true) {
}
/**
 * @brief 统一接口，需要指定上下界
 */
template <typename T, typename E>
pair<T, E> PairGenerator<T, E>::next() {
    if (!limit) {
        throw "No limits for this generator!";
    }
    return nextRange(a, b);
}
template <typename T, typename E>
pair<T, E> PairGenerator<T, E>::next(pair<T, E> n) {
    if (_not_same) {
        auto Tres = Tgen.next(n.first);
        auto Eres = Egen.next(n.second);
        while (Tres == Eres) {
            Tres = Tgen.next(n.first);
            Eres = Egen.next(n.second);
        }
        return std::make_pair(Tres, Eres);
    } else {
        return std::make_pair(Tgen.next(n.first), Egen.next(n.second));
    }
}
template <typename T, typename E>
pair<T, E> PairGenerator<T, E>::nextRange(pair<T, E> down, pair<T, E> up) {
    if (_not_same) {
        auto Tres = Tgen.nextRange(down.first, up.first);
        auto Eres = Egen.nextRange(down.second, up.second);
        while (Tres == Eres) {
            Tres = Tgen.nextRange(down.first, up.first);
            Eres = Egen.nextRange(down.second, up.second);
        }
        return std::make_pair(Tres, Eres);
    } else {
        return std::make_pair(Tgen.nextRange(down.first, up.first),
                              Egen.nextRange(down.second, up.second));
    }
}
template <typename T, typename E>
vector<pair<T, E>> PairGenerator<T, E>::next(pair<T, E> n, int m) {
    vector<pair<T, E>> res(m);
    for (int i = 0; i < m; i++) {
        res[i] = next(n);
    }
    return res;
}
template <typename T, typename E>
vector<pair<T, E>> PairGenerator<T, E>::nextRange(pair<T, E> down,
                                                  pair<T, E> up, int m) {
    vector<pair<T, E>> res(m);
    for (int i = 0; i < m; i++) {
        res[i] = nextRange(down, up);
    }
    return res;
}