#pragma once
#include "../basic_random.hpp"
template <typename T>
class GeneratorImpl {
    private:
    public:
    GeneratorImpl() {
    }
    virtual T next() {
        return T();
    };
};