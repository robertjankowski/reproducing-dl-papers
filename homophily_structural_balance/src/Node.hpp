#ifndef HOMOPHILY_STRUCTURAL_BALANCE_NODE_HPP
#define HOMOPHILY_STRUCTURAL_BALANCE_NODE_HPP

#include <array>
#include <random>
#include <algorithm>

enum class State {
    Positive = 1,
    Negative = -1
};

template<unsigned int G>
class Node {
    std::array<State, G> _attributes;

public:
    Node();

    [[nodiscard]] auto getAttributes() const { return _attributes; }

    void changeAttribute(unsigned int pos, State state);

    bool operator<(const Node<G> &node) const {
        return this->getTotalState() > node.getTotalState();
    }

private:
    State getRandomState() {
        const double probability = 0.5;
        static std::random_device rd;
        static std::mt19937 mt(rd());
        std::bernoulli_distribution dist(probability);
        if (dist(mt))
            return State::Positive;
        else
            return State::Negative;
    }

    [[nodiscard]] double getTotalState() const {
        double total{0.0};
        for (const auto &state: _attributes) {
            total += static_cast<int>(state);
        }
        return total;
    }
};

template<unsigned int G>
std::ostream &operator<<(std::ostream &os, const Node<G> &node) {
    const auto nodeAttributes = node.getAttributes();
    std::for_each(nodeAttributes.begin(), nodeAttributes.end(), [&os](const auto &state) {
        os << static_cast<int>(state) << ", ";
    });
    return os;
}

template<unsigned int G>
Node<G>::Node() {
    std::generate(_attributes.begin(), _attributes.end(), [&]() { return getRandomState(); });
}

template<unsigned int G>
void Node<G>::changeAttribute(unsigned int pos, State state) {
    if (_attributes.size() < pos)
        std::cerr << "Cannot change attribute. Position [" << pos << "] is out bigger than vector size\n";
    else
        _attributes.at(pos) = state;
}


template<unsigned int G>
State polarities(const Node<G> &n1, const Node<G> &n2) {
    double polarity{0};
    for (unsigned int i = 0; i < G; ++i) {
        const auto ai = static_cast<int>(n1.getAttributes().at(i));
        const auto aj = static_cast<int>(n2.getAttributes().at(i));
        polarity += ai * aj;
    }
    polarity /= 2 * G;
    if (polarity > 0)
        return State::Positive;
    else
        return State::Negative;
}

#endif //HOMOPHILY_STRUCTURAL_BALANCE_NODE_HPP
