//
// Created by Felipe Notebook on 25/03/2025.
//

#include "Client.hpp"

void Client::rate(const std::string &id, const int rate) const {
    for (const auto &property: this->vecOfProperties) {
        if (property->getId() == id) {
            property->getStars()->addStars(id, rate);
            return;
        }
    }
}

Client::Client(const std::string &name, const std::string &password, const std::string &email) :
    User(name, password, email) {}
