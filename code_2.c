#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100 // Define maximum number of products allowed in the inventory

// Struct for product details
typedef struct product {
    char *name;             // Name of the product (string)
    int quantity;           // Quantity of the product (integer)
    float price;            // Price of the product (float)
    struct product *new_address; // Pointer to the next product (linked list)
} product;

// Struct for transaction details
typedef struct transaction {
    char *name;             // Name of the product involved in the transaction (string)
    char *type;             // Type of transaction (added or removed)
    struct transaction *next_transaction; // Pointer to the next transaction (linked list)
} transaction;

// Stack struct to store transactions, using a linked list
typedef struct stack {
    transaction *top; // Pointer to the top of the transaction stack
} Stack;

// Function prototypes - declare all the functions that will be used in the program
void login();
void mainMenu(product **head, product **current, Stack *transactionStack, int *count);
void addItem(product **head, product **current, Stack *transactionStack, int *count);
void removeItem(product **head, Stack *transactionStack, int *count);
void updateItem(product *head, int *count);
void displayInventory(product *head, int count);
void displayTransactions(Stack *transactionStack);
int getIntInput(const char *prompt);
char *getStringInput(const char *prompt);
void pushTransaction(Stack *stack, const char *name, const char *type);

// Main function - entry point of the program
int main() {
    int count = 0; // Count of products in the inventory
    product *head = NULL; // Pointer to the head of the product list
    product *current = NULL; // Pointer to the current (last) product in the list
    Stack transactionStack = {NULL}; // Initialize the transaction stack to be empty

    // Call the login function before accessing the main menu
    login(); 
    // Show the main menu and manage the inventory
    mainMenu(&head, &current, &transactionStack, &count);

    // Freeing the allocated memory for the product list before exiting the program
    product *temp;
    while (head != NULL) {
        temp = head;
        head = head->new_address;
        free(temp->name); // Free product name
        free(temp);       // Free the product struct itself
    }

    // Freeing the allocated memory for the transactions
    transaction *tempTrans;
    while (transactionStack.top != NULL) {
        tempTrans = transactionStack.top;
        transactionStack.top = transactionStack.top->next_transaction;
        free(tempTrans->name); // Free transaction product name
        free(tempTrans->type); // Free transaction type
        free(tempTrans);       // Free the transaction struct itself
    }

    return 0; // Exit the program
}

// Function to simulate login with username and password
void login() {
    char username[21], password[21];
    printf("Enter username: ");
    scanf("%20s", username); // Take username input (max 20 characters)
    while (getchar() != '\n'); // Clear the buffer
    printf("Enter password: ");
    scanf("%20s", password); // Take password input (max 20 characters)
    while (getchar() != '\n'); // Clear the buffer
    printf("Login successful!\n");
}

// Main menu function - handles the user's choices for managing the inventory
void mainMenu(product **head, product **current, Stack *transactionStack, int *count) {
    int choice;
    do {
        // Display menu options
        printf("\nMain Menu:\n");
        printf("1. Add Item\n");
        printf("2. Remove Item\n");
        printf("3. Update Item\n");
        printf("4. Display Inventory\n");
        printf("5. Display Transactions\n");
        printf("6. Exit\n");
        choice = getIntInput("Choose your option: ");

        // Switch-case for different menu options
        switch (choice) {
            case 1: addItem(head, current, transactionStack, count); break;
            case 2: removeItem(head, transactionStack, count); break;
            case 3: updateItem(*head, count); break;
            case 4: displayInventory(*head, *count); break;
            case 5: displayTransactions(transactionStack); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid option! Please try again.\n");
        }
    } while (choice != 6); // Repeat until the user chooses to exit
}

// Function to get integer input with validation
int getIntInput(const char *prompt) {
    int value;
    char buffer[100];  // Temporary buffer to store input

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Validate if the input is an integer
            if (sscanf(buffer, "%d", &value) == 1) {
                return value; // Return valid integer input
            } else {
                printf("Invalid input! Please enter a valid integer.\n");
            }
        } else {
            printf("Error reading input. Please try again.\n");
        }
    }
}

// Function to get string input dynamically (handles any size of input)
char *getStringInput(const char *prompt) {
    char *input = NULL;
    size_t len = 0;
    printf("%s", prompt);
    getline(&input, &len, stdin); // Read input line dynamically
    input[strcspn(input, "\n")] = 0;  // Remove the trailing newline character
    return input; // Return the string input
}

