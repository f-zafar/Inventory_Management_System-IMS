#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <queue>
#include <exception>
#include <vector>

// Base class for inventory items
class InventoryItem {
public:
    std::string name;
    int quantity;
    float price;

    // Constructor to initialize an inventory item
    InventoryItem(std::string n, int q, float p) : name(n), quantity(q), price(p) {}

    // Virtual destructor to ensure proper cleanup of derived class objects
    virtual ~InventoryItem() = default;

    // Virtual function to display the item details, to be overridden in derived classes
    virtual void display() const {
        std::cout << name << "\t" << quantity << "\t" << price << "\n";
    }

    // Pure virtual function to get the item type (for polymorphism)
    virtual std::string getType() const = 0; 
};

// Derived class: Electronics (inherits from InventoryItem)
class Electronic : public InventoryItem {
public:
    int warranty; // Warranty in months

    // Constructor to initialize an electronic item
    Electronic(std::string n, int q, float p, int w) : InventoryItem(n, q, p), warranty(w) {}

    // Override the display function to include warranty details
    void display() const override {
        std::cout << "Electronic: ";
        InventoryItem::display();
        std::cout << "\tWarranty: " << warranty << " months\n";
    }

    // Override the getType function to return the specific type
    std::string getType() const override { return "Electronic"; }
};

// Derived class: Perishables (inherits from InventoryItem)
class Perishable : public InventoryItem {
public:
    int shelfLife; // Shelf life in days

    // Constructor to initialize a perishable item
    Perishable(std::string n, int q, float p, int s) : InventoryItem(n, q, p), shelfLife(s) {}

    // Override the display function to include shelf life details
    void display() const override {
        std::cout << "Perishable: ";
        InventoryItem::display();
        std::cout << "\tShelf Life: " << shelfLife << " days\n";
    }

    // Override the getType function to return the specific type
    std::string getType() const override { return "Perishable"; }
};

// Transaction class to track changes in inventory
class Transaction {
public:
    std::string name, type; // name of the item and the type of transaction (added/removed)
    
    // Constructor to initialize a transaction
    Transaction(std::string n, std::string t) : name(n), type(t) {}
};

// Queue for order management, where orders are processed in a FIFO manner
class OrderQueue {
    std::queue<std::string> orders; // Queue to store orders

public:
    // Function to add an order to the queue
    void addOrder(const std::string& order) {
        orders.push(order);
        std::cout << "Order added: " << order << "\n";
    }

    // Function to process an order from the queue (FIFO)
    void processOrder() {
        if (orders.empty()) {
            std::cout << "No orders to process.\n";
            return;
        }
        std::cout << "Processing order: " << orders.front() << "\n";
        orders.pop();
    }

    // Function to display all pending orders
    void displayOrders() {
        if (orders.empty()) {
            std::cout << "No pending orders.\n";
            return;
        }
        std::queue<std::string> temp = orders; // Temporary copy to display orders
        std::cout << "Pending orders:\n";
        while (!temp.empty()) {
            std::cout << temp.front() << "\n";
            temp.pop();
        }
    }
};

// Inventory Manager to manage inventory and orders
class InventoryManager {
    std::vector<InventoryItem*> inventory; // List of inventory items
    std::vector<Transaction> transactions; // List of transactions (added/removed)
    OrderQueue orderQueue; // Object to manage orders

public:
    // Destructor to clean up dynamically allocated memory for inventory items
    ~InventoryManager() {
        for (auto item : inventory) delete item;
    }

