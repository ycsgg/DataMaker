#pragma once
#include "../basic_random.hpp"
/**
 * @brief 统一接口
 * 
 * @tparam T 类型
 */
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