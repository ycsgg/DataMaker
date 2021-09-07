#pragma once
#include <cstdlib>
#include <string>
class Executor {
    private:
    Executor() {
    }

    public:
    static void execute(const std::string &s) {
        if (system(s.c_str()) != 0) {
            throw "excute : " + s + " error!";
        }
    }
    static void compile(const std::string &path,
                        const std::string &output = "std.out",
                        const std::string &option = "-std=c++17 -O2") {
        std::string command("g++ ");
        command.append(path).append(" -o ").append(output).append(" ").append(
            option);
        execute(command);
    }
    static void remove(const std::string &path) {
#ifdef WIN_32
        std::string command("del ");
#else
        std::string command("rm ");
#endif
        command.append(path);
        execute(command);
    }
    static void pipeline(const std::string &exec, const std::string &input,
                         const std::string &output) {
#ifdef WIN_32
        std::string command(".\\");
#else
        std::string command("./");
#endif
        command.append(exec).append(" < ").append(input).append(" > ").append(
            output);
        execute(command);
    }
};