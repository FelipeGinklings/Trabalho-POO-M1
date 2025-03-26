//
// Created by Felipe Notebook on 25/03/2025.
//

#ifndef USER_HPP
#define USER_HPP
#include <string>
#include <vector>

#include "Property.hpp"

class User {
protected:
    std::string id;
    std::string name;
    std::string email;
    std::string password;
    std::vector<Property> vecOfProperties;

public:
    [[nodiscard]] std::string getId() const;

    [[nodiscard]] std::string getName() const;

    [[nodiscard]] std::string getEmail() const;

    [[nodiscard]] std::string getPassword() const;

    [[nodiscard]] std::vector<Property> getProperties() const;

    Property getProperty(const std::string &idP);

    void add(const Property &property);

    void remove(const std::string &idP);

    User(const std::string &name, const std::string &password, const std::string &email);

};


#endif  // USER_HPP
