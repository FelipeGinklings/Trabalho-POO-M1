//
// Created by Felipe Notebook on 25/03/2025.
//

#ifndef ADDRESS_HPP
#define ADDRESS_HPP
#include <string>


class Address {
    std::string country;
    std::string state;
    std::string city;

public:
    std::string getCountry();

    std::string getState();

    std::string getCity();

    void setCountry(const std::string& countryNew);

    void setState(const std::string& stateNew);

    void setCity(const std::string& cityNew);

    friend std::ostream& operator<<(std::ostream& os, const Address& address);

    friend bool operator==(Address addressA, Address addressB);

    Address(const std::string& country, const std::string& state, const std::string& city);
};


#endif  // ADDRESS_HPP
