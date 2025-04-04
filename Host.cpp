//
// Created by Felipe Notebook on 25/03/2025.
//

#include "Host.hpp"

void Host::update(const std::string &id, const std::string &locationType, const int capacity,
                  const int price) {
    for (const auto &property: this->vecOfProperties) {
        if (property->getId() == id) {
            property->updateProperty(locationType, capacity, price);
            return;
        }
    }
}

Host::Host(const std::string &name, const std::string &password, const std::string &email) :
    User(name, password, email) {}
