#ifndef HOMOPHILY_STRUCTURAL_BALANCE_SIMULATION_H
#define HOMOPHILY_STRUCTURAL_BALANCE_SIMULATION_H

#include "Graph.hpp"
#include "Node.hpp"
#include "Metrics.h"

template<unsigned int SIZE, unsigned int G>
class Simulation {

    Graph<SIZE, G> _graph;

public:
    Simulation();

    void run(double p, unsigned int iterations);

private:
    void singleStep(double p);

};

template<unsigned int SIZE, unsigned int G>
void Simulation<SIZE, G>::run(double p, unsigned int iterations) {
    for (unsigned int i = 0; i < iterations; ++i) {
        std::cout << "Positive links density at step " << i << " = " << metrics::positiveLinksDensity(_graph)
                  << std::endl;
        singleStep(p);
    }
}

template<unsigned int SIZE, unsigned int G>
Simulation<SIZE, G>::Simulation() {
    _graph = Graph<SIZE, G>::completeGraph();
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

//    std::cout << "i: " << i << " j: " << j << " k: " << k << std::endl;
//    std::cout << "p_ij: " << p_ij << " p_jk: " << p_jk << " p_ik: " << p_ik << std::endl;
    const auto outputPolarity = p_ij * p_jk * p_ik;
    if (outputPolarity == -1) {
        const auto triadType = p_ij + p_jk + p_ik;
//        std::cout << "Triad type: " << triadType << "\n";
        Node<G> toUpdate;
        if (triadType == -3) {
            // \Delta_3
            switch (utils::getRandom(0, 2)) {
                case 0:
                    toUpdate = i;
                    break;
                case 1:
                    toUpdate = j;
                    break;
                case 2:
                    toUpdate = k;
                    break;
                default:
                    break;
            }
            toUpdate.flipToPositive(1);
        } else if (triadType == 1) {
            //  \Delta_1
            if (p < utils::getRandom()) {
                // negative link is chosen
                if (p_ij * p_jk == -1) {
                    toUpdate = j;
                } else if (p_jk * p_ik == -1) {
                    toUpdate = k;
                } else if (p_ij * p_ik == -1) {
                    toUpdate = i;
                }
                toUpdate.flipToPositive(1);
            } else {
                // positive link is chosen
                if (p_ij * p_jk == 1) {
                    toUpdate = j;
                } else if (p_jk * p_ik == 1) {
                    toUpdate = k;
                } else if (p_ij * p_ik == 1) {
                    toUpdate = i;
                }
                toUpdate.flipToNegative(1);
            }
        }
        _graph.updateNode(toUpdate);
    }
}

#endif //HOMOPHILY_STRUCTURAL_BALANCE_SIMULATION_H
