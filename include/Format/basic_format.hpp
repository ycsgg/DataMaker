#pragma once
#include <string>
template <typename T>
class FormatterImpl {
    private:
    public:
    virtual std::string format(const T &obj) {
        return "";
    };
};