#ifndef HOMOPHILY_STRUCTURAL_BALANCE_COMPLETEGRAPH_HPP
#define HOMOPHILY_STRUCTURAL_BALANCE_COMPLETEGRAPH_HPP

#include <vector>
#include <tuple>
#include "Node.hpp"
#include "Utils.hpp"

template<unsigned int SIZE>
using AdjenencyMatrix = std::array<std::array<bool, SIZE>, SIZE>;

template<unsigned int SIZE, unsigned int G>
class CompleteGraph {
    std::array<Node<G>, SIZE> _nodes{};

public:
    CompleteGraph<SIZE, G>();

    [[nodiscard]] std::tuple<Node<G>, Node<G>, Node<G>> getRandomStateTriad() const;

    void updateNode(const Node<G> &newNode);

    [[nodiscard]] auto getNodes() const { return _nodes; }
};

template<unsigned int SIZE, unsigned int G>
std::tuple<Node<G>, Node<G>, Node<G>> CompleteGraph<SIZE, G>::getRandomStateTriad() const {
    // Sample 3 random nodes (they are connected because the graph is complete)
    auto i = utils::getRandom(0, SIZE - 1);

    auto j = utils::getRandom(0, SIZE - 1);
    while (i == j)
        j = utils::getRandom(0, SIZE - 1);

    auto k = utils::getRandom(0, SIZE - 1);
    while (k == i || k == j)
        k = utils::getRandom(0, SIZE - 1);

    return std::make_tuple(_nodes.at(i), _nodes.at(j), _nodes.at(k));
}

template<unsigned int SIZE, unsigned int G>
CompleteGraph<SIZE, G>::CompleteGraph() {
    for (unsigned int i = 0; i < SIZE; ++i)
        _nodes.at(i) = Node<G>(i);
}

template<unsigned int SIZE, unsigned int G>
void CompleteGraph<SIZE, G>::updateNode(const Node<G> &newNode) {
    const auto it = std::find(_nodes.begin(), _nodes.end(), newNode);
    if (it != _nodes.end()) {
        const auto index = std::distance(_nodes.begin(), it);
        _nodes.at(index) = newNode;
    }
}

template<unsigned int SIZE, unsigned int G>
std::ostream &operator<<(std::ostream &os, const CompleteGraph<SIZE, G> &graph) {
    const auto matrix = graph.getAdjenencyMatrix();
    for (unsigned int i = 0; i < SIZE; ++i) {
        for (unsigned int j = 0; j < SIZE; ++j)
            os << matrix[i][j] << " ";
        os << "\n";
    }
    return os;
}

#endif //HOMOPHILY_STRUCTURAL_BALANCE_COMPLETEGRAPH_HPP
