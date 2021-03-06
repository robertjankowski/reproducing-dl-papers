#ifndef HOMOPHILY_STRUCTURAL_BALANCE_UTILS_HPP
#define HOMOPHILY_STRUCTURAL_BALANCE_UTILS_HPP

#include <random>
#include <algorithm>
#include <cstdlib>
#include <ctime>

namespace utils {

    static std::default_random_engine eng{static_cast<long unsigned int>(time(nullptr))};

    auto getRandom(double probability) {
        std::mt19937 gen(eng());
        std::bernoulli_distribution dist(probability);
        return dist(gen);
    }

    auto getRandom() {
        std::mt19937 gen(eng());
        std::uniform_real_distribution<> distr;
        return distr(gen);
    }

    auto getRandom(int from, int to) {
        std::mt19937 gen(eng());
        std::uniform_int_distribution<> distr(from, to);
        return distr(gen);
    }

    template<typename T>
    auto randomShuffle(std::vector<T> &vec) {
        std::random_device rd;
        auto rng = std::default_random_engine{rd()};
        std::shuffle(vec.begin(), vec.end(), rng);
    }

    template<typename T>
    void saveToFile(const std::string &filename, const T &content) {
        std::ofstream file(filename, std::ios_base::app);
        file << content << '\n';
        file.close();
    }

}

#endif //HOMOPHILY_STRUCTURAL_BALANCE_UTILS_HPP
