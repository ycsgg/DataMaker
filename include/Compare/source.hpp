#include "../Base/executor.hpp"
#include "./exec.hpp"

class Source {
    private:
    std::string path;
    std::string name;

    public:
#ifdef WIN_32
    explicit Source(const std::string &name, const std::string &path = ".\\")
        : path(path), name(name) {
    }
#else
    explicit Source(const std::string &name, const std::string &path = "./")
        : path(path), name(name) {
    }
#endif
    Exec compile(const std::string &output = "std.out",
                 const std::string &option = "-std=c++17 -O2") {
        Executor::compile(path + name, output, option);
        return Exec(output, path);
    }
};