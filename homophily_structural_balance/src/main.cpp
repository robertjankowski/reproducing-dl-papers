#include <iostream>
#include <chrono>
#include "Simulation.hpp"
#include "Experiments.hpp"

int main() {
    Simulation<3, 101> s;
    constexpr double p = 0.68;
    constexpr unsigned int iterations = 2000000;
    const auto filename = s.prepareFilename("../phase-rhop", p, iterations);

    auto start = std::chrono::steady_clock::now();

    experiments::phaseDiagramRhoVsP(s, 0, 1.0, 10, iterations, filename);
//    experiments::phaseDiagramPpVsP(s, 0, 1, 10, iterations, filename);

    auto end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms\n";
    
    return 0;
}
