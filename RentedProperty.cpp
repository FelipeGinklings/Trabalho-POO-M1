//
// Created by Felipe Notebook on 25/03/2025.
//

#include "RentedProperty.hpp"

#include <iostream>


void RentedProperty::hostStatus() const {
    std::cout << "Date: ";
    this->date.print();
    std::cout << "Host: " << this->hostName << std::endl;
}

void RentedProperty::clientStatus() const {
    std::cout << "Date: ";
    this->date.print();
    std::cout << "Client: " << this->clientName << std::endl;
}

void RentedProperty::setRented(const Date date, const std::string &clientName) {
    this->date = date;
    this->clientName = clientName;
}

RentedProperty::RentedProperty(const Date date, const std::string &hostName, const std::string &clientName) :
    date(date) {
    this->hostName = hostName;
    this->clientName = clientName;
}
RentedProperty::RentedProperty(const std::string &hostName) : date(Date()) {
    this->hostName = hostName;
    this->clientName = "";
}
