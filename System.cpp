//
// Created by Felipe Notebook on 25/03/2025.
//

#include "System.hpp"

#include <cstdlib>
#include <iostream>
// Internal class functions

/**
 * Retrieves the currently logged-in user's information, whether they are a client or host.
 * The method checks the list of clients or hosts based on the `clientType` and matches
 * against the `loggedUserId`. If the user is found, the corresponding client or host
 * information is stored in a `UserExist` object. If no match is found, the `UserExist`
 * object will indicate the user's non-existence.
 *
 * @return A `UserExist` object containing details about the logged-in user,
 *         including whether they exist, and their corresponding client or host data.
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
 * Retrieves a UserExist object based on the provided email and password.
 * Searches through the list of clients or hosts depending on the user type
 * and checks if the given email and password match an existing user.
 * If a match is found, updates the UserExist object to indicate the user's existence.
 *
 * @param email The email of the user to search for.
 * @param password The password of the user to validate.
 * @return A UserExist object representing whether the user exists
 *         and includes the matched client or host details if found.
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
 * @brief Populates the listOfProperties vector with Property objects from all hosts.
 *
 * This method iterates through the vector of Host objects (vecOfHosts), retrieves
 * their associated properties using the Host:->getProperties method, and appends them
 * to the global static vector this->listOfProperties.
 *
 * @note This method assumes that vecOfHosts contains valid Host objects, each having
 * a non-empty vector of properties when applicable. It clears no existing elements in
 * listOfProperties prior to insertion.
 */
void System::createPropertiesList() {
    for (const auto& host: this->vecOfHosts) {
        std::vector<SharedProperty> localProperties = host->getProperties();
        this->listOfProperties.insert(this->listOfProperties.end(), localProperties.begin(), localProperties.end());
    }
}
bool System::hasFilters() const { return addressFilter != Address("", "", "") || priceFilter != 0; }

bool System::getClientType() const { return this->clientType; }

bool System::getIsLogged() const { return this->isLogged; }

/**
 * Filters and retrieves a list of properties based on specified criteria, including
 * location and price filters. The method iterates through all available properties,
 * applying the filters to determine which properties meet the conditions. Properties
 * that match the criteria are displayed and returned as a collection.
 *
 * @return A vector of `Property` objects that satisfy the filtering criteria, including
 *         properties that are not rented and fall within the specified location and
 *         price range.
 */
