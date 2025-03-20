#include <iostream>
#include <string>
#include <limits>

// Class to represent a product
class Product {
public:
    std::string name;  // Product name
    int quantity;      // Product quantity
    float price;       // Product price
    Product* next;     // Pointer to the next product

    // Constructor to initialize a product
    Product(std::string name, int quantity, float price)
        : name(name), quantity(quantity), price(price), next(nullptr) {}
};

// Class to represent a transaction
class Transaction {
public:
    std::string name;  // Product name
    std::string type;  // Transaction type (added or removed)
    Transaction* next; // Pointer to the next transaction

    // Constructor to initialize a transaction
    Transaction(std::string name, std::string type)
        : name(name), type(type), next(nullptr) {}
};

// Class to manage a stack of transactions
class Stack {
public:
    Transaction* top;  // Pointer to the top of the transaction stack

    Stack() : top(nullptr) {}

    // Function to push a transaction onto the stack
    void push(const std::string& name, const std::string& type) {
        Transaction* newTransaction = new Transaction(name, type);
        newTransaction->next = top;
        top = newTransaction;
        std::cout << "Transaction added: " << name << " - " << type << std::endl;
    }

    // Function to display all transactions
    void display() const {
        if (!top) {
            std::cout << "No transactions recorded.\n";
            return;
        }
        std::cout << "\nTransactions:\n";
        std::cout << "No.\tProduct Name\tType\n";
        Transaction* current = top;
        int i = 1;
        while (current) {
            std::cout << i++ << "\t" << current->name << "\t\t" << current->type << std::endl;
            current = current->next;
        }
    }

    // Destructor to clean up transaction memory
    ~Stack() {
        while (top) {
            Transaction* temp = top;
            top = top->next;
            delete temp;
        }
    }
};

// Class to manage products and transactions
class InventoryManager {
public:
    Product* head;       // Pointer to the head of the product list
    Stack transactionStack; // Transaction stack
    int productCount;    // Count of products in the inventory

    InventoryManager() : head(nullptr), productCount(0) {}

    // Destructor to clean up product memory
    ~InventoryManager() {
        while (head) {
            Product* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Function to add a new item to the inventory
    void addItem() {
        std::string name;
        int quantity;
        float price;

        std::cout << "Enter product name: ";
        std::getline(std::cin, name);
        std::cout << "Enter quantity: ";
        std::cin >> quantity;
        std::cout << "Enter price: ";
        std::cin >> price;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

        Product* newProduct = new Product(name, quantity, price);
        newProduct->next = head; // Insert new product at the beginning
        head = newProduct;
        productCount++;

        // Record the transaction
        transactionStack.push(newProduct->name, "Added");
        std::cout << "Product added successfully!" << std::endl;
    }

    // Function to remove an item from the inventory
    void removeItem() {
        if (productCount == 0) {
            std::cout << "No items to remove.\n";
            return;
        }

        int choice;
        std::cout << "Remove (1) one product or (2) all products: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            std::string nameToRemove;
            std::cout << "Enter the name of the product to remove: ";
            std::getline(std::cin, nameToRemove);

            Product* temp = head;
            Product* prev = nullptr;
            while (temp) {
                if (temp->name == nameToRemove) {
                    if (prev) {
                        prev->next = temp->next;
                    } else {
                        head = temp->next;
                    }
                    transactionStack.push(temp->name, "Removed");
                    delete temp;
                    productCount--;
                    std::cout << "Product removed successfully.\n";
                    return;
                }
                prev = temp;
                temp = temp->next;
            }
            std::cout << "Product not found.\n";
        } else if (choice == 2) {
            while (head) {
                Product* temp = head;
                head = head->next;
                transactionStack.push(temp->name, "Removed");
                delete temp;
            }
            productCount = 0;
            std::cout << "All products removed.\n";
        } else {
            std::cout << "Invalid choice.\n";
        }
    }

    // Function to update a product's details
    void updateItem() {
        if (productCount == 0) {
            std::cout << "No items to update.\n";
            return;
        }

        std::string nameToUpdate;
        std::cout << "Enter the name of the product to update: ";
        std::getline(std::cin, nameToUpdate);

        Product* temp = head;
        while (temp) {
            if (temp->name == nameToUpdate) {
                std::cout << "Enter new quantity: ";
                std::cin >> temp->quantity;
                std::cout << "Enter new price: ";
                std::cin >> temp->price;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Item updated successfully!\n";
                return;
            }
            temp = temp->next;
        }
        std::cout << "Item not found.\n";
    }

    // Function to display all products in the inventory
    void displayInventory() const {
        if (productCount == 0) {
            std::cout << "No items in inventory.\n";
            return;
        }

        std::cout << "\nInventory List:\n";
        std::cout << "No.\tName\t\tQuantity\tPrice\n";
        Product* temp = head;
        int i = 1;
        while (temp) {
            std::cout << i++ << "\t" << temp->name << "\t\t" << temp->quantity << "\t\t" << temp->price << std::endl;
            temp = temp->next;
        }
    }
};

// Function to get integer input with validation
int getIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (!std::cin.fail()) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
            return value;
        } else {
            std::cout << "Invalid input! Please enter a valid integer.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

// Main function
int main() {
    InventoryManager manager;

    // Login info
    std::string username, password;
    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);
    std::cout << "Login successful!\n";

    int choice;
    do {
        std::cout << "\nMain Menu:\n";
        std::cout << "1. Add Item\n";
        std::cout << "2. Remove Item\n";
        std::cout << "3. Update Item\n";
        std::cout << "4. Display Inventory\n";
        std::cout << "5. Display Transactions\n";
        std::cout << "6. Exit\n";
        choice = getIntInput("Choose your option: ");

        switch (choice) {
            case 1: manager.addItem(); break;
            case 2: manager.removeItem(); break;
            case 3: manager.updateItem(); break;
            case 4: manager.displayInventory(); break;
            case 5: manager.transactionStack.display(); break;
            case 6: std::cout << "Exiting...\n"; break;
            default: std::cout << "Invalid option! Please try again.\n";
        }
    } while (choice != 6);

    return 0; // Exit the program
}

