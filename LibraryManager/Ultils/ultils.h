#ifndef UTIL_H
#define UTIL_H

#include "../Book/book.h"
#include "../User/user.h"

#define MENU_LIST(X) \
    X(MENU_MAIN,"PROGRAM MANAGE THE LIBRARY",mainMenuItems) \
    X(MENU_BOOK,"BOOK MANAGEMENT MENU",bookMenuItems) \
    X(MENU_USER,"USER MANAGEMENT MENU",userMenuItems) \
    X(MENU_BORROW,"BORROW / RETURN MANAGEMENT MENU",borrowMenuItems) \
    X(MENU_SEARCH,"SEARCH & DISPLAY MENU",searchMenuItems)

typedef enum {
    #define DEFINE_ENUM(name, title, items) name,
    MENU_LIST(DEFINE_ENUM)
    MENU_LAST
    #undef DEFINE_ENUM
} MenuType_t;

void showBooks(Book_t books[], int n);
void showUsers(User_t users[], int n);
void showBorrowedBooks(Book_t books[], int n);
void showBorrowingUsers(User_t users[], int n);
void searchBook(Book_t books[], int n);
void searchUser(User_t users[], int n);
void showMenu(MenuType_t type);

#endif