    // Function to add an item to the inventory
    void addItem() {
        try {
            std::string name, type;
            int quantity; 
            float price;
            std::cout << "Enter item type (Electronic/Perishable): ";
            std::getline(std::cin, type);
            std::cout << "Enter name: "; 
            std::getline(std::cin, name);
            std::cout << "Enter quantity: "; 
            std::cin >> quantity;
            if (quantity < 0) throw std::invalid_argument("Quantity cannot be negative.");
            std::cout << "Enter price: "; 
            std::cin >> price;
            if (price < 0) throw std::invalid_argument("Price cannot be negative.");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

            // Handle different item types
            if (type == "Electronic") {
                int warranty;
                std::cout << "Enter warranty (months): "; 
                std::cin >> warranty;
                inventory.push_back(new Electronic(name, quantity, price, warranty));
            } else if (type == "Perishable") {
                int shelfLife;
                std::cout << "Enter shelf life (days): "; 
                std::cin >> shelfLife;
                inventory.push_back(new Perishable(name, quantity, price, shelfLife));
            } else {
                throw std::invalid_argument("Invalid item type.");
            }
            transactions.emplace_back(name, "Added");
            std::cout << "Item added successfully.\n";
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    // Function to remove an item from the inventory
    void removeItem() {
        try {
            if (inventory.empty()) throw std::runtime_error("No items in inventory.");
            std::string name;
            std::cout << "Enter name of the item to remove: ";
            std::getline(std::cin, name);

            // Find and remove the item from the inventory
            for (auto it = inventory.begin(); it != inventory.end(); ++it) {
                if ((*it)->name == name) {
                    delete *it; // Free memory
                    inventory.erase(it); // Remove from the vector
                    transactions.emplace_back(name, "Removed");
                    std::cout << "Item removed successfully.\n";
                    return;
                }
            }
            throw std::runtime_error("Item not found.");
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    // Function to display all items in the inventory
    void displayInventory() const {
        if (inventory.empty()) {
            std::cout << "No items in inventory.\n";
            return;
        }
        std::cout << "Inventory:\n";
        for (const auto& item : inventory) item->display();
    }

    // Function to save inventory data to a file
    void saveToFile() {
        try {
            std::ofstream outFile("inventory.txt");
            if (!outFile) throw std::ios_base::failure("Error opening file.");
            for (const auto& item : inventory) {
                outFile << item->getType() << "," << item->name << "," << item->quantity << "," << item->price << "\n";
            }
            outFile.close();
            std::cout << "Inventory saved to file.\n";
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    // Function to load inventory data from a file
    void loadFromFile() {
        try {
            std::ifstream inFile("inventory.txt");
            if (!inFile) throw std::ios_base::failure("Error opening file.");
            inventory.clear(); // Clear the current inventory
            std::string type, name; 
            int quantity; 
            float price;
            while (inFile >> type) {
                std::getline(inFile, name, ','); // Read name
                inFile >> quantity >> price;
                if (type == "Electronic") 
                    inventory.push_back(new Electronic(name, quantity, price, 12));
                else if (type == "Perishable") 
                    inventory.push_back(new Perishable(name, quantity, price, 7));
            }
            inFile.close();
            std::cout << "Inventory loaded from file.\n";
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    // Function to manage orders
    void manageOrders() {
        int choice;
        do {
            std::cout << "1. Add Order\n2. Process Order\n3. Display Orders\n4. Back to Main Menu\n";
            std::cin >> choice; 
            std::cin.ignore();
            switch (choice) {
                case 1: {
                    std::string order;
                    std::cout << "Enter order name: "; 
                    std::getline(std::cin, order);
                    orderQueue.addOrder(order);
                    break;
                }
                case 2: 
                    orderQueue.processOrder(); 
                    break;
                case 3: 
                    orderQueue.displayOrders(); 
                    break;
                case 4: 
                    return;
                default: 
                    std::cout << "Invalid choice.\n";
            }
        } while (choice != 4);
    }

    // Helper function to get an integer input with validation
    int getIntInput(const std::string& prompt) {
        int value;
        std::cout << prompt;
        while (!(std::cin >> value)) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid integer: ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        return value;
    }
};

// Main function where the program starts
int main() {
    InventoryManager manager;
    int choice;

    do {
        std::cout << "\nInventory Management System\n";
        std::cout << "1. Add Item\n2. Remove Item\n3. Display Inventory\n4. Save to File\n5. Load from File\n6. Manage Orders\n7. Exit\n";
        choice = manager.getIntInput("Choose an option: ");
        
        switch (choice) {
            case 1: manager.addItem(); break;
            case 2: manager.removeItem(); break;
            case 3: manager.displayInventory(); break;
            case 4: manager.saveToFile(); break;
            case 5: manager.loadFromFile(); break;
            case 6: manager.manageOrders(); break;
            case 7: std::cout << "Exiting program.\n"; break;
            default: std::cout << "Invalid choice.\n"; break;
        }
    } while (choice != 7);

    return 0;
}
