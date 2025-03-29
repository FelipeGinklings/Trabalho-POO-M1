//
// Criado por Felipe Notebook em 25/03/2025.
//

#include "System.hpp"

#include <cstdlib>
#include <iostream>

/**
 * Recupera o usuário atualmente logado no sistema com base no tipo de usuário (cliente ou anfitrião).
 *
 * @return Um objeto UserExist, contendo as informações do usuário encontrado.
 */
UserExist System::getUser() {
    auto tempUser = UserExist();
    if (this->clientType) {
        for (const auto& client: this->vecOfClients) {
            if (client->getId() == this->loggedUserId) {
                tempUser.setItExist(true);
                tempUser.setClient(client);
                break;
            }
        }
        return tempUser;
    }
    for (const auto& host: this->vecOfHosts) {
        if (host->getId() == this->loggedUserId) {
            tempUser.setItExist(true);
            tempUser.setHost(host);
            break;
        }
    }
    return tempUser;
}

/**
 * Recupera um usuário com base no email e na senha fornecidos.
 *
 * @param email O email do usuário.
 * @param password A senha do usuário.
 * @return Um objeto UserExist, contendo as informações do usuário encontrado.
 */
UserExist System::getUser(const std::string& email, const std::string& password) {
    auto tempUser = UserExist();
    for (const auto& client: this->vecOfClients) {
        if (client->getEmail() == email && client->getPassword() == password) {
            tempUser.setItExist(true);
            tempUser.setClient(client);
        }
    }
    if (!tempUser.getItExist()) {
        for (const auto& host: this->vecOfHosts) {
            if (host->getEmail() == email && host->getPassword() == password) {
                tempUser.setItExist(true);
                tempUser.setHost(host);
                break;
            }
        }
    }
    return tempUser;
}

/**
 * Cria uma lista consolidada de todas as propriedades de todos os anfitriões presentes no sistema.
 */
void System::createPropertiesList() {
    for (const auto& host: this->vecOfHosts) {
        std::vector<SharedProperty> localProperties = host->getProperties();
        this->listOfProperties.insert(this->listOfProperties.end(), localProperties.begin(), localProperties.end());
    }
}

/**
 * Verifica se há filtros aplicados para a pesquisa de propriedades.
 *
 * @return true se filtros estiverem ativos, false caso contrário.
 */
bool System::hasFilters() const { return addressFilter != Address("", "", "") || priceFilter != 0; }

/**
 * Retorna o tipo de usuário logado (cliente ou anfitrião).
 *
 * @return true se for cliente, false se for anfitrião.
 */
bool System::getClientType() const { return this->clientType; }

/**
 * Verifica se há um usuário logado no sistema.
 *
 * @return true se estiver logado, false caso contrário.
 */
bool System::getIsLogged() const { return this->isLogged; }

/**
 * Mostra as propriedades disponíveis no sistema, aplicando os filtros de preço e localização, se configurados.
 *
 * @return Uma lista de propriedades que atendem aos filtros aplicados.
 */
std::vector<SharedProperty> System::showProperties() {
    int i = 1;
    std::vector<SharedProperty> properties;
    bool noPriceFilter = false;
    bool noLocationFilter = false;
    if (this->priceFilter == 0) noPriceFilter = true;
    if (this->addressFilter == Address("", "", "")) noLocationFilter = true;
    for (auto& allProperty: this->listOfProperties) {
        // filtros de localização
        const bool sameCountry = this->addressFilter.getCountry() == allProperty->getAddress().getCountry();
        const bool sameState = this->addressFilter.getState() == allProperty->getAddress().getState();
        const bool sameCity = this->addressFilter.getCity() == allProperty->getAddress().getCity();

        const bool isNotRented = !allProperty->getIsRented();

        bool withPriceFilter = this->priceFilter >= allProperty->getPrice();
        bool withLocationsFilters = sameCountry || sameState || sameCity;
        if (noPriceFilter) withPriceFilter = true;
        if (noLocationFilter) withLocationsFilters = true;

        if (isNotRented && (withPriceFilter && withLocationsFilters)) {
            std::cout << " ~~ Propriedade numero " << i << " ~~ " << std::endl;
            allProperty->status();
            properties.push_back(allProperty);
            std::cout << std::endl;
            i++;
        }
    }
    return properties;
}

/**
 * Mostra as propriedades, baseando-se no status (alugada ou não) e no tipo de usuário logado.
 *
 * @param rented Um indicador para focar em propriedades alugadas ("rented").
 * @return Uma lista das propriedades relevantes.
 */
