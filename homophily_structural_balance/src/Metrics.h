#ifndef HOMOPHILY_STRUCTURAL_BALANCE_METRICS_H
#define HOMOPHILY_STRUCTURAL_BALANCE_METRICS_H

#include "CompleteGraph.hpp"

namespace metrics {

    template<unsigned int SIZE, unsigned int G>
    double positiveLinksDensity(const CompleteGraph<SIZE, G> &g) {
        const auto nodes = g.getNodes();
        int positiveLinks{0}, totalLinks{0};
        for (unsigned int i = 0; i < SIZE; ++i) {
            for (unsigned int j = 0; j < i; ++j) { // or check if not `j < SIZE`
                const auto source = nodes.at(i);
                const auto target = nodes.at(j);
                if (polarities(source, target) == State::Positive)
                    positiveLinks += 1;
                totalLinks += 1;
            }
        }
        // Divide by two ?
        return static_cast<double>(positiveLinks) / totalLinks;
    }

}


#endif //HOMOPHILY_STRUCTURAL_BALANCE_METRICS_H
