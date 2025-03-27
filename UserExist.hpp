//
// Created by Felipe Notebook on 25/03/2025.
//

#ifndef USEREXIST_HPP
#define USEREXIST_HPP
#include "Client.hpp"
#include "Host.hpp"


class UserExist {
    bool itExist;
    SharedClient client;
    SharedHost host;

public:
    [[nodiscard]] bool getItExist() const;

    void setItExist(bool itExist);

    [[nodiscard]] SharedClient getClient() const;

    void setClient(const SharedClient& client);

    [[nodiscard]] SharedHost getHost() const;

    void setHost(const SharedHost& host);

    UserExist();
};


#endif  // USEREXIST_HPP
