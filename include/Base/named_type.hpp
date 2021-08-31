#pragma once
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>
template <typename T, typename Parameter>
class NamedType {
    private:
    T _value;

    public:
    explicit NamedType(T const &value) : _value(value){};
    explicit NamedType(T &&value) : _value(std::move(value)){};
    T &get() {
        return _value;
    }
    const T &get() const {
        return _value;
    }
    struct Argument {
        template <typename UnderlyingType>
        NamedType operator=(UnderlyingType &&value) const {
            return NamedType(std::forward<UnderlyingType>(value));
        }
        Argument() = default;
        Argument(Argument const &) = delete;
        Argument(Argument &&) = delete;
        Argument &operator=(Argument const &) = delete;
        Argument &operator=(Argument &&) = delete;
    };
};

#define registerNamedType(__name__, __type__)                                  \
    using __name__##Type = NamedType<__type__, struct __##__name__##Tag>;      \
    static const __name__##Type::Argument __name__;

template <typename T, typename... Us>
struct __has_type : std::disjunction<std::is_same<T, Us>...> {};

template <typename __getType, typename T>
auto __pick(T &__tuple) -> decltype(std::declval<__getType>().get()) {
    return std::get<__getType>(__tuple).get();
}
template <typename __getType>
using NamedType_contained_type =
    std::remove_reference_t<decltype(std::declval<__getType>().get())>;

template <typename __getType, typename... Args>
auto getval(std::tuple<Args...> &__tuple,
            NamedType_contained_type<__getType> &&default_Ret_Value)
    -> NamedType_contained_type<__getType> {
    using __RetType = NamedType_contained_type<__getType>;
    if constexpr (__has_type<__getType, Args...>::value)
        return std::get<__getType>(__tuple).get();
    else
        return std::forward<__RetType>(default_Ret_Value);
}