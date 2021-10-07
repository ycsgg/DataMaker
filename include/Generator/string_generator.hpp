#pragma once
#include "../basic_random.hpp"
#include "basic_generator.hpp"
#include "common_generator.hpp"
#include <algorithm>

namespace DefaultAlphabet {
static std::vector<char> LOWERCASE({'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                                    'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                                    's', 't', 'u', 'v', 'w', 'x', 'y', 'z'});
static std::vector<char> UPPERCASE({'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                                    'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                                    'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'});
static std::vector<char>
    LETTER({'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
            'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'});
static std::vector<char> NUMBER({'0', '1', '2', '3', '4', '5', '6', '7', '8',
                                 '9'});
} // namespace DefaultAlphabet

namespace generator {
using namespace DefaultAlphabet;
class StringGenerator : GeneratorImpl<char> {
    private:
    Random &rnd;
    std::vector<char> &Alphabet;

    public:
    StringGenerator() : rnd(Random::getRandom()), Alphabet(LOWERCASE) {
    }
    StringGenerator(vector<char> &alphabet)
        : rnd(Random::getRandom()), Alphabet(alphabet) {
    }
    char next() override;
    vector<char> next(int n);
};
char StringGenerator::next() {
    return rnd.choose(Alphabet);
}
vector<char> StringGenerator::next(int n) {
    vector<char> res;
    res.reserve(n);
    while (n--) {
        res.push_back(next());
    }
    return res;
}
} // namespace generator