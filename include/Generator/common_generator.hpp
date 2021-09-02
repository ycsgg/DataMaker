#pragma once
#include "../Base/named_type.hpp"
#include "../basic_random.hpp"
#include "basic_generator.hpp"
#include <assert.h>

registerNamedType(lim, int);
registerNamedType(siz, int);

template <typename T>   
class Generator : public GeneratorImpl<T> {
    private:
    Random &rnd;
    std::vector<T> pool;
    int _lim, _cur;
    int _siz;
    bool usepool;
    bool limit;
    T a, b;
    void ReGen();

    public:
    Generator();
    Generator(T a, T b, int lim, int siz = 1024);
    Generator(T a, T b);
    ~Generator() = default;
    T next() override;
    T next(T n);
    T nextRange(T a, T b);
    T wnext(T n, i32 type);
    T wnextRange(T a, T b, i32 type);
    std::vector<T> next(T n, int m);
    std::vector<T> nextRange(T a, T b, int m);
    std::vector<T> wnext(T n, int type, int m);
    std::vector<T> wnextRange(T a, T b, int type, int m);
};
template <typename T>
Generator<T>::Generator()
    : rnd(Random::getRandom()), usepool(false), limit(false) {
}
template <typename T>
Generator<T>::Generator(T a, T b, int lim, int siz)
    : rnd(Random::getRandom()), usepool(true), a(a), b(b), _lim(lim), _cur(0),
      _siz(siz), limit(true) {
    pool = rnd.nextRange(a, b, lim);
}
template <typename T>
Generator<T>::Generator(T a, T b)
    : usepool(false), rnd(Random::getRandom()), limit(true), a(a), b(b) {
}
template <typename T>
T Generator<T>::next() {
    if(!limit){
        throw "No limits for this generator!";
    }
    if (usepool == false) {
        return nextRange(a, b);
    } else {
        if (_cur == _lim) {
            ReGen();
        }
        return pool[_cur++];
    }
}
template <typename T>
void Generator<T>::ReGen() {
    if (usepool) {
        std::cerr << "Regen!" << '\n';
        _lim = _siz;
        pool = rnd.nextRange(a, b, _lim);
        _cur = 0;
    }
}
template <typename T>
T Generator<T>::next(T n) {
    return rnd.next(n);
}
template <typename T>
std::vector<T> Generator<T>::next(T n, int m) {
    return rnd.next(n, m);
}

template <typename T>
T Generator<T>::nextRange(T a, T b) {
    return rnd.nextRange(a, b);
}
template <typename T>
std::vector<T> Generator<T>::nextRange(T a, T b, int m) {
    return rnd.nextRange(a, b, m);
}
template <typename T>
T Generator<T>::wnext(T n, int type) {
    return rnd.wnext(n, type);
}
template <typename T>
T Generator<T>::wnextRange(T a, T b, int type) {
    return rnd.wnextRange(a, b, type);
}
template <typename T>
std::vector<T> Generator<T>::wnext(T n, int type, int m) {
    return rnd.wnext(n, type, m);
}
template <typename T>
std::vector<T> Generator<T>::wnextRange(T a, T b, int type, int m) {
    return rnd.wnextRange(a, b, type, m);
}