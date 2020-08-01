#include <iostream>
#include <chrono>
#include "Node.hpp"
#include "Graph.hpp"

int main() {
    auto n = Node<10>(0);
    const auto n2 = Node<10>(1);
    std::cout << n << std::endl;
    std::cout << n2 << std::endl;
    std::cout << static_cast<int>(polarities(n, n2)) << std::endl;
    n.changeAttribute(0, State::Positive);
    std::cout << n << std::endl;


    auto g = Graph<200, 10>::completeGraph();

    auto start = std::chrono::steady_clock::now();
    for (int ii = 0; ii < 10000; ++ii) {
        const auto[i, j, k] = g.getRandomStateTriad();
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";


    return 0;
}
