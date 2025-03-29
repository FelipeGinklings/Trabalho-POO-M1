//
// Created by Felipe Notebook on 25/03/2025.
//

#include "Date.hpp"

#include <iostream>

void Date::print() const { std::cout << this->day << "/" << this->month << "/" << this->year << std::endl; }

Date::Date(const int day, const int month, const int year) {
    this->day = day;
    this->month = month;
    this->year = year;
}
Date::Date() {
    this->day = 0;
    this->month = 0;
    this->year = 0;
}
