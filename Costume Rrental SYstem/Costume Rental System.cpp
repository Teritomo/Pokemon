#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <list>

using namespace std;

class CostumeRental; // Forward declaration

// Costume ADT
class Costume {
public:
    int costumeID;
    string costumeName;
    int size;
    string costumeFit;
    int numberOfCopies;

    Costume(int id, string n, int s, string f, int num)
        : costumeID(id), costumeName(n), size(s), costumeFit(f), numberOfCopies(num) {}

    void display() const {
        cout << "Costume ID: " << costumeID << "\nCostume Name: " << costumeName << "\nSize: " << size
             << "\nCostume Fit (Adult/Child): " << costumeFit << "\nNumber of Copies: " << numberOfCopies << endl;
    }

    static void addCostume(CostumeRental &store, int id, string costumeName, int size, string fit, int copies);
    static void rentCostume(CostumeRental &store, int customerID, int costumeID);
    static void returnCostume(CostumeRental &store, int customerID);
    static void showCostumeDetails(CostumeRental &store, int costumeID);
    static void displayAllCostumes(CostumeRental &store);
    static void checkCostumeAvailability(CostumeRental &store, int costumeID);
};

// Customer ADT
class Customer {
public:
    int customerID;
    string name;
    string address;

    Customer(int id, string n, string a)
        : customerID(id), name(n), address(a) {}

    void display() const {
        cout << "Customer ID: " << customerID << "\nName: " << name << "\nAddress: " << address << endl;
    }

    static void addCustomer(CostumeRental &store, int id, string name, string address);
    static void showCustomerDetails(CostumeRental &store, int customerID);
    static void listAllCustomers(CostumeRental &store);
    static void listAllCostumesRentedByCustomer(CostumeRental &store, int customerID);
};

// CustomerRent ADT (inherits from Customer)
class CustomerRent : public Customer {
public:
    list<int> rentedCostumes;

    CustomerRent(int id, string n, string a) : Customer(id, n, a) {}

    void rentCostume(int costumeID) {
        rentedCostumes.push_back(costumeID);
    }

    void returnCostume(int costumeID) {
        rentedCostumes.remove(costumeID);
    }

    void displayRentedCostumes() const {
        cout << "Costumes rented by Customer ID " << customerID << ":\n";
        for (list<int>::const_iterator it = rentedCostumes.begin(); it != rentedCostumes.end(); ++it) {
            cout << "Costume ID: " << *it << endl;
        }
    }

    void returnAllCostumes() {
        rentedCostumes.clear();
    }
};

// CostumeRental class to manage all operations
class CostumeRental {
private:
    deque<Costume> costumes;
    deque<CustomerRent> customers;
    int costumeCounter;
    int customerCounter;

public:
    CostumeRental() : costumeCounter(0), customerCounter(0) {
        loadCostumes();
        loadCustomers();
        loadCustomerRents();
    }

    void loadCostumes();
    void loadCustomers();
    void loadCustomerRents();
    void saveCostumes();
    void saveCustomers();
    void saveCustomersRents();
    void menu(); // Declare the menu function

    friend class Costume;
    friend class Customer;
};

// Costume ADT operations implementation
void Costume::addCostume(CostumeRental &store, int id, string costumeName, int size, string fit, int copies) {
    store.costumes.push_back(Costume(id, costumeName, size, fit, copies));
    store.saveCostumes();
    cout << "======================================"<< endl;
    cout << "Costume added successfully." << endl;
    cout << "======================================"<< endl;
}

void Costume::rentCostume(CostumeRental &store, int customerID, int costumeID) {
    for (deque<Costume>::iterator it = store.costumes.begin(); it != store.costumes.end(); ++it) {
        if (it->costumeID == costumeID) {
            it->display();
            if (it->numberOfCopies > 0) {
                it->numberOfCopies--;
                for (deque<CustomerRent>::iterator cit = store.customers.begin(); cit != store.customers.end(); ++cit) {
                    if (cit->customerID == customerID) {
                        cit->rentCostume(costumeID);
                        store.saveCostumes();
                        store.saveCustomersRents();
                        cout << "======================================"<< endl;
                        cout << "Costume rented successfully." << endl;
                        cout << "======================================"<< endl;
                        return;
                    }
                }
                cout << "======================================"<< endl;
                cout << "Customer not found." << endl;
                cout << "======================================"<< endl;
                return;
            } else {
                cout << "======================================"<< endl;
                cout << "Costume not available." << endl;
                cout << "======================================"<< endl;
                return;
            }
        }
    }
    cout << "======================================"<< endl;
    cout << "Costume not found." << endl;
    cout << "======================================"<< endl;
}

