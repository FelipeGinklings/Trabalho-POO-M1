//
// Created by Felipe Notebook on 25/03/2025.
//

#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#include "Client.hpp"
#include "Host.hpp"
#include "UserExist.hpp"


class System {
    std::vector<SharedClient> vecOfClients;
    std::vector<SharedHost> vecOfHosts;
    std::vector<SharedProperty> listOfProperties;
    bool clientType;  // true for user false for host
    bool isLogged;
    std::string loggedUserId;
    Address addressFilter;
    uint16_t priceFilter;


    UserExist getUser();

    UserExist getUser(const std::string &email, const std::string &password);

    void createPropertiesList();

public:
    [[nodiscard]] bool hasFilters() const;

    [[nodiscard]] bool getClientType() const;

    [[nodiscard]] bool getIsLogged() const;

    std::vector<SharedProperty> showProperties();

    std::vector<SharedProperty> showProperties(const std::string &rented);

    std::vector<SharedProperty> showProperties(bool hostProperties);

    bool signin();

    void signup();

    void logout();

    void searchFilter(const std::string &filterChoice);

    void searchFilter();

    void rent(const SharedProperty &property);

    static void update(const SharedProperty &property, const std::string &option);

    void remove(const std::string &id);

    void rate(const SharedProperty &property) const;

    void newProperty();

    void interface(const std::string &option) const;

    [[nodiscard]] static std::string selector(const std::string &option);

    void addUser(const SharedHost &newHost);

    void addUser(const SharedClient &newClient);

    void addProperty(const SharedHost &user, const std::string &country, const std::string &state,
                     const std::string &city, const std::string &locationType, const uint16_t &capacity,
                     const uint16_t &price);

    System();
};


#endif  // SYSTEM_HPP
