#pragma once
#include <string>
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
    explicit Data(const std::string &name, const std::string &suffix,
                  const std::string &path = "./")
        : name(name), suffix(suffix), path(path) {
    }
    Data(const std::string &s) : path("./") {
        suffix = s.substr(s.find('.'));
        name = s.substr(0, s.find('.'));
    }
#endif
    std::string getFile() const {
        return path + name + suffix;
    }
    std::string getName() const {
        return name;
    }
    std::string getPath() const {
        return path;
    }
    std::string getSuffix() const {
        return suffix;
    }
};