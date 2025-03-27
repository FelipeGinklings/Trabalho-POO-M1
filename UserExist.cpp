//
// Created by Felipe Notebook on 25/03/2025.
//

#include "UserExist.hpp"

bool UserExist::getItExist() const { return itExist; }

void UserExist::setItExist(const bool itExist) { this->itExist = itExist; }

SharedClient UserExist::getClient() const { return client; }

void UserExist::setClient(const SharedClient& client) {
    this->client.reset();
    this->client = client;
}

SharedHost UserExist::getHost() const { return host; }

void UserExist::setHost(const SharedHost& host) {
    this->host.reset();
    this->host = host;
}

UserExist::UserExist() : client(new Client("", "", "")), host(new Host("", "", "")) { this->itExist = false; }
