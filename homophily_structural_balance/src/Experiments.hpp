#ifndef HOMOPHILY_STRUCTURAL_BALANCE_EXPERIMENTS_HPP
#define HOMOPHILY_STRUCTURAL_BALANCE_EXPERIMENTS_HPP

#include <string>
#include <vector>
#include <cmath>
#include "Simulation.hpp"
#include "Metrics.hpp"
#include "Utils.hpp"

namespace experiments {
    template<unsigned int SIZE, unsigned int G>
    double singleSimulation(Simulation<SIZE, G> &simulation, double p, unsigned int maxIterations);

    bool isStationaryState(std::vector<double> &rhos, double epsilon = 0.005, unsigned int nLast = 10);

    template<unsigned int SIZE, unsigned int G>
    void phaseDiagramRhoVsP(Simulation<SIZE, G> &simulation, double pStart, double pStop,
                            unsigned int pSteps, unsigned int maxIterations,
                            const std::string &filename, unsigned int nTimes = 5) {
        const double h = (pStop - pStart) / pSteps;
        utils::saveToFile(filename, "p\trho");
        for (double p = pStart; p < pStop; p += h) {
            std::cout << "Running simulation for p = " << p << std::endl;
            double averagedRho{0};
            for (auto i = 0; i < nTimes; ++i)
                averagedRho += singleSimulation(simulation, p, maxIterations);
            averagedRho /= nTimes;
            utils::saveToFile(filename, std::to_string(p) + "\t" + std::to_string(averagedRho));
        }
    }

    template<unsigned int SIZE, unsigned int G>
    double singleSimulation(Simulation<SIZE, G> &simulation, double p, unsigned int maxIterations) {
        simulation.resetGraph();
        bool isDone = false;
        double averagedRho{0};
        unsigned int n{0};
        std::vector<double> rhos;

        // Check positive links density 100 times in total
        // If last 10 rho values are very similar, break the loop and return the last value
        const auto checkPerSteps = maxIterations / 100;
        while (!isDone && n < maxIterations) {
            simulation.singleStep(p);
            if (n % checkPerSteps == 0) {
                std::cout << "n = " << n << '\n';
                if (isStationaryState(rhos))
                    isDone = true;
                else {
                    averagedRho = metrics::positiveLinksDensity(simulation.getGraph());
                    rhos.push_back(averagedRho);
                }
            }
            n++;
        }
        return averagedRho;
    }


    bool isStationaryState(std::vector<double> &rhos, double epsilon, unsigned int nLast) {
        if (rhos.size() == nLast) {
            const auto lastValue = rhos.at(rhos.size() - 1);
            double totalEpsilon{0};
            for (const auto &rho: rhos)
                totalEpsilon += std::abs(lastValue - rho);

            if (totalEpsilon < epsilon * rhos.size()) {
                return true;
            } else {
                // Remove the first element of the vector
                // and only store `nLast` elements at the time
                rhos.erase(rhos.begin());
                return false;
            }
        } else
            return false;
    }

}

#endif //HOMOPHILY_STRUCTURAL_BALANCE_EXPERIMENTS_HPP
