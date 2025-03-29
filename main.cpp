#include <iostream>
#include <ostream>

#include "System.hpp"

int main() {
    int control = 1;
    std::string option;
    auto system = System();

    // Para testes
    auto user = std::make_shared<Host>("userHost", "0", "user@Host");
    system.addUser(user);
    system.addProperty(user, "Brasil", "SC", "Itajai", "Casa", 5, 300);
    system.addProperty(user, "Brasil", "SP", "Sao Paulo", "Apartamento", 3, 200);
    system.addProperty(user, "Brasil", "SC", "Itajai", "Apartamento", 15, 500);
    system.addProperty(user, "Brasil", "SP", "Sao Paulo", "Casa", 25, 1000);
    system.addProperty(user, "Argentina", "Bueno Aires", "La PLata", "Casa", 5, 150);
    system.addProperty(user, "Argentina", "Bueno Aires", "La PLata", "Apartamento", 3, 180);
    user.reset();
    system.addUser(std::make_shared<Client>("userClient", "0", "user@Client"));


    while (control != -1) {
        switch (control) {
            case 1: {
                if (!system.getIsLogged()) {
                    system.interface("notLogged");
                    option = System::selector("options");
                    if (option == "1") {
                        control = 2;
                    } else if (option == "2") {
                        control = 3;
                    } else {
                        control = 0;
                    }
                    break;
                }
                system.interface("logged");
                option = System::selector("options");
                if (system.getClientType()) {
                    if (option == "1")
                        control = 4;
                    else if (option == "2")
                        control = 6;
                    else if (option == "3")
                        control = 8;
                    else if (option == "s")
                        control = 0;
                    else
                        control = 1;
                    break;
                }
                if (option == "1")
                    control = 5;
                else if (option == "2")
                    control = 6;
                else if (option == "3")
                    control = 7;
                else if (option == "4")
                    control = 8;
                else if (option == "s")
                    control = 0;
                else
                    control = 1;
                break;
            }
            case 2: {
                system.signin();
                control = 1;
                break;
            }
            case 3: {
                system.signup();
                control = 1;
                break;
            }
            case 4: {  // All properties
                std::vector<SharedProperty> propertiesNR = system.showProperties();
                if (propertiesNR.empty()) {
                    if (system.hasFilters()) {
                        control = 4;
                        std::cout << "Nenhuma resultado combina com os filtros aplicados" << std::endl;
                        system.interface("filters");
                        option = System::selector("options");
                        if (option == "f5") {
                            system.searchFilter();
                        }
                    } else
                        control = 9;
                    break;
                }
                option = System::selector("searchClient");
                if (option == "f") {
                    do {
                        propertiesNR = system.showProperties();
                        if (propertiesNR.empty()) break;
                        system.interface("filters");
                        option = "f" + System::selector("options");
                        system.searchFilter(option);
                        if (option == "f5") system.searchFilter();
                        propertiesNR.clear();
                    } while (option != "fv");
                    control = 4;
                    propertiesNR.clear();
                    break;
                }
                if (option == "v") {
                    control = 1;
                    propertiesNR.clear();
                    break;
                }
                // Property Selected
                const int indexC = std::stoi(option) - 1;
                auto& propertyNR = propertiesNR[indexC];
                propertyNR->status();
                option = System::selector("selectedProperty");
                if (option == "a") system.rent(propertyNR);
                control = 4;
                propertyNR.reset();
                propertiesNR.clear();
                break;
            }
            case 5: {  // All properties from host
                std::vector<SharedProperty> propertiesH = system.showProperties("allHost");
                if (propertiesH.empty()) {
                    control = 9;
                    break;
                }
                option = System::selector("select");
                if (option == "v") {
                    control = 1;
                    break;
                }
                // Property Selected
                const int indexH = std::stoi(option) - 1;
                auto& propertyH = propertiesH[indexH];
                propertyH->status();
                option = System::selector("manageProperty");
                if (option == "d") {
                    delete propertyH->getRentedProperty();
                    delete propertyH->getStars();
                    system.remove(propertyH->getId());
                    control = 5;
                }
                if (option != "e") {
                    propertiesH.clear();
                    break;
                }
                do {
                    propertyH->status();
                    system.interface("manage");
                    option = System::selector("options");
                    System::update(propertyH, option);
                } while (option != "v");
                propertyH.reset();
                propertiesH.clear();
                break;
            }
            case 6: {  // All properties rented
                std::vector<SharedProperty> propertiesR = system.showProperties("rented");
                if (propertiesR.empty()) {
                    control = 9;
                    break;
                }
                if (system.getClientType())
                    option = System::selector("select");
                else {
                    // ReSharper disable once CppDFAUnusedValue
                    option = System::selector("back");
                    option = "v";
                }

                if (option == "v") {
                    control = 1;
                    propertiesR.clear();
                    break;
                }

                // Property Selected
                const int indexR = std::stoi(option) - 1;
                auto& propertyR = propertiesR[indexR];
                propertyR->status();
                option = System::selector("selectedRent");
                if (option == "a") {
                    system.rate(propertyR);
                } else if (option == "c") {
                    system.remove(propertyR->getId());
                    propertyR->setIsRented(false);
                }
                control = 6;
                propertyR.reset();
                propertiesR.clear();
                break;
            }
            case 7: {
                system.newProperty();
                control = 1;
                break;
            }
            case 8: {
                system.logout();
                control = 1;
                break;
            }
            case 9: {
                std::cout << "Nao ha propriedades cadastradas" << std::endl;
                // ReSharper disable once CppDFAUnusedValue
                option = System::selector("back");
                control = 1;
                break;
            }
            default: {
                std::cout << "Voce tem certeza que quer sair?" << std::endl;
                option = System::selector("confirm");
                if (option != "s") {
                    control = 1;
                    break;
                }
                control = -1;
                std::cout << "Saindo..." << std::endl;
                break;
            }
        }
    }
    return control;
}