// Push transaction to the stack (add to the top)
void pushTransaction(Stack *stack, const char *name, const char *type) {
    // Allocate memory for a new transaction
    transaction *newTransaction = (transaction *)malloc(sizeof(transaction));
    if (newTransaction == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    // Duplicate the name and type strings for the transaction
    newTransaction->name = strdup(name);
    newTransaction->type = strdup(type);
    // Insert the new transaction at the top of the stack
    newTransaction->next_transaction = stack->top;
    stack->top = newTransaction;
    printf("Transaction added: %s - %s\n", name, type); // Confirmation message
}

// Function to add a new item to the inventory
void addItem(product **head, product **current, Stack *transactionStack, int *count) {
    // Allocate memory for the new product
    product *newProduct = (product *)malloc(sizeof(product));
    if (newProduct == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    // Get the product details from the user
    newProduct->name = getStringInput("Enter product name: ");
    newProduct->quantity = getIntInput("Enter quantity: ");
    printf("Enter price: ");
    scanf("%f", &newProduct->price); // Read price input
    while (getchar() != '\n');  // Clear input buffer

    newProduct->new_address = NULL; // Initialize new_address pointer to NULL
    if (*head == NULL) {
        *head = newProduct; // If the list is empty, make this the head
    } else {
        (*current)->new_address = newProduct; // Otherwise, add it to the end
    }
    *current = newProduct; // Update the current pointer
    (*count)++; // Increment the product count

    // Record the transaction
    pushTransaction(transactionStack, newProduct->name, "Added");
    printf("Product added successfully!\n");
}

// Function to remove an item (or all items) from the inventory
void removeItem(product **head, Stack *transactionStack, int *count) {
    if (*count == 0) {
        printf("No items to remove.\n");
        return;
    }

    // Ask user if they want to remove one product or all
    int choice = getIntInput("Remove (1) one product or (2) all products: ");
    if (choice == 1) {
        // Removing a specific product
        char *nameToRemove = getStringInput("Enter the name of the product to remove: ");
        product *temp = *head, *prev = NULL;

        // Search for the product by name
        while (temp != NULL && strcmp(temp->name, nameToRemove) != 0) {
            prev = temp;
            temp = temp->new_address;
        }

        if (temp == NULL) {
            printf("Product not found.\n");
            free(nameToRemove);
            return;
        }

        // Remove the product from the list
        if (prev == NULL) {
            *head = temp->new_address; // If removing the head product
        } else {
            prev->new_address = temp->new_address; // If removing another product
        }

        // Record the transaction
        pushTransaction(transactionStack, temp->name, "Removed");
        free(temp->name); // Free memory allocated for the name
        free(temp);       // Free memory allocated for the product
        (*count)--;       // Decrement the product count
        printf("Product removed successfully.\n");
        free(nameToRemove); // Free the name to remove input
    } else if (choice == 2) {
        // Removing all products from the list
        product *temp;
        while (*head != NULL) {
            temp = *head;
            *head = (*head)->new_address;
            pushTransaction(transactionStack, temp->name, "Removed");
            free(temp->name); // Free product name
            free(temp);       // Free product struct
        }
        *count = 0; // Reset product count
        printf("All products removed.\n");
    } else {
        printf("Invalid choice.\n");
    }
}

// Function to update product details
void updateItem(product *head, int *count) {
    if (*count == 0) {
        printf("No items to update.\n");
        return;
    }
    char *nameToUpdate = getStringInput("Enter the name of the product to update: ");
    product *temp = head;

    // Search for the product by name
    while (temp != NULL) {
        if (strcmp(temp->name, nameToUpdate) == 0) {
            // Get updated product details from the user
            temp->quantity = getIntInput("Enter new quantity: ");
            printf("Enter new price: ");
            scanf("%f", &temp->price);
            while (getchar() != '\n'); // Clear input buffer
            printf("Item updated successfully!\n");
            free(nameToUpdate); // Free name input
            return;
        }
        temp = temp->new_address; // Move to the next product
    }
    printf("Item not found.\n");
    free(nameToUpdate); // Free name input
}

// Function to display all products in the inventory
void displayInventory(product *head, int count) {
    if (count == 0) {
        printf("No items in inventory.\n");
        return;
    }
    // Print inventory in a tabular format
    printf("\nInventory List:\n");
    printf("No.\tName\t\tQuantity\tPrice\n");
    product *temp = head;
    int i = 1; // Product number
    while (temp != NULL) {
        printf("%d\t%s\t\t%d\t\t%.2f\n", i++, temp->name, temp->quantity, temp->price);
        temp = temp->new_address; // Move to the next product
    }
}

// Function to display all transactions in the stack
void displayTransactions(Stack *transactionStack) {
    if (transactionStack->top == NULL) {
        printf("No transactions recorded.\n");
        return;
    }
    // Print transactions in a tabular format
    printf("\nTransactions:\n");
    printf("No.\tProduct Name\tType\n");
    transaction *current = transactionStack->top;
    int i = 1; // Transaction number
    while (current != NULL) {
        printf("%d\t%s\t\t%s\n", i++, current->name, current->type);
        current = current->next_transaction; // Move to the next transaction
    }
}
