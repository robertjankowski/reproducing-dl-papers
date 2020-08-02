#include <iostream>
#include <chrono>
#include "Node.hpp"
#include "Graph.hpp"
#include "Simulation.h"

int main() {
    // TODO:
    //  1. fix density of positive links results:
    //      - it could be the issue with simulation code or metrics calculations
    //  2. Calculate probability of reaching the paradise state (rho = 1) P_p ???
    //  3. Perform simulation to plot
    //      a) phase diagram `rho` vs `p` (Fig. 2, Fig. 4a)
    //      b) phase diagram `P_p` vs `p` (Fig. 5a,b)

    Simulation<11, 10001> s;

    auto start = std::chrono::steady_clock::now();

    s.run(0.8, 1000);

    auto end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";

    return 0;
}
