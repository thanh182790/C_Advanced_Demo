# 📚 Library Management System (C Project)

A simple **console-based library management system** written in C, designed to practice structured programming, modular design, and file organization.

---

## 🧩 Features

### 📖 Book Management
- Manage book information: **Title**, **Author**, **ID**, **Borrow status**
- Support operations:
  - ➕ Add a new book
  - ✏️ Edit book information
  - ❌ Delete a book
- Display a list of all books in the library

### 👤 User Management
- Manage user information: **Name**, **ID**, **List of borrowed books**
- Support operations:
  - ➕ Add a new user
  - ✏️ Edit user information
  - ❌ Delete a user
- Display a list of users and their borrowed books

### 🔄 Borrow / Return Management
- Allow users to borrow books **if available**
- Track borrowed and returned books
- Prevent borrowing if:
  - The book is already borrowed
  - The user has reached their borrow limit

### 🔍 Search & Display
- Search for books by **title** or **author**
- Display:
  - Books currently available
  - Books currently borrowed
  - Users who have borrowed books

### ⚙️ Error Handling
- Validate user input (menu options, IDs, etc.)
- Handle error cases such as:
  - Nonexistent users or books
  - Borrowing unavailable books
  - Empty search results

---

## 🗂️ Project Structure

B1_LibraryManager/
├── Book/
│ ├── book.c # Implementation of book operations
│ └── book.h # Book structure and function declarations
├── User/
│ ├── user.c # Implementation of user operations
│ └── user.h # User structure and function declarations
├── Management/
│ ├── management.c # Core menu & control logic
│ ├── management.h # Function declarations for management layer
│ └── management.c_bk # (Backup file)
├── Ultils/
│ ├── ultils.c # Utility functions (menu, helpers, etc.)
│ └── ultils.h
├── main.c # Entry point of the program
├── Makefile # Build configuration
└── Readme.md # Project documentation

---

## 🏗️ Build & Run Instructions

### 🧱 1. Build the project
Use the provided `Makefile`:

```bash
make

This will:

Compile all source files under Book/, User/, Management/, and Ultils/

Create object files in the build/ directory

Generate the executable: library_manager

---

Run code 
./library_manager

Clean
make clean