std::vector<SharedProperty> System::showProperties(const std::string& rented) {
    auto userExist = getUser();
    int i = 1;
    std::vector<SharedProperty> properties;
    if (this->clientType && rented == "rented") {
        for (auto& clientProperty: userExist.getClient()->getProperties()) {
            std::cout << " ~~ Propriedade numero " << i << " ~~ " << std::endl;
            std::cout << "Address: " << clientProperty->getAddress() << std::endl;
            clientProperty->getRentedProperty()->hostStatus();
            properties.push_back(clientProperty);
            std::cout << std::endl;
            i++;
        }
        userExist.setClient(nullptr);
        return properties;
    }
    for (auto& hostProperty: userExist.getHost()->getProperties()) {
        std::cout << " ~~ Propriedade numero " << i << " ~~ " << std::endl;
        if (hostProperty->getIsRented()) {
            hostProperty->getRentedProperty()->clientStatus();
            properties.push_back(hostProperty);
            std::cout << std::endl;
            i++;
        } else {
            hostProperty->status();
            properties.push_back(hostProperty);
            std::cout << std::endl;
            i++;
        }
    }
    userExist.setHost(nullptr);
    return properties;
}

/**
 * Realiza o login de um usuário no sistema com base no email e na senha fornecidos.
 *
 * @return true se o login for bem-sucedido, false caso contrário.
 */
bool System::signin() {
    std::string email, password;
    std::cout << " ~~ Login ~~" << std::endl;
    std::cout << "Email: ";
    std::cin >> email;
    std::cout << "Senha: ";
    std::cin >> password;
    const UserExist user = getUser(email, password);

    if (!user.getItExist()) {
        std::cout << "Usuario nao encontrado!" << std::endl;
        return false;
    }

    if (user.getClient()->getEmail() == email && user.getClient()->getPassword() == password) {
        this->clientType = true;
        this->loggedUserId = user.getClient()->getId();
    } else {
        this->clientType = false;
        this->loggedUserId = user.getHost()->getId();
    }

    this->isLogged = true;
    std::cout << "Logado com sucesso" << std::endl;

    return true;
}

/**
 * Cadastra um novo usuário no sistema (cliente ou anfitrião) e realiza o login automaticamente.
 */
void System::signup() {
    std::string name, email, password;
    int type;
    std::cout << " ~~ Criar conta ~~" << std::endl;
    std::cout << "Name: ";
    std::cin >> name;
    std::cout << "Email: ";
    std::cin >> email;
    std::cout << "Senha: ";
    std::cin >> password;
    std::cout << "Host(0)\tClient(1): ";
    std::cin >> type;

    if (type == 0) {
        auto newHost = std::make_shared<Host>(name, password, email);
        this->vecOfHosts.push_back(newHost);
        this->loggedUserId = newHost->getId();
        newHost.reset();
        this->clientType = false;
    } else {
        auto newClient = std::make_shared<Client>(name, password, email);
        this->vecOfClients.push_back(newClient);
        this->loggedUserId = newClient->getId();
        newClient.reset();
        this->clientType = true;
    }

    this->isLogged = true;
    std::cout << "Usuario cadastrado e logado com sucesso!" << std::endl;
}

/**
 * Realiza o logout do usuário atual e redefine os filtros aplicados.
 */
void System::logout() {
    std::cout << " ~~ Logout ~~" << std::endl;
    this->isLogged = false;
    this->loggedUserId = "";
    this->addressFilter = Address("", "", "");
    this->priceFilter = 0;
    std::cout << "Deslogado com sucesso!" << std::endl << std::endl;
}
/**
 * Aplica filtros de pesquisa com base na escolha do usuário.
 *
 * @param filterChoice A escolha do filtro (ex.: "f1" para valor, "f2" para país, "f3" para estado, "f4" para cidade).
 */
void System::searchFilter(const std::string& filterChoice) {
    if (filterChoice == "f1") {
        std::cout << "Digite o valor maximo para filtrar: ";
        std::cin >> this->priceFilter;
    } else if (filterChoice == "f2") {
        std::string country;
        std::cout << "Digite o nome do Pais para filtrar: ";
        std::cin >> country;
        this->addressFilter.setCountry(country);
    } else if (filterChoice == "f3") {
        std::string state;
        std::cout << "Digite o nome do Estado para filtrar: ";
        std::cin >> state;
        this->addressFilter.setState(state);
    } else if (filterChoice == "f4") {
        std::string city;
        std::cout << "Digite o nome da Cidade para filtrar: ";
        std::cin >> city;
        this->addressFilter.setCity(city);
    }
}

/**
 * Remove todos os filtros de pesquisa configurados no sistema.
 */
void System::searchFilter() {
    this->addressFilter.setCountry("");
    this->addressFilter.setState("");
    this->addressFilter.setCity("");
    this->priceFilter = 0;
}

/**
 * Realiza o aluguel de uma propriedade para o cliente logado.
 *
 * @param property A propriedade que será alugada.
 */
