//
// Created by Felipe Notebook on 25/03/2025.
//

#ifndef HOST_HPP
#define HOST_HPP
#include "User.hpp"


class Host : public User {
public:
    void update(const std::string &id, const std::string &locationType, int capacity, int price);
    Host(const std::string &name, const std::string &password, const std::string &email);
};

using SharedHost = std::shared_ptr<Host>;

#endif  // HOST_HPP
