//
// Created by Felipe Notebook on 25/03/2025.
//

#include "Property.hpp"

#include <iostream>
#include <utility>

#include "RandomId.hpp"

std::string Property::getId() const { return this->id; }

std::string Property::getOwnerName() const { return this->ownerName; }

uint16_t Property::getPrice() const { return this->price; }

bool Property::getIsRented() const { return this->isRented; }

void Property::setIsRented(const bool isRentedP) { this->isRented = isRentedP; }

Stars Property::getStars() { return this->stars; };

Address &Property::getAddress() { return this->address; }

RentedProperty Property::getRentedProperty() { return this->rentedProperty; }


void Property::status() const {
    std::cout << "Stars: " << this->stars.getStars() << std::endl;
    std::cout << "Number of avaliations: " << this->stars.amountOfAvaliations() << std::endl;
    std::cout << "Address: " << this->address << std::endl;
    std::cout << "Owner Name: " << this->ownerName << std::endl;
    std::cout << "Location Type: " << this->locationType << std::endl;
    std::cout << "Capacity: " << static_cast<int>(this->capacity) << std::endl;
    std::cout << "Price: " << static_cast<int>(this->price) << std::endl;
}
void Property::updateProperty(const std::string &locationType = "", const uint16_t capacity = 0,
                              const uint16_t price = 0) {
    if (!locationType.empty()) this->locationType = locationType;
    if (capacity > 0) this->capacity = capacity;
    if (price > 0) this->price = price;
}

Property::Property(Address address, const std::string &ownerName, const std::string &locationType,
                   const uint16_t capacity, const uint16_t price) :
    address(std::move(address)), rentedProperty(RentedProperty(ownerName)) {
    this->id = RandomId::generateRandomId();
    this->ownerName = ownerName;
    this->locationType = locationType, this->capacity = capacity;
    this->price = price;
    this->isRented = false;
    this->stars = Stars();
}
