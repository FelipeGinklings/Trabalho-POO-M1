//
// Created by Felipe Notebook on 25/03/2025.
//

#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#include "Client.hpp"
#include "Host.hpp"
#include "UserExist.hpp"


class System {
    static std::vector<Client> vecOfClients;
    static std::vector<Host> vecOfHosts;
    static std::vector<Property> listOfProperties;
    static bool clientType;  // true for user false for host
    static bool isLogged;
    static std::string loggedUserId;
    static Address addressFilter;
    static uint16_t priceFilter;


    static UserExist getUser();

    static UserExist getUser(const std::string &email, const std::string &password);

    static void createPropertiesList();

public:
    [[nodiscard]] static Address getAddressFilter();

    [[nodiscard]] static uint16_t getPriceFilter();

    [[nodiscard]] static bool getClientType();

    [[nodiscard]] static bool getIsLogged();

    static std::vector<Property> showProperties();

    static std::vector<Property> showProperties(const std::string &rented);

    static std::vector<Property> showProperties(bool hostProperties);

    static bool signin();

    static void signup();

    static void logout();

    static void searchFilter(const std::string &filterChoice);

    static void searchFilter();

    static void rent(Property &property);

    static void update(Property &property, const std::string &option);

    static void remove();

    static void rate(Property &property);

    static void newProperty();

    static void interface(const std::string &option);

    [[nodiscard]] static std::string selector(const std::string &option);

    System();
};


#endif  // SYSTEM_HPP
