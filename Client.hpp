//
// Created by Felipe Notebook on 25/03/2025.
//

#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <string>

#include "User.hpp"


class Client : public User {
public:
    void rate(const std::string &id, int rate) const;

    Client(const std::string &name, const std::string &password, const std::string &email);
};

using SharedClient = std::shared_ptr<Client>;

#endif  // CLIENT_HPP
