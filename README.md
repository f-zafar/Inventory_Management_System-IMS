# Inventory Management System (IMS)

## Overview
This project is an **Inventory Management System (IMS)** developed progressively over a 14-week course. The system was initially written in **C** and later transitioned to **C++**, incorporating advanced programming paradigms and data structures to improve efficiency, maintainability, and usability.

## Team Members
- Fatima Zafar
- Amini Marvo
- Alireza Eftekhar
- Yahya Maniar

## Features
### Initial Version (C-based)
- Simple array-based inventory tracking
- Functions for adding, removing, updating, and displaying items
- Basic user authentication

### Improved Version (C with Dynamic Memory)
- Implementation of **linked lists** for efficient inventory management
- **Structs** for better organization of product data
- Enhanced memory management for scalability

### Final Version (C++ with OOP)
- Transitioned to **Object-Oriented Programming (OOP)**
- Utilized **classes and inheritance** to categorize inventory items
- Implemented **polymorphism** for handling different product types
- Used **stacks and queues** for transaction history and order management
- Added **file handling** for saving and loading inventory data
- Improved user interaction with better input validation and error handling

## Files
- `code_1.c`: Basic C implementation with arrays
- `code_2.c`: Improved C implementation with linked lists and dynamic memory
- `code_3.cpp`: Transitioned to C++ using classes and linked lists
- `code_4.cpp`: Advanced C++ version with polymorphism, file handling, and order management
- `IMS_presentation.pdf`: Project documentation and presentation

## Installation & Compilation
### Requirements
- GCC (for C-based versions)
- G++ (for C++ versions)
- Any standard C/C++ compiler (e.g., MinGW, Clang, MSVC)

### Compilation Steps
For C programs:
```sh
gcc code_1.c -o ims_c
./ims_c
```

For C++ programs:
```sh
g++ code_3.cpp -o ims_cpp
./ims_cpp
```

For the advanced version:
```sh
g++ code_4.cpp -o ims_advanced_cpp
./ims_advanced_cpp
```

## Usage
1. Run the program.
2. Log in using a username and password.
3. Choose from the main menu options:
   - Add an item
   - Remove an item
   - Update item details
   - Display inventory
   - View transactions
   - Manage orders (in advanced version)
4. Follow on-screen instructions to manage inventory effectively.

## Future Improvements
- Implement a **graphical user interface (GUI)**
- Integrate a **database** for persistent storage
- Add **networking capabilities** for multi-user access
- Enhance security with **encryption and role-based authentication**

## Conclusion
This project demonstrates the evolution of an **Inventory Management System**, showcasing **structured programming in C** and **OOP principles in C++**. The final version efficiently manages inventory using **advanced data structures** and **memory management techniques**.