void Costume::returnCostume(CostumeRental &store, int customerID) {
    for (deque<CustomerRent>::iterator cit = store.customers.begin(); cit != store.customers.end(); ++cit) {
        if (cit->customerID == customerID) {
            cit->displayRentedCostumes();
            for (list<int>::iterator it = cit->rentedCostumes.begin(); it != cit->rentedCostumes.end(); ++it) {
                for (deque<Costume>::iterator vit = store.costumes.begin(); vit != store.costumes.end(); ++vit) {
                    if (vit->costumeID == *it) {
                        vit->numberOfCopies++;
                    }
                }
            }
            cit->returnAllCostumes();
            store.saveCostumes();
            store.saveCustomersRents();
            cout << "======================================"<< endl;
            cout << "All costumes returned successfully." << endl;
            cout << "======================================"<< endl;
            return;
        }
    }
    cout << "======================================"<< endl;
    cout << "Customer not found." << endl;
    cout << "======================================"<< endl;
}

void Costume::showCostumeDetails(CostumeRental &store, int costumeID) {
    for (deque<Costume>::iterator it = store.costumes.begin(); it != store.costumes.end(); ++it) {
        if (it->costumeID == costumeID) {
            it->display();
            return;
        }
    }
    cout << "======================================"<< endl;
    cout << "Costume with ID " << costumeID << " not found." << endl;
    cout << "======================================"<< endl;
}

void Costume::displayAllCostumes(CostumeRental &store) {
    for (deque<Costume>::iterator it = store.costumes.begin(); it != store.costumes.end(); ++it) {
        it->display();
        cout << endl;
    }
    
}

void Costume::checkCostumeAvailability(CostumeRental &store, int costumeID) {
    for (deque<Costume>::iterator it = store.costumes.begin(); it != store.costumes.end(); ++it) {
        if (it->costumeID == costumeID) {
            it->display();
            cout << "======================================"<< endl;
            cout << "Number of copies available: " << it->numberOfCopies << "\n";
            cout << "======================================"<< endl;
            if (it->numberOfCopies > 0) {
                cout << "\n======================================"<< endl;
                cout << "Status: Available" << endl;
                cout << "======================================"<< endl;
            } else {
                cout << "\n======================================"<< endl;
                cout << "Status: Not Available" << endl;
                cout << "======================================"<< endl;
            }
            return;
        }
    }
    cout << "======================================"<< endl;
    cout << "Costume not found." << endl;
    cout << "======================================"<< endl;
}

// Customer ADT operations implementation
void Customer::addCustomer(CostumeRental &store, int id, string name, string address) {
    store.customers.push_back(CustomerRent(id, name, address));
    store.saveCustomers();
    cout << "======================================"<< endl;
    cout << "Customer added successfully." << endl;
    cout << "======================================"<< endl;
}

void Customer::showCustomerDetails(CostumeRental &store, int customerID) {
    for (deque<CustomerRent>::iterator it = store.customers.begin(); it != store.customers.end(); ++it) {
        if (it->customerID == customerID) {
            it->display();
            return;
        }
    }
    cout << "======================================"<< endl;
    cout << "Customer not found." << endl;
    cout << "======================================"<< endl;
}

void Customer::listAllCustomers(CostumeRental &store) {
    for (deque<CustomerRent>::iterator it = store.customers.begin(); it != store.customers.end(); ++it) {
        it->display();
        cout << endl;
    }
}

void Customer::listAllCostumesRentedByCustomer(CostumeRental &store, int customerID) {
    bool customerFound = false;

    for (deque<CustomerRent>::iterator it = store.customers.begin(); it != store.customers.end(); ++it) {
        if (it->customerID == customerID) {
            customerFound = true;
            if (it->rentedCostumes.empty()) {
                cout << "======================================"<< endl;
                cout << "Customer ID " << customerID << " has not rented any costumes." << endl;
                cout << "======================================"<< endl;
            } else {
                it->displayRentedCostumes();
            }
            return;
        }
    }
    if (!customerFound) {
        cout << "======================================"<< endl;
        cout << "Customer not found." << endl;
        cout << "======================================"<< endl;
    }
}

