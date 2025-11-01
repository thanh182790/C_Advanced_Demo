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

/**
 * @brief   Displays all books in the library.
 * @param   books   Array of Book_t structures.
 * @param   n       Number of books to display.
 * @return  void
 *
 * @details Prints a formatted list of all books and their information.
 */
void showBooks(Book_t books[], int n);

/**
 * @brief   Displays all users in the system.
 * @param   users   Array of User_t structures.
 * @param   n       Number of users to display.
 * @return  void
 *
 * @details Prints a formatted list of all users and their details.
 */
void showUsers(User_t users[], int n);

/**
 * @brief   Displays all books currently borrowed.
 * @param   books   Array of Book_t structures.
 * @param   n       Number of books in the collection.
 * @return  BookRetCode_t  Status code indicating operation result.
 *
 * @details Lists all books that are currently marked as borrowed.
 */
BookRetCode_t showBorrowedBooks(Book_t books[], int n);

/**
 * @brief   Displays all users who are currently borrowing books.
 * @param   users   Array of User_t structures.
 * @param   n       Number of users in the system.
 * @return  UserRetCode_t  Status code indicating operation result.
 *
 * @details Shows users who have at least one borrowed book.
 */
UserRetCode_t showBorrowingUsers(User_t users[], int n);

/**
 * @brief   Searches for a book by ID, title, or author.
 * @param   books   Array of Book_t structures.
 * @param   n       Number of books to search within.
 * @return  BookRetCode_t  Status code indicating search result.
 *
 * @details Allows user to search and display matching book records.
 */
BookRetCode_t searchBook(Book_t books[], int n);

/**
 * @brief   Searches for a user by ID or name.
 * @param   users   Array of User_t structures.
 * @param   n       Number of users to search within.
 * @return  UserRetCode_t  Status code indicating search result.
 *
 * @details Allows user to search and display matching user records.
 */
UserRetCode_t searchUser(User_t users[], int n);

/**
 * @brief   Displays a menu based on the given menu type.
 * @param   type    Enum value defining which menu to show (main, book, user, etc.).
 * @return  void
 *
 * @details Clears the screen and prints the appropriate menu for user interaction.
 */
void showMenu(MenuType_t type);

#endif
