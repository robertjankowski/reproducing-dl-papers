#ifndef HOMOPHILY_STRUCTURAL_BALANCE_GRAPH_HPP
#define HOMOPHILY_STRUCTURAL_BALANCE_GRAPH_HPP

#include <vector>
#include <map>
#include "Node.hpp"


template<typename T>
using AdjenencyList = std::map<T, std::vector<T>>;

template<unsigned int G>
class Graph {
    AdjenencyList<Node<G>> _adjenencyList{};


public:
    void addEdge(const Node<G> &source, const Node<G> &target);

    [[nodiscard]] auto getAdjenencyList() const { return _adjenencyList; }

    // TODO:
    //  0. add id to each node (in Node class)
    //  1. create edges
    //  2. Graph structure
    //  3. Find triads in network ?
    //  4. triangle update rule

};

template<unsigned int G>
void Graph<G>::addEdge(const Node<G> &source, const Node<G> &target) {
    if (_adjenencyList.find(source) == _adjenencyList.end())
        _adjenencyList[source] = {};
    _adjenencyList[source].push_back(target);
}

template<unsigned int G>
std::ostream &operator<<(std::ostream &os, const Graph<G> &graph) {
    for (const auto&[target, sources]: graph.getAdjenencyList())
        for (const auto &source: sources)
            os << target << ": " << source;
    return os;
}


#endif //HOMOPHILY_STRUCTURAL_BALANCE_GRAPH_HPP
