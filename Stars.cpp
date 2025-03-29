//
// Created by Felipe Notebook on 25/03/2025.
//

#include "Stars.hpp"

void Stars::calculateStars() {
    int stars = 0;
    for (const auto &grade: this->vecOfStars) stars += grade.stars;
    stars /= this->vecOfStars.size();
    this->stars = stars;
}

void Stars::addStars(const std::string &id, const int stars) {
    for (auto &grade: this->vecOfStars) {
        if (grade.id == id) {
            grade.stars = stars;
            calculateStars();
            return;
        }
    }
    this->vecOfStars.emplace_back(id, stars);
    calculateStars();
}

size_t Stars::amountOfAvaliations() const { return this->vecOfStars.size(); }

int Stars::getStars() const { return this->stars; }

Stars::Stars() { this->stars = 0; }
