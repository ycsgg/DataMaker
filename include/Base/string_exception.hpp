//
// Created by ycs_gg on 2021/10/7.
//
#pragma once
#include <exception>
#include <string>
#include <utility>
#ifndef CP_DATAMAKER_STRING_EXCEPTION_H
#define CP_DATAMAKER_STRING_EXCEPTION_H
class StringException : public std::exception {
    private:
    std::string msg;
    public:
    explicit StringException(std::string s) : msg(std::move(s)){
    }
    [[nodiscard]] const char * what() const noexcept override{
        return msg.c_str();
    }
};
#endif //CP_DATAMAKER_STRING_EXCEPTION_H