std::vector<SharedProperty> System::showProperties() {
    int i = 1;
    std::vector<SharedProperty> properties;
    bool noPriceFilter = false;
    bool noLocationFilter = false;
    if (this->priceFilter == 0) noPriceFilter = true;
    if (this->addressFilter == Address("", "", "")) noLocationFilter = true;
    for (auto& allProperty: this->listOfProperties) {
        // locations filters
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
 * Displays the properties owned by the logged-in user and returns them as a vector.
 * The method identifies whether the logged-in user is a client or a host using the `clientType` flag.
 *
 * If the user is a client, it retrieves their list of properties, displays the property details
 * (address and rental status), and adds them to the result vector.
 *
 * If the user is a host, it filters their list of properties to include only the ones currently rented,
 * displays the rental status for those properties, and adds them to the result vector.
 *
 * The rental status is fetched using the `RentedProperty::clientStatus()` method. The address and other
 * property-specific details are printed during the process.
 *
 * @param rented An optional string parameter, which is currently not used in the logic of the function.
 * @return A vector of `Property` objects representing the user's relevant properties.
 */
std::vector<SharedProperty> System::showProperties([[maybe_unused]] const std::string& rented = "rented") {
    int i = 1;
    std::vector<SharedProperty> properties;
    if (this->clientType) {
        for (auto& clientProperty: getUser().getClient()->getProperties()) {
            std::cout << " ~~ Propriedade numero " << i << " ~~ " << std::endl;
            std::cout << "Address: " << clientProperty->getAddress() << std::endl;
            clientProperty->getRentedProperty().clientStatus();
            properties.push_back(clientProperty);
            std::cout << std::endl;
            i++;
        }
        return properties;
    }
    for (auto& hostProperty: getUser().getHost()->getProperties()) {
        if (hostProperty->getIsRented()) {
            std::cout << " ~~ Propriedade numero " << i << " ~~ " << std::endl;
            hostProperty->getRentedProperty().clientStatus();
            properties.push_back(hostProperty);
            std::cout << std::endl;
            i++;
        }
    }
    return properties;
}

/**
 * Displays a list of properties associated with the currently logged-in user
 * and optionally filters them based on the `hostProperties` parameter.
 *
 * Iterates through the logged-in host user's properties and displays their
 * details, including their status. Each property is added to a returned list
 * of properties. The function outputs information about the properties
 * to the console as part of the process.
 *
 * @param hostProperties A boolean parameter that specifies whether to display
 *                        properties associated with hosts. This parameter is
 *                        currently unused in the implementation.
 * @return A `std::vector` of `Property` objects representing the properties
 *         associated with the currently logged-in host.
 */
std::vector<SharedProperty> System::showProperties([[maybe_unused]] bool hostProperties) {
    int i = 1;
    std::vector<SharedProperty> properties;
    for (const auto& hostProperty: getUser().getHost()->getProperties()) {
        if (!hostProperty->getIsRented()) {
            std::cout << " ~~ Propriedade numero " << i << " ~~ " << std::endl;
            hostProperty->status();
            properties.push_back(hostProperty);
            std::cout << std::endl;
            i++;
        }
    }
    return properties;
}


/**
 * Allows a user to sign in to the system by providing an email and password.
 * Determines whether the user is a client or a host based on the provided credentials
 * and sets the appropriate flags and user ID if the authentication is successful.
 * If the entered email and password do not match any records, access is denied.
 *
 * @return true if the sign-in operation is successful, false otherwise.
 */
bool System::signin() {
    std::string password, email;
    std::cout << " ~~ Signin ~~" << std::endl;
    std::cout << "Email: ";
    std::cin >> email;
    std::cout << "Password: ";
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
 * @brief Handles the user signup process for the system.
 *
 * This method allows a user to register as either a Host or a Client.
 * The user inputs their name, email, and password, and selects their role (Host or Client).
 * Depending on the role selected, a new Host or Client object is created,
 * added to the respective list, and the user's ID is set as the logged-in user.
 *
 * Upon successful registration, the user is automatically logged in, and a confirmation
 * message is displayed. The system then clears the console for a fresh interface.
 *
 * @note This method performs input prompts through the standard input/output stream
 * and temporarily pauses the system for confirmation.
 */
void System::signup() {
    std::string name, email, password;
    int type;
    std::cout << " ~~ Signup ~~" << std::endl;
    std::cout << "Name: ";
    std::cin >> name;
    std::cout << "Email: ";
    std::cin >> email;
    std::cout << "Password: ";
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
 * @brief Logs the currently logged-in user out of the system.
 *
 * This method performs the following actions:
 * - Displays a logout message to the user.
 * - Sets the isLogged flag too false to indicate the user is no longer logged in.
 * - Clears the loggedUserId variable.
 * - Displays a success message to the user.
 * - Pauses the execution momentarily.
 * - Clears the terminal screen.
 *
 * No parameters are required, and the method does not return any value.
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
 * Filters addresses based on the provided filterChoice value.
 * Prompts the user to input a price, country, state, or city depending on the value of the position parameter.
 *
 * @param filterChoice The filter criteria position:
 *                 - 'f1' for filtering by price
 *                 - 'f2' for filtering by country
 *                 - 'f3' for filtering by state
 *                 - 'f4' for filtering by city
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
 * @brief Resets the search filter by clearing the address fields and setting the filter value to zero.
 *
 * This method clears the country, state, and city fields of the `newAddress` object,
 * effectively resetting the address filters to empty values. Additionally, it sets
 * the `priceFilter` to zero, indicating there is no specific price filter applied.
 */
void System::searchFilter() {
    this->addressFilter.setCountry("");
    this->addressFilter.setState("");
    this->addressFilter.setCity("");
    this->priceFilter = 0;
}

/**
 * Handles the process of renting a property to a currently logged-in client user.
 * The method marks the given property as rented, associates it with the client,
 * and sets a rental date based on user input.
 *
 * @param property The `Property` object to be rented. This will be updated with
 *                 rental information such as the rental status and date.
 */
void System::rent(const SharedProperty& property) {
    const auto user = getUser().getClient();
    property->setIsRented(true);
    user->add(property);
    std::cout << " ~~ Alugando Propriedade ~~ " << std::endl;
    std::cout << " ~~ Insira a Data ~~ " << std::endl;
    std::cout << "Dia: ";
    uint8_t day;
    std::cin >> day;
    std::cout << "Mes: ";
    uint8_t month;
    std::cin >> month;
    std::cout << "Ano: ";
    uint16_t year;
    std::cin >> year;
    property->getRentedProperty().setRented(Date(day, month, year), user->getName());
}


/**
 * Updates the specified property's attributes based on the user's choice (option).
 * Depending on the provided option, the method prompts the user to input a new value
 * for the location type, capacity, or price. Users can also retain the current value
 * by providing an empty input or zero, as appropriate. The property is updated
 * only if at least one valid input is provided; otherwise, no changes are made.
 *
 * @param property The property object to be updated.
 * @param option   Defines the attribute to be updated:
 *                 - "2": Update the location type.
 *                 - "3": Update the capacity.
 *                 - "4": Update the price.
 */
void System::update(const SharedProperty& property, const std::string& option) {
    std::string locationType;
    uint16_t capacity = 0;
    uint16_t price = 0;
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
 * Removes a property associated with the currently logged-in host user.
 * The method retrieves the host information of the logged-in user, then calls
 * the `remove` method on the host object to remove the property corresponding
 * to the `loggedUserId`. It also provides user feedback on the status of the removal
 * and refreshes the properties list afterward.
 */
void System::remove(const std::string& id) {
    const auto user = getUser();
    if (this->clientType)
        user.getClient()->remove(id);
    else {
        user.getHost()->remove(id);
        this->listOfProperties.clear();
        createPropertiesList();
    }
    std::cout << " ~~ Removendo Propriedade ~~ " << std::endl;
    std::cout << " ~~ Propriedade removida com sucesso ~~ " << std::endl;
}

/**
 * Allows the logged-in user to rate a property by providing a star rating between 1 and 5.
 * The rating is collected from the user, and the method then associates the given
 * rating with the property under the logged-in user's ID.
 *
 * @param property The property object to be rated by the user. The property's star-rating
 *                 system is updated based on the user's input.
 */
void System::rate(const SharedProperty& property) const {
    std::cout << " ~~ Avaliar Propriedade ~~ " << std::endl;
    std::cout << "Digite a nota (1-5): " << std::endl;
    uint8_t stars;
    std::cin >> stars;
    property->getStars().addStars(this->loggedUserId, stars);
}

/**
 * Adds a new property to the system and associates it with the currently logged-in host.
 * This method interacts with the user to collect property details, including address,
 * location type, capacity, and price. It then creates a new `Property` object and
 * assigns it to the logged-in host's list as well as the system-wide property list.
 *
 * The method retrieves the logged-in user as a host via `getUser().getHost()`
 * and ensures the property owner information is updated accordingly.
 *
 * Steps performed by this method:
 * - Prompts the user to input the property's address (country, state, and city).
 * - Collects additional property attributes such as location type, capacity, and price.
 * - Constructs a new `Property` object with the gathered details.
 * - Updates the user's property list and the system's global list of properties.
 */
void System::newProperty() {
    const auto user = getUser().getHost();
    std::cout << " ~~ Adicionar Nova Propriedade ~~ " << std::endl;
    // Gather property details from the user
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
    uint16_t capacity;
    std::cin >> capacity;

    std::cout << "Digite o preco do imovel: ";
    uint16_t price;
    std::cin >> price;

    // Create the new property
    auto newProperty = std::make_shared<Property>(propertyAddress, user->getName(), locationType, capacity, price);
    // Add the property to the user's list and system list
    user->add(newProperty);
    this->listOfProperties.push_back(newProperty);
    newProperty.reset();
}

/**
 * Displays various system interface menus to the user based on their current state or action.
 * The method adapts its menu options depending on whether the user is logged in, their user type,
 * or the specific interface section they're interacting with, like filters or property management.
 *
 * @param option The interface option to display. Possible values are:
 *               "notLogged" - Display the menu for unauthenticated users.
 *               "logged" - Display the menu for logged-in users, with options depending on their type (client or host).
 *               "filters" - Display the menu for setting or removing filters, available only for clients.
 *               "manage" - Display the property management menu, available only for clients.
 */
void System::interface(const std::string& option) const {
    if (option == "notLogged") {  // Not Logged
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
 * Displays a menu based on the provided option and captures the user's choice.
 * Depending on the `option` parameter, this method presents various menu options
 * for user interactions like searching, managing, or confirming actions. The user's
 * choice is read from input, clears the console, and returns the entered choice.
 *
 * @param option The specific menu type to display. Defaults to "choice". Options include:
 *               "searchClient", "searchHost", "selectProperty", "manageProperty",
 *               "rate", "confirm". If none match, a general selection prompt is shown.
 * @return A string representing the user's choice from the displayed menu.
 */
std::string System::selector(const std::string& option = "options") {
    if (option == "searchClient") {  // Selector with filter
        std::cout << "Filtrar(f)\tSelecionar(numero)\tVoltar(v)" << std::endl;
    } else if (option == "select") {  // Selector without filter
        std::cout << "Selecionar(numero)\tVoltar(v)" << std::endl;
    } else if (option == "selectedProperty") {  // Selected property
        std::cout << "Alugar(a)\tVoltar(v)" << std::endl;
    } else if (option == "manageProperty") {  // Manage property
        std::cout << "Editar(e)\tDeletar(d)\tVoltar(v)" << std::endl;
    } else if (option == "selectedRent") {  // Rate property choice
        std::cout << "Avaliar(a)\tCancelar(c)\tVoltar(v)" << std::endl;
    } else if (option == "back") {
        std::cout << "Voltar(v)\t" << std::endl;
    } else if (option == "confirm") {  // Confirmation menu
        std::cout << "Confirmar(s)\tCancelar(n)" << std::endl;
    } else {
        std::cout << "Escolha: " << std::endl;
    }
    std::string choice;
    std::cin >> choice;
    std::cout << std::endl;
    return choice;
}

void System::addUser(const SharedHost& newHost) { this->vecOfHosts.push_back(newHost); }

void System::addUser(const SharedClient& newClient) { this->vecOfClients.push_back(newClient); }

void System::addProperty(const SharedHost& user, const std::string& country, const std::string& state,
                         const std::string& city, const std::string& locationType, const uint16_t& capacity,
                         const uint16_t& price) {
    auto newProperty =
        std::make_shared<Property>(Address(country, state, city), user->getName(), locationType, capacity, price);
    user->add(newProperty);
    this->listOfProperties.push_back(newProperty);
    newProperty.reset();
}

/**
 * @brief Default constructor for the System class.
 *
 * Initializes the System class with default values:
 * - `clientType` is set to true to indicate user/client mode.
 * - `isLogged` is set too false to indicate no user is logged in.
 * - `loggedUserId` is initialized as an empty string.
 *
 * @return A newly created System instance with default configurations.
 */
System::System() : addressFilter(Address("", "", "")) {
    clientType = true;  // true for user false for host
    isLogged = false;
    loggedUserId = "";
    priceFilter = 0;
    createPropertiesList();
}