// CostumeRental class function implementations
void CostumeRental::loadCostumes() {
    ifstream inFile("costumes.txt");
    if (!inFile) {
        cerr << "Error opening costumes file.\n" << endl;
        return;
    }

    int id, size, copies;
    string costumeName, fit;
    while (inFile >> id) {
        inFile.ignore(); // Ignore the newline character
        getline(inFile, costumeName);
        inFile >> size;
        inFile.ignore(); // Ignore the newline character
        getline(inFile, fit);
        inFile >> copies;
        costumes.push_back(Costume(id, costumeName, size, fit, copies));
    }
    inFile.close();
}

void CostumeRental::loadCustomers() {
    ifstream inFile("customers.txt");
    if (!inFile) {
        cerr << "Error opening customers file.\n" << endl;
        return;
    }

    int id;
    string name, address;
    while (inFile >> id) {
        inFile.ignore(); // Ignore the newline character
        getline(inFile, name);
        getline(inFile, address);
        customers.push_back(CustomerRent(id, name, address));
    }
    inFile.close();
}

void CostumeRental::loadCustomerRents() {
    ifstream inFile("customer_rents.txt");
    if (!inFile) {
        cerr << "Error opening customer rents file.\n" << endl;
        return;
    }

    int customerID, costumeID;
    while (inFile >> customerID >> costumeID) {
        for (deque<CustomerRent>::iterator it = customers.begin(); it != customers.end(); ++it) {
            if (it->customerID == customerID) {
                it->rentCostume(costumeID);
                break;
            }
        }
    }
    inFile.close();
}

void CostumeRental::saveCostumes() {
    ofstream outFile("costumes.txt");
    if (!outFile) {
        cerr << "Error opening costumes file for writing.\n" << endl;
        return;
    }

    
    outFile << "Costumes Data File\n"; //labeling text for text file
    outFile << "ID | Name | Size | Fit | NumberOfCopies\n"; //labeling text for text file

    for (deque<Costume>::iterator it = costumes.begin(); it != costumes.end(); ++it) {
        outFile << it->costumeID << "  | " << it->costumeName << " | "
                << it->size << " | " << it->costumeFit << " | "
                << it->numberOfCopies << endl;
    }
    outFile.close();
}

void CostumeRental::saveCustomers() {
    ofstream outFile("customers.txt");
    if (!outFile) {
        cerr << "Error opening customers file for writing.\n" << endl;
        return;
    }

    
    outFile << "Customers Data File\n"; //labeling text for text file
    outFile << "ID | Name | Address\n"; //labeling text for text file

    for (deque<CustomerRent>::iterator it = customers.begin(); it != customers.end(); ++it) {
        outFile << it->customerID << "  | " << it->name << " | "
                << it->address << endl;
    }
    outFile.close();
}

void CostumeRental::saveCustomersRents() {
    ofstream outFile("customer_rents.txt");
    if (!outFile) {
        cerr << "Error opening customer rents file for writing.\n" << endl;
        return;
    }

    outFile << "Customer Rents Data File\n"; //labeling text for text file
    outFile << "CustomerID | CostumeID\n"; //labeling text for text file

    for (deque<CustomerRent>::iterator it = customers.begin(); it != customers.end(); ++it) {
        for (list<int>::iterator vit = it->rentedCostumes.begin(); vit != it->rentedCostumes.end(); ++vit) {
            outFile << it->customerID << " | " << *vit << endl;
        }
    }
    outFile.close();
}

