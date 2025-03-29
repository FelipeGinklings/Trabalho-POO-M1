//
// Created by Felipe Notebook on 25/03/2025.
//

#ifndef USER_HPP
#define USER_HPP
#include <memory>
#include <string>
#include <vector>

#include "Property.hpp"

using SharedProperty = std::shared_ptr<Property>;

class User {
protected:
    std::string id;
    std::string name;
    std::string email;
    std::string password;
    std::vector<SharedProperty> vecOfProperties;

    [[nodiscard]] std::string getId() const;

    [[nodiscard]] std::string getEmail() const;

    [[nodiscard]] std::string getPassword() const;

public:
    [[nodiscard]] std::string getName() const;

    [[nodiscard]] std::vector<SharedProperty> getProperties() const;

    std::shared_ptr<Property> getProperty(const std::string &idP);

    void add(const SharedProperty &property);

    void remove(const std::string &idP);

    User(const std::string &name, const std::string &password, const std::string &email);

    friend class System;
};


#endif  // USER_HPP
