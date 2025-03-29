//
// Created by Felipe Notebook on 25/03/2025.
//

#ifndef PROPERTY_HPP
#define PROPERTY_HPP
#include <string>

#include "Address.hpp"
#include "RentedProperty.hpp"
#include "Stars.hpp"


class Property {
    std::string id;
    std::string ownerName;
    Address address;
    std::string locationType;
    int capacity;
    int price;
    Stars *stars;
    bool isRented;
    RentedProperty *rentedProperty;

public:
    [[nodiscard]] std::string getId() const;

    [[nodiscard]] std::string getOwnerName() const;

    [[nodiscard]] int getPrice() const;

    [[nodiscard]] bool getIsRented() const;

    void setIsRented(bool isRentedP);

    [[nodiscard]] Stars *getStars() const;

    Address &getAddress();

    [[nodiscard]] RentedProperty *getRentedProperty() const;

    void status() const;

    void updateProperty(const std::string &locationType, int capacity, int price);

    Property(Address address, const std::string &ownerName, const std::string &locationType, int capacity, int price);
};

inline bool operator<(const Property &propA, const Property &propB) { return propA.getId() < propB.getId(); }


#endif  // PROPERTY_HPP
