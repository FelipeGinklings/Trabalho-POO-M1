//
// Created by Felipe Notebook on 25/03/2025.
//

#ifndef PROPERTY_HPP
#define PROPERTY_HPP
#include <cstdint>
#include <string>

#include "Address.hpp"
#include "RentedProperty.hpp"
#include "Stars.hpp"


class Property {
    std::string id;
    std::string ownerName;
    Address address;
    std::string locationType;
    uint16_t capacity;
    uint16_t price;
    Stars stars;
    bool isRented;
    RentedProperty rentedProperty;

public:
    [[nodiscard]] std::string getId() const;

    [[nodiscard]] std::string getOwnerName() const;

    [[nodiscard]] uint16_t getPrice() const;

    [[nodiscard]] bool getIsRented() const;

    void setIsRented(bool isRentedP);

    Stars getStars();

    Address &getAddress();

    RentedProperty getRentedProperty();

    void status() const;

    void updateProperty(const std::string &locationType, uint16_t capacity, uint16_t price);

    Property(Address address, const std::string &ownerName, const std::string &locationType, uint16_t capacity,
             uint16_t price);
};

inline bool operator<(const Property &propA, const Property &propB) { return propA.getId() < propB.getId(); }


#endif  // PROPERTY_HPP
