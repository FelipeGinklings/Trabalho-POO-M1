//
// Created by Felipe Notebook on 25/03/2025.
//

#ifndef STARS_HPP
#define STARS_HPP
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

struct Grade {
    std::string id;
    uint8_t stars;

    Grade(std::string id, const uint8_t stars) : id(std::move(id)), stars(stars) {}
};


class Stars {
    std::vector<Grade> vecOfStars;
    uint8_t stars;

    void calculateStars();

public:
    void addStars(const std::string &id, uint8_t stars);

    [[nodiscard]] size_t amountOfAvaliations() const;

    [[nodiscard]] uint8_t getStars() const;

    Stars();
};


#endif  // STARS_HPP
