#include <iostream>
#include "Node.hpp"
#include "Graph.hpp"

int main() {
    auto n = Node<10>();
    const auto n2 = Node<10>();
    std::cout << n << std::endl;
    std::cout << n2 << std::endl;
    std::cout << static_cast<int>(polarities(n, n2)) << std::endl;
    n.changeAttribute(0, State::Positive);
    std::cout << n << std::endl;

    auto g = Graph<10>();
    g.addEdge(n, n2);
    std::cout << "Graph: " << std::endl;
    std::cout << g << std::endl;


    return 0;
}
