#pragma once
#include "basic_generator.hpp"
#include "common_generator.hpp"
using std::pair;
template <typename T, typename E>
class PairGenerator : public GeneratorImpl<pair<T, E>> {
    private:
    Generator<T> Tgen;
    Generator<E> Egen;
    bool _same;
    bool limit;
    pair<T, E> a, b;

    public:
    PairGenerator();
    PairGenerator(pair<T, E> a, pair<T, E> b);
    PairGenerator(bool _same);
    PairGenerator(pair<T, E> a, pair<T, E> b, bool same);
    void SetSame(bool same) {
        this->_same = same;
    }
    pair<T, E> next() override;
    pair<T, E> next(pair<T, E> n);
    pair<T, E> nextRange(pair<T, E> down, pair<T, E> up);
    vector<pair<T, E>> next(pair<T, E> n, int m);
    vector<pair<T, E>> nextRange(pair<T, E> down, pair<T, E> up, int m);
};
template <typename T, typename E>
PairGenerator<T, E>::PairGenerator()
    : Tgen(), Egen(), _same(false), limit(false) {
}
template <typename T, typename E>
PairGenerator<T, E>::PairGenerator(pair<T, E> a, pair<T, E> b)
    : Tgen(a.first, b.first), Egen(a.second, b.second), _same(false),
      limit(true), a(a), b(b) {
}
template <typename T, typename E>
PairGenerator<T, E>::PairGenerator(bool _same)
    : Tgen(), Egen(), _same(_same), limit(false) {
}
template <typename T, typename E>
PairGenerator<T, E>::PairGenerator(pair<T, E> a, pair<T, E> b, bool same)
    : Tgen(a.first, b.first), Egen(a.second, b.second), a(a), b(b), _same(same),
      limit(true) {
}
template <typename T, typename E>
pair<T, E> PairGenerator<T, E>::next() {
    assert(limit == true);
    return nextRange(a, b);
}
template <typename T, typename E>
pair<T, E> PairGenerator<T, E>::next(pair<T, E> n) {
    if (_same) {
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
    if (_same) {
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