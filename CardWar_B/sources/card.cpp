

#include "card.hpp"

namespace ariel {
    Card::Card(std::string val, std::string shape) {
        cardValue_ = val;
        cardShape_ = shape;
    }

    std::string Card::getCardValue() {
        return cardValue_;
    }

    std::string Card::getCardShape() {
        return cardShape_;
    }
}
