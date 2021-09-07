#pragma once
#include "../Base/executor.hpp"
#include "../File/data.hpp"
class Exec {
    private:
    std::string path;
    std::string name;

    public:
#ifdef WIN_32
    explicit Exec(const std::string &name, const std::string &path = ".\\")
        : path(path), name(name) {
    }
#else
    explicit Exec(const std::string &name, const std::string &path = "./")
        : path(path), name(name) {
    }
#endif
    void run(const Data &input, const Data &output) {
        Executor::pipeline(path + name, input.getFile(), output.getFile());
    }
    void run(const Data &input) {
        Data output(input.getName(), ".out", input.getPath());
        run(input, output);
    }
};