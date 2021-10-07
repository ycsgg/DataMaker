#pragma once
#include "../Base/named_type.hpp"
#include "../basic_random.hpp"
#include "basic_generator.hpp"
#include <cassert>
namespace generator {
using namespace random_d;
/**
 * @brief 基本生成器，可以生成 T 类型的随机数
 * 
 * @tparam T 数类型，仅接受 整型 和 浮点型
 */

template <typename T>
class Generator : public GeneratorImpl<T> {
    private:
    Random &rnd;
    std::vector<T> pool;
    int _lim{}, _cur{};
    int _siz{};
    bool is_use_pool;
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
    T nextRange(T down, T up);
    T wnext(T n, i32 type);
    T wnextRange(T down, T up, i32 type);
    std::vector<T> next(T n, int m);
    std::vector<T> nextRange(T down, T up, int m);
    std::vector<T> wnext(T n, int type, int m);
    std::vector<T> wnextRange(T down, T up, int type, int m);
    std::vector<T> distinct(T down, T up, int n);
};
/**
 * @brief 创建一个新的 Generator 对象
 */
template <typename T>
Generator<T>::Generator()
    : rnd(random_d::Random::getRandom()), is_use_pool(false), limit(false) {
}
/**
 * @brief Generator 对象
 *
 * @param a 随机生成的下界(用于next())
 * @param b 随机生成的上界(用于next())
 * @param lim 一次性生成的随机数池大小
 * @param siz 随机数池耗尽后的增量，默认 1024
 */
template <typename T>
Generator<T>::Generator(T a, T b, int lim, int siz)
    : rnd(random_d::Random::getRandom()), is_use_pool(true), a(a), b(b), _lim(lim),
      _cur(0), _siz(siz), limit(true) {
    pool = rnd.nextRange(a, b, lim);
}
/**
 * @brief 创建一个新的 Generator 对象
 *
 * @param a 随机生成的下界(用于next())
 * @param b 随机生成的上界(用于next())
 */
template <typename T>
Generator<T>::Generator(T a, T b)
    : is_use_pool(false), rnd(random_d::Random::getRandom()), limit(true), a(a),
      b(b) {
}
/**
 * @brief 统一接口，生成 [a,b] 中的随机数 (需在构造函数指定a,b)
 * 
 * @return T 随机数
 */
template <typename T>
T Generator<T>::next() {
    if (!limit) {
        throw StringException("No limits for this generator!");
    }
    if (!is_use_pool) {
        return nextRange(a, b);
    } else {
        if (_cur == _lim) {
            ReGen();
        }
        return pool[_cur++];
    }
}
/**
 * @brief 重新生成随机数池
 */
template <typename T>
void Generator<T>::ReGen() {
    if (is_use_pool) {
        _lim = _siz;
        pool = rnd.nextRange(a, b, _lim);
        _cur = 0;
    }
}
/**
 * @brief 生成 [0,n) 的随机数
 */
template <typename T>
T Generator<T>::next(T n) {
    return rnd.next(n);
}
/**
 * @brief 生成 m 个 [0,n) 的随机数
 */
template <typename T>
std::vector<T> Generator<T>::next(T n, int m) {
    return rnd.next(n, m);
}
/**
 * @brief 生成 [down,up] 间的随机数
 */
template <typename T>
T Generator<T>::nextRange(T down, T up) {
    return rnd.nextRange(down, up);
}
/**
 * @brief 生成 m 个 [down,up] 间的随机数
 */
template <typename T>
std::vector<T> Generator<T>::nextRange(T down, T up, int m) {
    return rnd.nextRange(down, up, m);
}
template <typename T>
T Generator<T>::wnext(T n, int type) {
    return rnd.wnext(n, type);
}
template <typename T>
T Generator<T>::wnextRange(T down, T up, int type) {
    return rnd.wnextRange(down, up, type);
}
template <typename T>
std::vector<T> Generator<T>::wnext(T n, int type, int m) {
    return rnd.wnext(n, type, m);
}
template <typename T>
std::vector<T> Generator<T>::wnextRange(T down, T up, int type, int m) {
    return rnd.wnextRange(down, up, type, m);
}
/**
 * @brief 生成 n 个 [down,up] 间的不同的随机数
 */
template <typename T>
std::vector<T> Generator<T>::distinct(T down, T up, int n) {
    return rnd.distinct(down, up, n);
}
} // namespace generator
