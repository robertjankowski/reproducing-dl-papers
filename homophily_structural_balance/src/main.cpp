#include <iostream>
#include <chrono>
#include "Simulation.hpp"
#include "Experiments.hpp"

int main() {
    //  TODO:
    //   2. Calculate probability of reaching the paradise state (rho = 1) P_p ???
    //   3. Perform simulation to plot
    //       a) phase diagram `rho` vs `p` (Fig. 2, Fig. 4a)
    //       b) phase diagram `P_p` vs `p` (Fig. 5a,b)

    Simulation<399, 7> s;
    constexpr double p = 0.68;
    constexpr unsigned int iterations = 5000000;
    const auto filename = s.prepareFilename("../test", p, iterations);

    auto start = std::chrono::steady_clock::now();

    experiments::phaseDiagramRhoVsP(s, 0.90, 1.0, 10, iterations, filename);

    auto end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms\n";
    
    return 0;
}
