//
// Created by Felipe Notebook on 25/03/2025.
//

#include "Stars.hpp"

void Stars::calculateStars() {
    for (const auto &grade: this->vecOfStars) this->stars += grade.stars;
    this->stars /= this->vecOfStars.size();
}

void Stars::addStars(const std::string &id, const uint8_t stars) {
    for (auto &grade: this->vecOfStars) {
        if (grade.id == id) {
            grade.stars = stars;
            calculateStars();
            return;
        }
    }
    this->vecOfStars.push_back(Grade(id, stars));
    calculateStars();
}

int Stars::amountOfAvaliations() const { return vecOfStars.size(); }

uint8_t Stars::getStars() const { return this->stars; }

Stars::Stars() { this->stars = 0; }
