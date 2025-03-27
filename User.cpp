//
// Created by Felipe Notebook on 25/03/2025.
//

#include "User.hpp"

#include <iostream>

#include "RandomId.hpp"


std::string User::getId() const { return this->id; }

std::string User::getName() const { return this->name; }

std::string User::getEmail() const { return this->email; }

std::string User::getPassword() const { return this->password; }

SharedProperty User::getProperty(const std::string& idP) {
    for (const auto& property: this->vecOfProperties) {
        if (property->getId() == idP) {
            return property;
        }
    }
    std::cout << "Property with ID " << idP << " not found." << std::endl;
    return nullptr;
}

void User::add(const SharedProperty& property) { this->vecOfProperties.push_back(property); }

void User::remove(const std::string& idP) {
    std::erase_if(this->vecOfProperties, [&idP](const auto& ptr) { return ptr->getId() == idP; });
}

std::vector<SharedProperty> User::getProperties() const { return this->vecOfProperties; };

User::User(const std::string& name, const std::string& password, const std::string& email) {
    this->id = RandomId::generateRandomId();
    this->name = name;
    this->email = email;
    this->password = password;
}
