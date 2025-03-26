//
// Created by Felipe Notebook on 25/03/2025.
//

#include "User.hpp"

#include <stdexcept>

#include "RandomId.hpp"


std::string User::getId() const { return this->id; }

std::string User::getName() const { return this->name; }

std::string User::getEmail() const { return this->email; }

std::string User::getPassword() const { return this->password; }

Property User::getProperty(const std::string& idP) {
    for (auto& property: this->vecOfProperties) {
        if (property.getId() == idP) {
            return property;
        }
    }
    throw std::runtime_error("Property with ID " + idP + " not found.");
}

void User::add(const Property& property) { this->vecOfProperties.push_back(property); }

void User::remove(const std::string& idP) {
    std::erase_if(this->vecOfProperties, [idP](const Property& property) { return property.getId() == idP; });
}

std::vector<Property> User::getProperties() const { return this->vecOfProperties; };

User::User(const std::string& name, const std::string& password, const std::string& email) {
    this->id = RandomId::generateRandomId();
    this->name = name;
    this->email = email;
    this->password = password;
}
