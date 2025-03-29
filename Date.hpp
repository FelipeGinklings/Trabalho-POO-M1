//
// Created by Felipe Notebook on 25/03/2025.
//

#ifndef DATE_HPP
#define DATE_HPP


class Date {
    int day;
    int month;
    int year;

public:
    void print() const;

    Date(int day, int month, int year);

    Date();
};


#endif  // DATE_HPP
