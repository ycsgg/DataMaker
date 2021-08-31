#include "basic_generator.hpp"
using std::pair;
template <typename T, typename E>
class PairGenerator : public GeneratorImpl<pair<T, E>> {
    private:
    Random &rnd;
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