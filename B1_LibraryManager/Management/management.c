#include "management.h"
#include "../Ultils/ultils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*==================== Static Data ====================*/
static Book_t s_books[MAX_BOOKS];
static int s_bookCount = 0;
static User_t s_users[MAX_USERS];
static int s_userCount = 0;
static char s_choice[10];
static int s_retCode;

/*==================== Helper Functions ====================*/
static bool isValidMenuInput(const char *input)
{
    int len = strlen(input);
    return (len == 2 && input[1] == '\n') ||
           (len == 3 && input[1] == '\r' && input[2] == '\n');
}

/**
 * @brief   Reads and validates user menu input.
 * @param   menuType   Menu type to redisplay on error.
 * @return  true if valid input read into s_choice, false otherwise.
 */
static bool readMenuChoice(MenuType_t menuType)
{
    memset(s_choice, 0, sizeof(s_choice));
    printf("\nENTER YOUR CHOICE: ");
    if (fgets(s_choice, sizeof(s_choice), stdin) == NULL)
    {
        system("clear");
        showMenu(menuType);
        printf("\n\t\t\t-> ERROR: Failed to read input.\n");
        return false;
    }

    if (!isValidMenuInput(s_choice))
    {
        system("clear");
        showMenu(menuType);
        printf("\n\t\t\t-> ERROR: INVALID INPUT. Please enter one character!\n");
        return false;
    }

    return true;
}


/**
 * @brief Generic function to handle menu input and loop.
 * @param menuType   The menu type to display (MENU_BOOK, MENU_USER, etc.).
 * @param exitKey    The key to exit this menu (e.g., 'M' or 'E').
 * @param handler    Callback function to handle each user choice.
 */
static void runMenu(MenuType_t menuType, char exitKey, void (*handler)(char))
{
    system("clear");
    showMenu(menuType);
    do
    {
        if (!readMenuChoice(menuType))
        {
            continue;
        }

        if (s_choice[0] == exitKey || s_choice[0] == (exitKey + 32))
        {
            break;
        }

        handler(s_choice[0]);

    } while (1);

    system("clear");
    showMenu(MENU_MAIN);
}

/*==================== Menu Handlers ====================*/

static void handleBookChoice(char c)
{
    switch (c)
    {
    case 'A':   /* Fall through */
    case 'a':
        s_retCode = addBook(s_books, &s_bookCount);
        bookRetCodeToString((BookRetCode_t)s_retCode);
        break;
    case 'E':   /* Fall through */
    case 'e':
        s_retCode = editBook(s_books, s_bookCount);
        bookRetCodeToString((BookRetCode_t)s_retCode);
        break;
    case 'D':   /* Fall through */
    case 'd':
        s_retCode = deleteBook(s_books, &s_bookCount);
        bookRetCodeToString((BookRetCode_t)s_retCode);
        break;
    case 'S':   /* Fall through */
    case 's':
        showBooks(s_books, s_bookCount);
        break;
    default:
        printf("\t\t\t-> INVALID CHOICE. TRY AGAIN!\n");
        break;
    }
}

static void handleUserChoice(char c)
{
    switch (c)
    {
    case 'A':   /* Fall through */
    case 'a':
        s_retCode = addUser(s_users, &s_userCount);
        userRetCodeToString((UserRetCode_t)s_retCode);
        break;
    case 'E':   /* Fall through */
    case 'e':
        s_retCode = editUser(s_users, s_userCount);
        userRetCodeToString((UserRetCode_t)s_retCode);
        break;
    case 'D':   /* Fall through */
    case 'd':
        s_retCode = deleteUser(s_users, &s_userCount);
        userRetCodeToString((UserRetCode_t)s_retCode);
        break;
    case 'S':   /* Fall through */
    case 's':
        showUsers(s_users, s_userCount);
        break;
    default:
        printf("\t\t\t-> INVALID CHOICE. TRY AGAIN!\n");
        break;
    }
}

static void handleBorrowChoice(char c)
{
    switch (c)
    {
    case 'B':   /* Fall through */
    case 'b':
        s_retCode = borrowReturnBook(s_books, s_bookCount,
                                     s_users, s_userCount,
                                     BORROW_BOOK);
        bookRetCodeToString((BookRetCode_t)s_retCode);
        break;
    case 'R':   /* Fall through */
    case 'r':
        s_retCode = borrowReturnBook(s_books, s_bookCount,
                                     s_users, s_userCount,
                                     RETURN_BOOK);
        bookRetCodeToString((BookRetCode_t)s_retCode);
        break;
    default:
        printf("\t\t\t-> INVALID CHOICE. TRY AGAIN!\n");
        break;
    }
}

static void handleSearchChoice(char c)
{
    switch (c)
    {
    case '1':
        s_retCode = searchBook(s_books, s_bookCount);
        bookRetCodeToString((BookRetCode_t)s_retCode);
        break;
    case '2':
        showBorrowedBooks(s_books, s_bookCount);
        break;
    case '3':
        showBorrowingUsers(s_users, s_userCount);
        break;
    case '4':
        s_retCode = searchUser(s_users, s_userCount);
        userRetCodeToString((UserRetCode_t)s_retCode);
        break;
    default:
        printf("\t\t\t-> INVALID CHOICE. TRY AGAIN!\n");
        break;
    }
}

/*==================== Main Menu ====================*/
void manageLibrary()
{
    showMenu(MENU_MAIN);
    do
    {
        if (!readMenuChoice(MENU_MAIN))
        {
            continue;
        }

        switch (s_choice[0])
        {
        case 'B':  /* Fall through */
        case 'b':
            runMenu(MENU_BOOK, 'M', handleBookChoice);
            break;
        case 'U':   /* Fall through */
        case 'u':
            runMenu(MENU_USER, 'M', handleUserChoice);
            break;
        case 'P':   /* Fall through */
        case 'p':
            runMenu(MENU_BORROW, 'M', handleBorrowChoice);
            break;
        case 'S':   /* Fall through */
        case 's':
            runMenu(MENU_SEARCH, 'M', handleSearchChoice);
            break;
        case 'E':   /* Fall through */
        case 'e':
            printf("\n\t\t\tEXIT PROGRAM SUCCESSFULLY!!!\n");
            return;
        default:
            printf("\t\t\t-> INVALID CHOICE. TRY AGAIN!\n");
            break;
        }
    } while (1);
}
