#include <iostream>
#include <ostream>

#include "System.hpp"

auto main() -> int {
    int control = 1;
    std::string option;
    while (control != -1) {
        switch (control) {
            case 1: {
                if (!System::getIsLogged()) {
                    System::interface("notLogged");
                    option = System::selector("choice");
                    if (option == "1")
                        control = 2;
                    else if (option == "2")
                        control = 3;
                    break;
                }
                System::interface("logged");
                option = System::selector("choice");
                if (System::getClientType()) {
                    if (option == "1")
                        control = 4;
                    else if (option == "2")
                        control = 6;
                    else if (option == "3")
                        control = 8;
                    else
                        control = 0;
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
                else
                    control = 0;
                break;
            }
            case 2: {
                System::signin();
                control = 1;
                break;
            }
            case 3: {
                System::signup();
                control = 1;
                break;
            }
            case 4: {  // All properties from client
                std::vector<Property> properties = System::showProperties();
                option = System::selector("searchClient");
                if (option == "f") {
                    do {
                        System::interface("filters");
                        option = "f" + System::selector("choice");
                        System::searchFilter(option);
                        if (option == "f5") {
                            System::searchFilter();
                            break;
                        }
                    } while (option != "f6");
                    control = 4;
                    break;
                }
                if (option == "v") {
                    control = 1;
                    break;
                }
                // Property Selected
                const int indexC = std::stoi(option) - 1;
                Property propertyC = properties[indexC];
                propertyC.status();
                option = System::selector("selectedProperty");
                if (option == "1") System::rent(propertyC);
                control = 4;
                break;
            }
            case 5: {  // All properties from host
                std::vector<Property> propertiesH = System::showProperties(true);
                option = System::selector("select");
                if (option == "v") {
                    control = 1;
                    break;
                }
                // Property Selected
                const int indexH = std::stoi(option) - 1;
                Property propertyH = propertiesH[indexH];
                option = System::selector("manageProperty");
                if (option == "2") {
                    System::remove();
                }
                control = 5;
                if (option != "1") {
                    control = 1;
                    break;
                }
                do {
                    System::interface("manage");
                    option = System::selector("choice");
                    System::update(propertyH, option);
                } while (option != "4");
                break;
            }
            case 6: {  // All properties rented
                std::vector<Property> propertiesRent = System::showProperties("rented");
                if (System::getClientType())
                    option = System::selector("select");
                else {
                    option = System::selector("back");
                    if (option == "1") {
                        control = 1;
                        break;
                    }
                }

                if (option == "2") {
                    control = 1;
                    break;
                }

                // Property Selected
                const int indexR = std::stoi(option) - 1;
                Property propertyR = propertiesRent[indexR];
                propertyR.status();
                option = System::selector("rate");
                if (option == "1") {
                    System::rate(propertyR);
                    control = 1;
                } else
                    control = 6;
                break;
            }
            case 7: {
                System::newProperty();
                control = 1;
                break;
            }
            case 8: {
                System::logout();
                control = 1;
                break;
            }
            default: {
                std::cout << "Você tem certeza que quer sair?" << std::endl;
                option = System::selector("confirm");
                if (option == "2") {
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
