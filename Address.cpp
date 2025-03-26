//
// Created by Felipe Notebook on 25/03/2025.
//

#include "Address.hpp"

#include <string>
#include <iostream>

std::string Address::getCountry() { return this->country; }

std::string Address::getState() { return this->state; }

std::string Address::getCity() { return this->city; }

void Address::setCountry(const std::string& countryNew) { this->country = countryNew; };

void Address::setState(const std::string& stateNew) { this->state = stateNew; };

void Address::setCity(const std::string& cityNew) { this->city = cityNew; };

Address::Address(const std::string& country, const std::string& state, const std::string& city) {
    this->country = country;
    this->state = state;
    this->city = city;
}

std::ostream& operator<<(std::ostream& os, const Address& address) {
    os << "Country: " << address.country << " - State: " << address.state << " - City: " << address.city;
    return os;
}