//
// Created by Felipe Notebook on 25/03/2025.
//

#include "Client.hpp"

void Client::rate(const std::string &id, const uint8_t rate) const {
    for (auto property: this->vecOfProperties) {
        if (property.getId() == id) {
            property.getStars().addStars(id, rate);
        }
    }
}

Client::Client(const std::string &name, const std::string &password, const std::string &email) :
    User(name, password, email) {}
