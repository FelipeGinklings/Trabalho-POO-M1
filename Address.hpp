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

    Address(const std::string& country, const std::string& state, const std::string& city);
};

inline bool operator==(Address addressA, Address addressB) {
    return addressA.getCountry() == addressB.getCountry() && addressA.getState() == addressB.getState() &&
           addressA.getCity() == addressB.getCity();
}


#endif  // ADDRESS_HPP
