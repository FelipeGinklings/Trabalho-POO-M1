//
// Created by Felipe Notebook on 25/03/2025.
//

#ifndef USEREXIST_HPP
#define USEREXIST_HPP
#include "Client.hpp"
#include "Host.hpp"


class UserExist {
    bool itExist;
    Client client;
    Host host;

public:
    [[nodiscard]] bool getItExist() const;

    void setItExist(bool itExist);

    Client getClient();

    void setClient(const Client& client);

    Host getHost();

    void setHost(const Host& host);

    UserExist();
};


#endif  // USEREXIST_HPP