void CostumeRental::menu() {
    int choice;
    do {
        cout << "======================================"<< endl;
        cout << "Costume Rental System Menu:\n";
        cout << "======================================"<< endl;
        cout << "1. New Costume\n";
        cout << "2. Rent a Costume\n";
        cout << "3. Return a Costume\n";
        cout << "4. Show Costume Details\n";
        cout << "5. Display All Costumes\n";
        cout << "6. Check Costume Availability\n";
        cout << "7. Customer Maintenance\n";
        cout << "8. Exit\n";
        cout << "======================================"<< endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "======================================"<< endl;

        switch (choice) {
            case 1: {
                int id;
                string costumeName;
                int size;
                string fit;
                int copies;
                cout << "Enter costume ID: ";
                cin >> id;
                cout << "Enter costume name: ";
                cin.ignore(); // Ignore any remaining newline character in the buffer
                getline(cin, costumeName);
                cout << "Enter size: ";
                cin >> size;
                cout << "Enter fit (Adult/Child): ";
                cin.ignore(); // Ignore any remaining newline character in the buffer
                getline(cin, fit);
                cout << "Enter number of copies: ";
                cin >> copies;
                Costume::addCostume(*this, id, costumeName, size, fit, copies);
                break;
            }
            case 2: {
                int customerID, costumeID;
                cout << "Enter customer ID: ";
                cin >> customerID;
                cout << "======================================"<< endl;
                Customer::showCustomerDetails(*this, customerID);
                cout << "======================================"<< endl;
                char rentAgain;
                do {
                    cout << "Enter costume ID: ";
                    cin >> costumeID;
                    cout << "======================================"<< endl;
                    Costume::rentCostume(*this, customerID, costumeID);
                    cout << "Do you want to rent another costume? (Y/N): ";
                    cin >> rentAgain;
                } while (rentAgain == 'Y' || rentAgain == 'y');
                break;
            }
            case 3: {
                int customerID;
                cout << "======================================"<< endl;
                cout << "Enter customer ID: ";
                cin >> customerID;
                cout << "======================================"<< endl;
                Costume::returnCostume(*this, customerID);
                break;
            }
            case 4: {
                int costumeID;
                cout << "======================================"<< endl;
                cout << "Enter costume ID: ";
                cin >> costumeID;
                Costume::showCostumeDetails(*this, costumeID); 
                break;
            }
            case 5: {
                if(costumes.empty()){
                    cout << "No costumes found.";
                } else {
                Costume::displayAllCostumes(*this);
                }
                break;
            }
            case 6: {
                int costumeID;
                cout << "======================================"<< endl;
                cout << "Enter costume ID: ";
                cin >> costumeID;
                cout << "======================================"<< endl;
                Costume::checkCostumeAvailability(*this, costumeID);
                break;
            }
            case 7: {
                int subChoice;
                cout << "======================================"<< endl;
                cout << "Customer Maintenance Menu:\n";
                cout << "======================================"<< endl;
                cout << "1. Add New Customer\n";
                cout << "2. Show Customer Details\n";
                cout << "3. List All Costumes Rented by a Customer\n";
                cout << "======================================"<< endl;
                cout << "Enter your choice: ";
                cin >> subChoice;
                cout << "======================================"<< endl;

                switch (subChoice) {
                    case 1: {
                        int id;
                        string name, address;
                        cout << "======================================"<< endl;
                        cout << "Enter customer ID: ";
                        cin >> id;
                        cout << "Enter name: ";
                        cin.ignore(); // Ignore any remaining newline character in the buffer
                        getline(cin, name);
                        cout << "Enter address: ";
                        getline(cin, address);
                        cout << "======================================"<< endl;
                        Customer::addCustomer(*this, id, name, address);
                        break;
                    }
                    case 2: {
                        int customerID;
                        cout << "======================================"<< endl;
                        cout << "Enter customer ID: ";
                        cin >> customerID;
                        cout << "======================================"<< endl;
                        Customer::showCustomerDetails(*this, customerID);
                        break;
                    }
                    case 3: {
                        int customerID;
                        cout << "======================================"<< endl;
                        cout << "Enter customer ID: ";
                        cin >> customerID;
                        cout << "======================================"<< endl;
                        Customer::showCustomerDetails(*this, customerID);
                        cout << "======================================"<< endl;
                        Customer::listAllCostumesRentedByCustomer(*this, customerID);
                        break;
                    }
                    default:
                        cout << "Invalid choice.\n";
                }
                break;
            }
            case 8: {
                cout << "Exiting program.\n";
                break;
            }
            default: {
                cout << "Invalid choice.\n";
            }
        }
    } while (choice != 8);
}

int main() {
    CostumeRental store;
    store.menu();
    return 0;
}
