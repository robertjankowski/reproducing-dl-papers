#ifndef HOMOPHILY_STRUCTURAL_BALANCE_SIMULATION_H
#define HOMOPHILY_STRUCTURAL_BALANCE_SIMULATION_H

#include "CompleteGraph.hpp"
#include "Node.hpp"
#include "Metrics.h"

template<unsigned int SIZE, unsigned int G>
class Simulation {

    CompleteGraph<SIZE, G> _graph{};

public:

    void run(double p, unsigned int iterations);

private:
    void singleStep(double p);

    void updateTriadDeltaThree(const Node<G> &i, const Node<G> &j, const Node<G> &k, Node<G> &toUpdate);

    void updateTriadDeltaOne(const Node<G> &i, const Node<G> &j, const Node<G> &k,
                             int p_ij, int p_jk, int p_ik, Node<G> &toUpdate, double p);

};

template<unsigned int SIZE, unsigned int G>
void Simulation<SIZE, G>::run(double p, unsigned int iterations) {
    for (unsigned int i = 0; i < iterations; ++i) {
        if (i % 5000 == 0) {
            std::cout << "Positive links density at step " << i << " = " << metrics::positiveLinksDensity(_graph)
                      << std::endl;
        }
        singleStep(p);
    }
}

template<unsigned int SIZE, unsigned int G>
void Simulation<SIZE, G>::singleStep(double p) {
    // 1. find triad in graph
    //  1.1. return (i, j, k) nodes
    // 2. calculate polarity of each pairs
    // 3. apply triad update rule if p_ij * p_jk * p_ik = -1
    //  3.1. check type of unbalanced triad
    //  \Delta_1 ->
    //    - with probability `p` the negative link is chosen
    //          -> select one of the nodes and swap one attribute to -1
    //    - with probability `1 - p` the positive link is chosen
    //          -> select one of the nodes and swap one attribute to +1
    //  \Delta_3 -> choose one node and swap one of his attribute

    auto[i, j, k] = _graph.getRandomStateTriad();
    const auto p_ij = static_cast<int>(polarities(i, j));
    const auto p_jk = static_cast<int>(polarities(j, k));
    const auto p_ik = static_cast<int>(polarities(i, k));

    const auto outputPolarity = p_ij * p_jk * p_ik;
    if (outputPolarity == -1) {
        const auto triadType = p_ij + p_jk + p_ik;
        Node<G> toUpdate = i; // do not create new object each time
        if (triadType == -3) {
            // \Delta_3
            updateTriadDeltaThree(i, j, k, toUpdate);
        } else if (triadType == 1) {
            // \Delta_1
            updateTriadDeltaOne(i, j, k, p_ij, p_jk, p_ik, toUpdate, p);
        }
        _graph.updateNode(toUpdate);
    }
}

template<unsigned int SIZE, unsigned int G>
void Simulation<SIZE, G>::updateTriadDeltaThree(const Node<G> &i, const Node<G> &j, const Node<G> &k,
                                                Node<G> &toUpdate) {
    switch (utils::getRandom(0, 2)) {
        case 0:
            toUpdate = Node<G>::flipNegativeEdge(i, j);
            break;
        case 1:
            toUpdate = Node<G>::flipNegativeEdge(j, k);
            break;
        case 2:
            toUpdate = Node<G>::flipNegativeEdge(i, k);
            break;
        default:
            break;
    }
}

template<unsigned int SIZE, unsigned int G>
void Simulation<SIZE, G>::updateTriadDeltaOne(const Node<G> &i, const Node<G> &j, const Node<G> &k,
                                              int p_ij, int p_jk, int p_ik, Node<G> &toUpdate, double p) {
    if (p > utils::getRandom()) {
        // Choose negative edge
        if (p_ij == -1) {
            toUpdate = Node<G>::flipNegativeEdge(i, j);
        } else if (p_jk == -1) {
            toUpdate = Node<G>::flipNegativeEdge(j, k);
        } else if (p_ik == -1) {
            toUpdate = Node<G>::flipNegativeEdge(i, k);
        }
    } else {
        // Choose positive edge
        if (p_ij == 1) {
            toUpdate = Node<G>::flipPositiveEdge(i, j);
        } else if (p_jk == 1) {
            toUpdate = Node<G>::flipPositiveEdge(j, k);
        } else if (p_ik == 1) {
            toUpdate = Node<G>::flipPositiveEdge(i, k);
        }
    }
}


#endif //HOMOPHILY_STRUCTURAL_BALANCE_SIMULATION_H