void System::rent(const SharedProperty& property) {
    auto userExist = getUser();
    const auto user = userExist.getClient();
    std::cout << " ~~ Alugando Propriedade ~~ " << std::endl;
    std::cout << " ~~ Insira a Data ~~ " << std::endl;

    std::cout << "Dia: ";
    int day;
    std::cin >> day;

    std::cout << "Mes: ";
    int month;
    std::cin >> month;

    std::cout << "Ano: ";
    int year;
    std::cin >> year;

    property->setIsRented(true);
    user->add(property);
    property->getRentedProperty()->setRented(Date(day, month, year), user->getName());
    userExist.setClient(nullptr);
}

/**
 * Atualiza as informações de uma propriedade com base em uma opção selecionada.
 *
 * @param property A propriedade a ser atualizada.
 * @param option A opção de atualização: "1" para localização, "2" para capacidade, "3" para preço, "4" para sair.
 */
void System::update(const SharedProperty& property, const std::string& option) {
    std::string locationType;
    int capacity = 0;
    int price = 0;
    std::cout << " ~~ Atualizar Propriedade ~~ " << std::endl;
    if (option == "1") {
        std::cout << "Digite o novo tipo de localizacao (ou pressione Enter para manter o atual): ";
        std::getline(std::cin >> std::ws, locationType);
    } else if (option == "2") {
        std::cout << "Digite a nova capacidade (ou 0 para manter o atual): ";
        std::cin >> capacity;
    } else if (option == "3") {
        std::cout << "Digite o novo preco (ou 0 para manter o atual): ";
        std::cin >> price;
    } else if (option == "4") {
        return;
    }

    if (!locationType.empty() || capacity > 0 || price > 0) {
        property->updateProperty(locationType, capacity, price);
    } else {
        std::cout << "Nenhuma alteracao feita." << std::endl;
    }
}

/**
 * Remove uma propriedade do sistema com base em seu ID.
 *
 * @param id O identificador da propriedade a ser removida.
 */
void System::remove(const std::string& id) {
    auto userExist = getUser();
    if (this->clientType) {
        userExist.getClient()->remove(id);
        userExist.setClient(nullptr);
    } else {
        userExist.getHost()->remove(id);
        this->listOfProperties.clear();
        createPropertiesList();
        userExist.setHost(nullptr);
    }
    std::cout << " ~~ Removendo Propriedade ~~ " << std::endl;
    std::cout << " ~~ Propriedade removida com sucesso ~~ " << std::endl;
}

/**
 * Avalia uma propriedade com uma nota entre 1 e 5.
 *
 * @param property A propriedade a ser avaliada.
 */
void System::rate(const SharedProperty& property) const {
    std::cout << " ~~ Avaliar Propriedade ~~ " << std::endl;
    std::cout << "Digite a nota (1-5): ";
    int stars;
    std::cin >> stars;
    property->getStars()->addStars(this->loggedUserId, stars);
}

/**
 * Adiciona uma nova propriedade ao sistema.
 */
void System::newProperty() {
    auto userExist = getUser();
    const auto user = userExist.getHost();
    std::cout << " ~~ Adicionar Nova Propriedade ~~ " << std::endl;
    // Obter detalhes da propriedade fornecidos pelo usuário
    std::cout << " ~~ Digite o endereco (insira os detalhes do pais, estado, cidade) ~~ " << std::endl;
    std::string country, state, city;
    std::cout << "Pais: ";
    std::getline(std::cin >> std::ws, country);
    std::cout << "Estado: ";
    std::getline(std::cin >> std::ws, state);
    std::cout << "Cidade: ";
    std::getline(std::cin >> std::ws, city);

    Address propertyAddress(country, state, city);
    std::cout << "Digite o tipo de localizacao: ";
    std::string locationType;
    std::getline(std::cin >> std::ws, locationType);

    std::cout << "Digite a capacidade do imovel: ";
    int capacity;
    std::cin >> capacity;

    std::cout << "Digite o preco do imovel: ";
    int price;
    std::cin >> price;

    // Criar a nova propriedade
    auto newProperty = std::make_shared<Property>(propertyAddress, user->getName(), locationType, capacity, price);
    // Adicionar a propriedade à lista do usuário e à lista do sistema
    user->add(newProperty);
    this->listOfProperties.push_back(newProperty);
    newProperty.reset();
    userExist.setHost(nullptr);
}

/**
 * Exibe os menus da interface do sistema com base no estado atual.
 *
 * @param option A opção que determina qual menu exibir: "notLogged", "logged", "filters", "manage".
 */
