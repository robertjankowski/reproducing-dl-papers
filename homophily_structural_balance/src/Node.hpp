#ifndef HOMOPHILY_STRUCTURAL_BALANCE_NODE_HPP
#define HOMOPHILY_STRUCTURAL_BALANCE_NODE_HPP

#include <array>
#include <random>
#include <algorithm>
#include "Utils.h"

enum class State {
    Positive = 1,
    Negative = -1
};

template<unsigned int G>
class Node {
    std::array<State, G> _attributes;
    unsigned int _id{0};
public:
    explicit Node(int id);

    Node() : Node(0) {}

    [[nodiscard]] auto getAttributes() const { return _attributes; }

    [[nodiscard]] auto getId() const { return _id; }

    void changeAttribute(unsigned int pos, const State &state);

    static Node<G> flipPositiveEdge(const Node<G> &nodeA, const Node<G> &nodeB, unsigned int count = 1);

    static Node<G> flipNegativeEdge(const Node<G> &nodeA, const Node<G> &nodeB, unsigned int count = 1);

    bool operator==(const Node<G> &node) {
        return _id == node.getId();
    }

private:
    [[nodiscard]] State getRandomState(double probability = 0.5) {
        if (utils::getRandom(probability))
            return State::Positive;
        else
            return State::Negative;
    }

    [[nodiscard]] static Node<G> getRandomNode(const Node<G> &nodeA, const Node<G> &nodeB, double probabilityA = 0.5) {
        if (utils::getRandom(probabilityA))
            return nodeA;
        else
            return nodeB;
    }

    static Node<G> flipEdge(const Node<G> &nodeA, const Node<G> &nodeB,
                            const std::string &negOrPos, unsigned int count = 1);
};

template<unsigned int G>
std::ostream &operator<<(std::ostream &os, const Node<G> &node) {
    os << node.getId() << ": ";
    const auto nodeAttributes = node.getAttributes();
    std::for_each(nodeAttributes.begin(), nodeAttributes.end(), [&os](const auto &state) {
        os << static_cast<int>(state) << ", ";
    });
    return os;
}

template<unsigned int G>
Node<G>::Node(int id): _id(id) {
    std::generate(_attributes.begin(), _attributes.end(), [&]() { return getRandomState(); });
}

template<unsigned int G>
void Node<G>::changeAttribute(unsigned int pos, const State &state) {
    if (_attributes.size() < pos)
        std::cerr << "Cannot change attribute. Position [" << pos << "] is out bigger than vector size\n";
    else
        _attributes.at(pos) = state;
}

template<unsigned int G>
Node<G> Node<G>::flipPositiveEdge(const Node<G> &nodeA, const Node<G> &nodeB, unsigned int count) {
    return flipEdge(nodeA, nodeB, "positive", count);
}

template<unsigned int G>
Node<G> Node<G>::flipNegativeEdge(const Node<G> &nodeA, const Node<G> &nodeB, unsigned int count) {
    return flipEdge(nodeA, nodeB, "negative", count);
}

template<unsigned int G>
Node<G> Node<G>::flipEdge(const Node<G> &nodeA, const Node<G> &nodeB,
                          const std::string &negOrPos, unsigned int count) {
//    std::cout << "NodeA: " << nodeA << "\tNodeB: " << nodeB << std::endl;
    Node<G> result = getRandomNode(nodeA, nodeB);
    const auto attrA = nodeA.getAttributes();
    const auto attrB = nodeB.getAttributes();
    std::vector<int> states;

    for (unsigned int i = 0; i < attrA.size(); ++i) {
        if ((negOrPos == "negative" && attrA.at(i) != attrB.at(i)) ||
            (negOrPos == "positive" && attrA.at(i) == attrB.at(i))) {
            states.push_back(i);
        }
    }

    utils::randomShuffle(states);
//    std::cout << "Chosen states: ";
//    for (auto a: states)
//        std::cout << a << '\t';
//    std::cout << '\n';
    states.resize(count); // only change `count` attributes

    for (const auto &pos: states) {
        switch (result.getAttributes().at(pos)) {
            case State::Positive:
                result.changeAttribute(pos, State::Negative);
                break;
            case State::Negative:
                result.changeAttribute(pos, State::Positive);
            default:
                break;
        }
    }
    return result;
}

template<unsigned int G>
double hammingDistance(const Node<G> &n1, const Node<G> &n2) {
    double distance{0};
    for (unsigned int i = 0; i < G; ++i) {
        const auto ai = static_cast<int>(n1.getAttributes().at(i));
        const auto aj = static_cast<int>(n2.getAttributes().at(i));
        distance += ai * aj;
    }
    return distance / (2 * G);
}

template<unsigned int G>
State polarities(const Node<G> &n1, const Node<G> &n2) {
    auto polarity = hammingDistance(n1, n2);
    if (polarity > 0)
        return State::Positive;
    else
        return State::Negative;
}

#endif //HOMOPHILY_STRUCTURAL_BALANCE_NODE_HPP
