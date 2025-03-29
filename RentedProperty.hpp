//
// Created by Felipe Notebook on 25/03/2025.
//

#ifndef RENTEDPROPERTY_HPP
#define RENTEDPROPERTY_HPP
#include <string>

#include "Date.hpp"


class RentedProperty {
    Date date;
    std::string hostName;
    std::string clientName;

public:
    void clientStatus() const;

    void setRented(Date date, const std::string &clientName);

    void hostStatus() const;

    RentedProperty(Date date, const std::string &hostName, const std::string &clientName);

    explicit RentedProperty(const std::string &hostName);
};


#endif  // RENTEDPROPERTY_HPP
