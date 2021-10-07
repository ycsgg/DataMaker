#pragma once

#include "../Base/string_exception.hpp"

namespace generator {
/**
 * @brief 统一接口
 * 
 * @tparam T 类型
 */
template <typename T>
class GeneratorImpl {
    private:
    public:
    GeneratorImpl() = default;
    virtual T next() {
        return T();
    };
};
} // namespace generator