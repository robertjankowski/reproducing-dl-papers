#ifndef HOMOPHILY_STRUCTURAL_BALANCE_GRAPH_HPP
#define HOMOPHILY_STRUCTURAL_BALANCE_GRAPH_HPP

#include <vector>
#include <map>
#include "Node.hpp"

template<unsigned int SIZE>
using AdjenencyMatrix = bool[SIZE][SIZE];

template<unsigned int SIZE, unsigned int G>
class Graph {
    AdjenencyMatrix<SIZE> _matrix{};
    std::array<Node<G>, SIZE> _nodes{};

public:
    Graph<SIZE, G>();

    void addEdge(const Node<G> &source, const Node<G> &target);

    void addEdgeUndirected(const Node<G> &source, const Node<G> &target);

    [[nodiscard]] State getRandomStateTriad() const;

    static Graph<SIZE, G> completeGraph();

    [[nodiscard]] auto getAdjenencyMatrix() const { return _matrix; }

    // TODO:
    //  3. Find triads in network ?
    //  4. triangle update rule

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
State Graph<SIZE, G>::getRandomStateTriad() const {
    // TODO:
    //  Return (i, j, k) nodes and State
    //  --
    //  choose random 2 neighbours and check if they are connected
    //  repeat until the triad will be found
    int random = rand() % SIZE;

    for (unsigned int i = 0; i < SIZE; ++i) {
        std::cout << _matrix[random][i] << " ";
    }

    return State::Negative;
}

template<unsigned int SIZE, unsigned int G>
Graph<SIZE, G>::Graph() {
    for (unsigned int i = 0; i < SIZE; ++i) {
        for (unsigned int j = 0; j < SIZE; ++j) {
            _matrix[i][j] = false;
        }
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
