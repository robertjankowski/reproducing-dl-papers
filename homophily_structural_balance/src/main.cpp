#include <iostream>
#include "Node.hpp"

int main() {
    auto n = Node<10>();
    const auto n2 = Node<10>();
    std::cout << n << std::endl;
    std::cout << n2 << std::endl;
    std::cout << static_cast<int>(polarities(n, n2)) << std::endl;
    n.changeAttribute(0, State::Positive);
    std::cout << n << std::endl;


    return 0;
}
