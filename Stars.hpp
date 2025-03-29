//
// Created by Felipe Notebook on 25/03/2025.
//

#ifndef STARS_HPP
#define STARS_HPP
#include <string>
#include <utility>
#include <vector>

struct Grade {
    std::string id;
    int stars;

    Grade(std::string id, const int stars) : id(std::move(id)), stars(stars) {}
};


class Stars {
    std::vector<Grade> vecOfStars;
    int stars;

    void calculateStars();

public:
    void addStars(const std::string &id, int stars);

    [[nodiscard]] size_t amountOfAvaliations() const;

    [[nodiscard]] int getStars() const;

    Stars();
};


#endif  // STARS_HPP
