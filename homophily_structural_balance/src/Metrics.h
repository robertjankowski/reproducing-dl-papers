#ifndef HOMOPHILY_STRUCTURAL_BALANCE_METRICS_H
#define HOMOPHILY_STRUCTURAL_BALANCE_METRICS_H

#include "Graph.hpp"

namespace metrics {

    template<unsigned int SIZE, unsigned int G>
    double positiveLinksDensity(const Graph<SIZE, G> &g) {
        const auto nodes = g.getNodes();
        const auto matrix = g.getAdjenencyMatrix();
        int positiveLinks{0};
        int totalLinks{0};
        for (unsigned int i = 0; i < SIZE; ++i) {
            for (unsigned int j = 0; j < i; ++j) { // or check if not `j < SIZE`
                if (matrix[i][j]) {
                    const auto source = nodes.at(i);
                    const auto target = nodes.at(j);
                    if (polarities(source, target) == State::Positive)
                        positiveLinks += 1;
                    totalLinks += 1;
                }
            }
        }
        return static_cast<double>(positiveLinks) / totalLinks;
    }

}


#endif //HOMOPHILY_STRUCTURAL_BALANCE_METRICS_H
