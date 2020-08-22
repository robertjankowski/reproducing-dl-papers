#ifndef HOMOPHILY_STRUCTURAL_BALANCE_SIMULATION_HPP
#define HOMOPHILY_STRUCTURAL_BALANCE_SIMULATION_HPP

#include <fstream>
#include <sstream>
#include "CompleteGraph.hpp"
#include "Node.hpp"
#include "Metrics.hpp"

template<unsigned int SIZE, unsigned int G>
class Simulation {

    CompleteGraph<SIZE, G> _graph{};

public:
    std::string prepareFilename(const std::string &prefix, double p, unsigned int iterations);

    double run(double p, unsigned int iterations, const std::string &filename,
               bool calculateParadiseProbability = false);

    void resetGraph();

    auto getGraph() const { return _graph; }

    int singleStep(double p, bool calculateParadiseProbability = false);

private:
    void updateTriadDeltaThree(const Node<G> &i, const Node<G> &j, const Node<G> &k, Node<G> &toUpdate);

    void updateTriadDeltaOne(const Node<G> &i, const Node<G> &j, const Node<G> &k,
                             int p_ij, int p_jk, int p_ik, Node<G> &toUpdate, double p);

    void saveMetrics(const std::string &filename);

    int checkParadiseState(const Node<G> &i, const Node<G> &j, const Node<G> &k, const Node<G> &toUpdate, int p_ij,
                           int p_jk, int p_ik);

    int isParadiseState(const Node<G> &x, const Node<G> &y, const Node<G> &toUpdate, int p_xy);
};

template<unsigned int SIZE, unsigned int G>
double Simulation<SIZE, G>::run(double p, unsigned int iterations, const std::string &filename,
                                bool calculateParadiseProbability) {
    auto paradiseProbability{0.0};
    for (unsigned int i = 0; i < iterations; ++i) {
        if (i % 5000 == 0) {
            saveMetrics(filename);
            std::cout << "Positive links density at step " << i << " = " << metrics::positiveLinksDensity(_graph)
                      << std::endl;
        }
        std::cout << "i  = " << i << '\n';
        paradiseProbability += singleStep(p, calculateParadiseProbability);
    }
    if (calculateParadiseProbability) {
        return paradiseProbability / iterations;
    } else {
        return -1;
    }
}

template<unsigned int SIZE, unsigned int G>
int Simulation<SIZE, G>::singleStep(double p, bool calculateParadiseProbability) {
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
        if (calculateParadiseProbability) {
            return checkParadiseState(i, j, k, toUpdate, p_ij, p_jk, p_ik);
        }
    }
    return -1;
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

template<unsigned int SIZE, unsigned int G>
void Simulation<SIZE, G>::saveMetrics(const std::string &filename) {
    utils::saveToFile<double>(filename, metrics::positiveLinksDensity(_graph));
//    std::ofstream file(filename, std::ios_base::app);
//    file << metrics::positiveLinksDensity(_graph) << '\n';
//    file.close();
}

template<unsigned int SIZE, unsigned int G>
std::string Simulation<SIZE, G>::prepareFilename(const std::string &prefix, double p, unsigned int iterations) {
    std::time_t t = std::time(nullptr);
    auto now = std::localtime(&t);
    std::stringstream ss;
    ss << prefix << "_p=" << p << "_iterations=" << iterations << "_SIZE=" << SIZE << "_G=" << G << "_";
    ss << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << "_";
    ss << now->tm_mday << "-" << now->tm_mon << "-" << now->tm_year << ".dat";
    return ss.str();
}

template<unsigned int SIZE, unsigned int G>
void Simulation<SIZE, G>::resetGraph() {
    _graph = CompleteGraph<SIZE, G>();
}

template<unsigned int SIZE, unsigned int G>
int Simulation<SIZE, G>::checkParadiseState(const Node<G> &i, const Node<G> &j, const Node<G> &k,
                                            const Node<G> &toUpdate, int p_ij, int p_jk, int p_ik) {
    if (toUpdate == i) {
        return isParadiseState(j, k, toUpdate, p_jk);
    } else if (toUpdate == j) {
        return isParadiseState(i, k, toUpdate, p_ik);
    } else if (toUpdate == k) {
        return isParadiseState(i, j, toUpdate, p_ij);
    } else {
        return 0;
    }
}

template<unsigned int SIZE, unsigned int G>
int Simulation<SIZE, G>::isParadiseState(const Node<G> &x, const Node<G> &y, const Node<G> &toUpdate, int p_xy) {
    const auto p_ux = static_cast<int>(polarities(toUpdate, x));
    const auto p_uy = static_cast<int>(polarities(toUpdate, y));
    if ((p_ux == 1) && (p_uy == 1) && (p_xy == 1)) {
        return 1;
    } else {
        return 0;
    }
}


#endif //HOMOPHILY_STRUCTURAL_BALANCE_SIMULATION_HPP
