//
// Created by Felipe Notebook on 25/03/2025.
//

#include "Date.hpp"

#include <iostream>

void Date::print() const {
    std::cout << static_cast<int>(day) << "/" << static_cast<int>(month) << "/" << static_cast<int>(year) << std::endl;
}

Date::Date(const uint16_t day, const uint8_t month, const uint16_t year) {
    this->day = day;
    this->month = month;
    this->year = year;
}
Date::Date() {
    this->day = 0;
    this->month = 0;
    this->year = 0;
}
