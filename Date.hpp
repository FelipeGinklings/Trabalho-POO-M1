//
// Created by Felipe Notebook on 25/03/2025.
//

#ifndef DATE_HPP
#define DATE_HPP
#include <cstdint>


class Date {
    uint8_t day;
    uint8_t month;
    uint16_t year;

public:
    void print() const;

    Date(uint16_t day, uint8_t month, uint16_t year);

    Date();
};


#endif  // DATE_HPP
