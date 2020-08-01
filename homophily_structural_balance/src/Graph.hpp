#ifndef HOMOPHILY_STRUCTURAL_BALANCE_GRAPH_HPP
#define HOMOPHILY_STRUCTURAL_BALANCE_GRAPH_HPP

#include <vector>
#include <tuple>
#include "Node.hpp"
#include "utils.h"

template<unsigned int SIZE>
using AdjenencyMatrix = std::array<std::array<bool, SIZE>, SIZE>;

template<unsigned int SIZE, unsigned int G>
class Graph {
    AdjenencyMatrix<SIZE> _matrix{};
    std::array<Node<G>, SIZE> _nodes{};

public:
    Graph<SIZE, G>();

    void addEdge(const Node<G> &source, const Node<G> &target);

    void addEdgeUndirected(const Node<G> &source, const Node<G> &target);

    [[nodiscard]] std::tuple<Node<G>, Node<G>, Node<G>> getRandomStateTriad() const;

    void updateNode(const Node<G> &newNode);

    static Graph<SIZE, G> completeGraph();

    [[nodiscard]] auto getAdjenencyMatrix() const { return _matrix; }

};

template<unsigned int SIZE, unsigned int G>
void Graph<SIZE, G>::addEdge(const Node<G> &source, const Node<G> &target) {
    auto sourceId = source.getId();
    auto targetId = target.getId();
    if (sourceId < SIZE && targetId < SIZE) {
        _matrix[sourceId][targetId] = true;
        _nodes.at(sourceId) = source;
        _nodes.at(targetId) = target;
    } else
        std::cerr << "Matrix size is smaller than source or target ID\n";
}


template<unsigned int SIZE, unsigned int G>
void Graph<SIZE, G>::addEdgeUndirected(const Node<G> &source, const Node<G> &target) {
    addEdge(source, target);
    addEdge(target, source);
}

template<unsigned int SIZE, unsigned int G>
Graph<SIZE, G> Graph<SIZE, G>::completeGraph() {
    auto g = Graph<SIZE, G>();
    for (unsigned int i = 0; i < SIZE; ++i)
        for (unsigned int j = 0; j < i; ++j)
            g.addEdgeUndirected(Node<G>(i), Node<G>(j));
    return g;
}

template<unsigned int SIZE, unsigned int G>
std::tuple<Node<G>, Node<G>, Node<G>> Graph<SIZE, G>::getRandomStateTriad() const {
    // Assumption: graph has at least one triad, otherwise function goes into infinity loop :/
    std::vector<Node<G>> triad{};
    while (triad.size() != 3) {
        triad.clear();
        unsigned int random = utils::getRandom(0, SIZE - 1);
        triad.push_back(_nodes.at(random));

        std::vector<unsigned int> possibleNodes{};
        for (unsigned int ii = 0; ii < SIZE; ++ii) {
            if (_matrix[random][ii] && ii != random)
                possibleNodes.push_back(ii);
        }
        if (possibleNodes.empty())
            continue; // given node has not got any neighbours
        utils::randomShuffle(possibleNodes);

        bool found = false;
        while (!found) {
            const auto randomJ = utils::getRandom(0, possibleNodes.size() - 1);
            const auto randomK = utils::getRandom(0, possibleNodes.size() - 1);
            if (randomJ != randomK) {
                const auto j = possibleNodes.at(randomJ);
                const auto k = possibleNodes.at(randomK);
                if (_matrix[j][k] && _matrix[k][j]) {
                    triad.push_back(_nodes.at(j));
                    triad.push_back(_nodes.at(k));
                    found = true;
                }
            }
        }
    }

    return std::make_tuple(triad.at(0), triad.at(1), triad.at(2));
}

template<unsigned int SIZE, unsigned int G>
Graph<SIZE, G>::Graph() {
    for (unsigned int i = 0; i < SIZE; ++i)
        for (unsigned int j = 0; j < SIZE; ++j)
            _matrix[i][j] = false;
}

template<unsigned int SIZE, unsigned int G>
void Graph<SIZE, G>::updateNode(const Node<G> &newNode) {
    // check if node with that id exists and update if
    const auto it = std::find(_nodes.begin(), _nodes.end(), newNode);
    if (it != _nodes.end()) {
        const auto index = std::distance(_nodes.begin(), it);
        _nodes.at(index) = newNode;
    }
}


template<unsigned int SIZE, unsigned int G>
std::ostream &operator<<(std::ostream &os, const Graph<SIZE, G> &graph) {
    const auto matrix = graph.getAdjenencyMatrix();
    for (unsigned int i = 0; i < SIZE; ++i) {
        for (unsigned int j = 0; j < SIZE; ++j)
            os << matrix[i][j] << " ";
        os << "\n";
    }
    return os;
}


#endif //HOMOPHILY_STRUCTURAL_BALANCE_GRAPH_HPP
