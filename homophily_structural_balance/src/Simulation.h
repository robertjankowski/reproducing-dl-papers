#ifndef HOMOPHILY_STRUCTURAL_BALANCE_SIMULATION_H
#define HOMOPHILY_STRUCTURAL_BALANCE_SIMULATION_H

#include "Graph.hpp"
#include "Node.hpp"

template<unsigned int SIZE, unsigned int G>
class Simulation {

    Graph<SIZE, G> _graph;

public:
    void run(double p, unsigned int iterations);

};

template<unsigned int SIZE, unsigned int G>
void Simulation<SIZE, G>::run(double p, unsigned int iterations) {
    // TODO:
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
        if (triadType == -3) {
            // \Delta_3
            Node<G> toUpdate;
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
            // Test that function ->
            toUpdate.flipToPositive(1);
            _graph.updateNode(toUpdate);
        } else if (triadType == 1) {
            // TODO:
            //  \Delta_1
            if (p < utils::getRandom()) {
                // negative link is chosen
            } else {
                // positive link is chosen
            }
        }
    }
}

#endif //HOMOPHILY_STRUCTURAL_BALANCE_SIMULATION_H
