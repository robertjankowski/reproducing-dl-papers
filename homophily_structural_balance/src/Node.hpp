#ifndef HOMOPHILY_STRUCTURAL_BALANCE_NODE_HPP
#define HOMOPHILY_STRUCTURAL_BALANCE_NODE_HPP

#include <array>
#include <random>
#include <algorithm>
#include "utils.h"

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

    void flipToPositive(unsigned int count);

private:
    [[nodiscard]] State getRandomState(double probability = 0.5) {
        if (utils::getRandom(probability))
            return State::Positive;
        else
            return State::Negative;
    }
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
void Node<G>::flipToPositive(unsigned int count) {
    std::vector<int> iterator(_attributes.size());
    std::iota(iterator.begin(), iterator.end(), 0);
    utils::randomShuffle(iterator);
    for (const auto &pos: iterator) {
        if (count < 1)
            break;
        if (_attributes.at(pos) == State::Negative) {
            _attributes.at(pos) == State::Positive;
            --count;
        }
    }
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
