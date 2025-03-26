//
// Created by Felipe Notebook on 25/03/2025.
//

#include "UserExist.hpp"

#include <utility>


bool UserExist::getItExist() const { return itExist; }

void UserExist::setItExist(const bool itExist) { this->itExist = itExist; }

Client UserExist::getClient() { return client; }

void UserExist::setClient(const Client& client) { this->client = client; }

Host UserExist::getHost() { return host; }

void UserExist::setHost(const Host& host) { this->host = host; }

UserExist::UserExist() : client(Client("", "", "")), host(Host("", "", "")) { this->itExist = false; }
