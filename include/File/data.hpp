#pragma once
#include <string>
#include <utility>
class Data {
    private:
    std::string path;
    std::string name;
    std::string suffix;

    public:
#ifdef WIN_32
    explicit Data(const std::string &name, const std::string &suffix,
                  const std::string &path = ".\\")
        : name(name), suffix(suffix), path(path) {
    }
    Data(const std::string &s) : path(".\\") {
        suffix = s.substr(s.find('.'));
        name = s.substr(0, s.find('.'));
    }
#else
    explicit Data(std::string name, std::string suffix,
                  std::string path = "./")
        : name(std::move(name)), suffix(std::move(suffix)), path(std::move(path)) {
    }
    explicit Data(const std::string &s) : path("./") {
        suffix = s.substr(s.find('.'));
        name = s.substr(0, s.find('.'));
    }
#endif
    [[nodiscard]] std::string getFile() const {
        return path + name + suffix;
    }
    [[nodiscard]] std::string getName() const {
        return name;
    }
    [[nodiscard]] std::string getPath() const {
        return path;
    }
    [[nodiscard]] std::string getSuffix() const {
        return suffix;
    }
};