void System::interface(const std::string& option) const {
    if (option == "notLogged") {  // Não Logado
        std::cout << " ~~ Nao Logado ~~ " << std::endl;
        std::cout << "1. Sign In" << std::endl;
        std::cout << "2. Sign Up" << std::endl;
        std::cout << "Sair(s)" << std::endl;
    } else if (option == "logged") {
        if (this->clientType) {
            std::cout << " ~~ Client Logado ~~ " << std::endl;
            std::cout << "1. Pesquisa" << std::endl;
            std::cout << "2. Mostra propriedades alugadas" << std::endl;
            std::cout << "3. Logout" << std::endl;
            std::cout << "Sair(s)" << std::endl;
        } else {
            std::cout << " ~~ Anfitriao Logado ~~ " << std::endl;
            std::cout << "1. Minhas propriedades" << std::endl;
            std::cout << "2. Mostrar propriedades alugadas" << std::endl;
            std::cout << "3. Adicionar propriedade " << std::endl;
            std::cout << "4. Logout" << std::endl;
            std::cout << "Sair(s)" << std::endl;
        }
    } else if (option == "filters") {
        std::cout << " ~~ Filtros ~~ " << std::endl;
        std::cout << "1. Filtrar por valor" << std::endl;
        std::cout << "2. Filtrar por pais" << std::endl;
        std::cout << "3. Filtrar por estado" << std::endl;
        std::cout << "4. Filtrar por cidade" << std::endl;
        std::cout << "5. Remover filtros" << std::endl;
        std::cout << "Voltar(v)" << std::endl;
    } else if (option == "manage") {
        std::cout << " ~~ Editar ~~ " << std::endl;
        std::cout << "1. Editar Tipo de Localizacao " << std::endl;
        std::cout << "2. Editar Capacidade" << std::endl;
        std::cout << "3. Editar Preco" << std::endl;
        std::cout << "Voltar(v)" << std::endl;
    }
    std::cout << std::endl;
}

/**
 * Exibe um menu de seleção com base na funcionalidade requisitada.
 *
 * @param option Determina qual menu de seleção exibir: "searchClient", "select", "selectedProperty", etc.
 * @return A escolha feita pelo usuário no menu.
 */
std::string System::selector(const std::string& option = "options") {
    if (option == "searchClient") {  // Seletor com filtro
        std::cout << "Filtrar(f)\tSelecionar(numero)\tVoltar(v)" << std::endl;
    } else if (option == "select") {  // Seletor sem filtro
        std::cout << "Selecionar(numero)\tVoltar(v)" << std::endl;
    } else if (option == "selectedProperty") {  // Propriedade selecionada
        std::cout << "Alugar(a)\tVoltar(v)" << std::endl;
    } else if (option == "manageProperty") {  // Gerenciar propriedade
        std::cout << "Editar(e)\tDeletar(d)\tVoltar(v)" << std::endl;
    } else if (option == "selectedRent") {  // Escolha para avaliar propriedade
        std::cout << "Avaliar(a)\tCancelar(c)\tVoltar(v)" << std::endl;
    } else if (option == "back") {
        std::cout << "Voltar(v)\t" << std::endl;
    } else if (option == "confirm") {  // Menu de confirmação
        std::cout << "Confirmar(s)\tCancelar(n)" << std::endl;
    } else {
        std::cout << "Escolha: " << std::endl;
    }
    std::string choice;
    std::cin >> choice;
    std::cout << std::endl;
    return choice;
}

/**
 * Adiciona um novo anfitrião à lista de anfitriões do sistema.
 *
 * @param newHost Um objeto representando o anfitrião a ser adicionado.
 */
void System::addUser(const SharedHost& newHost) { this->vecOfHosts.push_back(newHost); }

/**
 * Adiciona um novo cliente à lista de clientes do sistema.
 *
 * @param newClient Um objeto representando o cliente a ser adicionado.
 */
void System::addUser(const SharedClient& newClient) { this->vecOfClients.push_back(newClient); }

/**
 * Adiciona uma nova propriedade ao sistema, vinculada a um anfitrião específico.
 *
 * @param user O anfitrião responsável pela propriedade.
 * @param country O país da propriedade.
 * @param state O estado da propriedade.
 * @param city A cidade da propriedade.
 * @param locationType O tipo de localização da propriedade.
 * @param capacity A capacidade da propriedade.
 * @param price O preço da propriedade.
 */
void System::addProperty(const SharedHost& user, const std::string& country, const std::string& state,
                         const std::string& city, const std::string& locationType, const int& capacity,
                         const int& price) {
    auto newProperty =
        std::make_shared<Property>(Address(country, state, city), user->getName(), locationType, capacity, price);
    user->add(newProperty);
    this->listOfProperties.push_back(newProperty);
    newProperty.reset();
}

/**
 * Construtor da classe System. Inicializa variáveis padrão do sistema.
 */
System::System() : addressFilter(Address("", "", "")) {
    clientType = true;  // true para cliente, false para anfitrião
    isLogged = false;
    loggedUserId = "";
    priceFilter = 0;
    createPropertiesList();
}
