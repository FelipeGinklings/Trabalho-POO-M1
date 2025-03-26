//
// Created by Felipe Notebook on 25/03/2025.
//

#ifndef HOST_HPP
#define HOST_HPP
#include "User.hpp"


class Host : public User {
public:
    void update(const std::string &id, const std::string &locationType, uint16_t capacity, uint16_t price);
    Host(const std::string &name, const std::string &password, const std::string &email);
};

#endif  // HOST_HPP
