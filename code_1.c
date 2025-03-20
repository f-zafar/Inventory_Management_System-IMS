/* Cdeliv1gp<group 1>.pdf */
#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100

// Function prototypes
void login();
void mainMenu(char names[][30], int quantity[], float price[], int *count);
void addItem(char names[][30], int quantity[], float price[], int *count);
void removeItem(char names[][30], int quantity[], float price[], int *count);
void updateItem(char names[][30], int quantity[], float price[], int count);
void displayInventory(char names[][30], int quantity[], float price[], int count);

int main() {
    char names[MAX_PRODUCTS][30];
    int quantity[MAX_PRODUCTS];
    float price[MAX_PRODUCTS];
    int count = 0;

    login(); // Login before accessing the main menu
    mainMenu(names, quantity, price, &count);

    return 0;
}

void login() {
    char username[20], password[20];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    printf("Login successful!\n");
}

void mainMenu(char names[][30], int quantity[], float price[], int *count) {
    int option;

    do {
        printf("\nMain Menu:\n");
        printf("1. Add Item\n");
        printf("2. Remove Item\n");
        printf("3. Update Item\n");
        printf("4. Display Inventory\n");
        printf("5. Exit\n");
        printf("Choose your option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                addItem(names, quantity, price, count);
                break;
            case 2:
                removeItem(names, quantity, price, count);
                break;
            case 3:
                updateItem(names, quantity, price, *count);
                break;
            case 4:
                displayInventory(names, quantity, price, *count);
                break;
            case 5: 
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid option! Please try again.\n");
        }
    } while (option != 5);
}

void addItem(char names[][30], int quantity[], float price[], int *count) {
    if (*count < MAX_PRODUCTS) {
        printf("Enter product name: ");
        scanf("%s", names[*count]);
        printf("Enter quantity: ");
        scanf("%d", &quantity[*count]);
        printf("Enter price: ");
        scanf("%f", &price[*count]);
        (*count)++;
        printf("Item added successfully!\n");
    } else {
        printf("Inventory full! Cannot add more items.\n");
    }
}

void removeItem(char names[][30], int quantity[], float price[], int *count) {
    if (*count == 0) {
        printf("No items to remove.\n");
        return;
    }

    char nameToRemove[30];
    int found = -1;
    printf("Enter the name of the product to remove: ");
    scanf("%s", nameToRemove);

    for (int i = 0; i < *count; i++) {
        if (strcmp(names[i], nameToRemove) == 0) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        for (int j = found; j < *count - 1; j++) {
            strcpy(names[j], names[j + 1]);
            quantity[j] = quantity[j + 1];
            price[j] = price[j + 1];
        }
        (*count)--;
        printf("Item removed successfully!\n");
    } else {
        printf("Item not found.\n");
    }
}

void updateItem(char names[][30], int quantity[], float price[], int count) {
    if (count == 0) {
        printf("No items to update.\n");
        return;
    }

    char nameToUpdate[30];
    int found = -1;
    printf("Enter the name of the product to update: ");
    scanf("%s", nameToUpdate);

    for (int i = 0; i < count; i++) {
        if (strcmp(names[i], nameToUpdate) == 0) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        printf("Enter new quantity: ");
        scanf("%d", &quantity[found]);
        printf("Enter new price: ");
        scanf("%f", &price[found]);
        printf("Item updated successfully!\n");
    } else {
        printf("Item not found.\n");
    }
}

void displayInventory(char names[][30], int quantity[], float price[], int count) {
    if (count == 0) {
        printf("No items in inventory.\n");
        return;
    }

    printf("\nInventory List:\n");
    printf("----------------------------------------------------\n");
    printf("No.\tName\t\tQuantity\tPrice\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t\t%d\t\t%.2f\n", i+1, names[i], quantity[i], price[i]);
    }
    printf("----------------------------------------------------\n\n");
}
