#include "ultils.h"
#include <stdio.h>
#include <string.h>

static const char *mainMenuItems[] ={
    "|  1. PRESS 'B' OR 'b' TO MANAGE BOOK                               |",
    "|  2. PRESS 'U' OR 'u' TO MANAGE USER                               |",
    "|  3. PRESS 'P' OR 'p' TO MANAGE BORROW OR PAY BOOK                 |",
    "|  4. PRESS 'S' OR 's' TO SEARCH OR SHOW INFORMATION                |",
    "|  5. PRESS 'E' OR 'e' TO EXIT PROGRAM                              |"};

static const char *bookMenuItems[] = {
    "|  1. PRESS 'A' OR 'a' TO ADD A NEW BOOK                            |",
    "|  2. PRESS 'E' OR 'e' TO EDIT BOOK INFORMATION                     |",
    "|  3. PRESS 'D' OR 'd' TO DELETE A BOOK                             |",
    "|  4. PRESS 'S' OR 's' TO SHOW ALL BOOKS IN LIBRARY                 |",
    "|  5. PRESS 'M' OR 'm' TO RETURN TO MAIN MENU                       |"};

static const char *userMenuItems[] = {
    "|  1. PRESS 'A' OR 'a' TO ADD NEW USER                              |",
    "|  2. PRESS 'E' OR 'e' TO EDIT USER INFORMATION                     |",
    "|  3. PRESS 'D' OR 'd' TO DELETE USER                               |",
    "|  4. PRESS 'S' OR 's' TO SHOW ALL USERS                            |",
    "|  5. PRESS 'M' OR 'm' TO RETURN TO MAIN MENU                       |"};

static const char *borrowMenuItems[] = {
    "|  1. PRESS 'B' OR 'b' TO BORROW BOOK                               |",
    "|  2. PRESS 'R' OR 'r' TO RETURN BOOK                               |",
    "|  3. PRESS 'M' OR 'm' TO RETURN TO MAIN MENU                       |"};

static const char *searchMenuItems[] = {
    "|  1. PRESS '1' TO SEARCH BOOK BY TITLE OR AUTHOR                   |",
    "|  2. PRESS '2' TO SHOW ALL BORROWED BOOKS                          |",
    "|  3. PRESS '3' TO SHOW USERS WHO BORROWED BOOKS                    |",
    "|  4. PRESS '4' TO SEARCH USER BY NAME OR ID                        |",
    "|  5. PRESS 'M' OR 'm' TO RETURN TO MAIN MENU                       |"};

#define DEFINE_TITLE(name, title, items) [name] = title,
static const char *menuTitles[] = {
    MENU_LIST(DEFINE_TITLE)};
#undef DEFINE_TITLE

#define DEFINE_ITEMS(name, title, items) [name] = items,
static const char *const *menuContents[] = {
    MENU_LIST(DEFINE_ITEMS)};
#undef DEFINE_ITEMS

#define LINE "-----------------------------------------------------------------------------"

void showMenu(MenuType_t type)
{
    printf("\033[1;33m"); /* Yellow color */
    printf("\n\t\t=====================================================================\n");
    printf("\t\t %40s \n", menuTitles[type]);
    printf("\t\t=====================================================================\n");

    const char *const *items = menuContents[type];
    for (size_t i = 0; items[i] != NULL; ++i)
        printf("\t\t%s\n", items[i]);

    printf("\t\t=====================================================================\n");
    printf("\033[0m"); /* Reset color */
}

/**
 * @brief   Display all books in the library.
 */
void showBooks(Book_t books[], int n)
{
    printf("\n================================= BOOK LIST =================================\n");
    printf("%-5s | %-30s | %-20s | %-8s\n", "ID", "Title", "Author", "Status");
    printf("%s\n", LINE);
    if (n == 0)
    {
        printf("No books available.\n");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        printf("%-5d | %-30s | %-20s | %-8s\n",
               books[i].id,
               books[i].title,
               books[i].author,
               books[i].isBorrowed == 0 ? "Available" : "Borrowed");
    }
    printf("%s\n", LINE);
}

/**
 * @brief   Display all users in the system.
 */
void showUsers(User_t users[], int n)
{
    printf("\n================================= USER LIST =================================\n");
    printf("%-5s | %-25s | %-15s\n", "ID", "Name", "Borrowing");
    printf("%s\n", LINE);
    if (n == 0)
    {
        printf("No users available.\n");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        printf("%-5d | %-25s | %-15d\n",
               users[i].id,
               users[i].name,
               users[i].borrowedCount);
    }
    printf("%s\n", LINE);
}

/**
 * @brief   Show all borrowed books.
 */
BookRetCode_t showBorrowedBooks(Book_t books[], int n)
{
    int found = 0;

    printf("\n============================ BORROWED BOOKS LIST ============================\n");
    printf("%-5s | %-30s | %-20s\n", "ID", "Title", "Author");
    printf("%s\n", LINE);
    for (int i = 0; i < n; i++)
    {
        if (books[i].isBorrowed == 1)
        {
            printf("%-5d | %-30s | %-20s\n",
                   books[i].id,
                   books[i].title,
                   books[i].author);
            found = 1;
        }
    }

    if (!found)
    {
        return BOOK_BORROWED_SHOW_NOT_FOUND;
    }

    printf("%s\n", LINE);
    return BOOK_BORROWED_SHOW_OK;
}

/**
 * @brief   Show all users currently borrowing books.
 */
UserRetCode_t showBorrowingUsers(User_t users[], int n)
{
    int found = 0;

    printf("\n========================= USERS CURRENTLY BORROWING =========================\n");
    printf("%-5s | %-25s | %-15s\n", "ID", "Name", "Books Borrowed");
    printf("%s\n", LINE);
    for (int i = 0; i < n; i++)
    {
        if (users[i].borrowedCount > 0)
        {
            printf("%-5d | %-25s | %-15d\n",
                   users[i].id,
                   users[i].name,
                   users[i].borrowedCount);
            found = 1;
        }
    }

    if (!found)
    {
        return USER_BORROWING_SHOW_NOT_FOUND;
    }

    printf("%s\n", LINE);
    return USER_BORROWING_SHOW_OK;
}

/**
 * @brief   Search for books by title or author keyword.
 */
BookRetCode_t searchBook(Book_t books[], int n)
{
    char keyword[100];
    int found = 0;

    printf("\nEnter keyword (title/author): ");
    getchar();
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0;
    printf("\n=============================== SEARCH RESULT ===============================\n");
    printf("%-5s | %-30s | %-20s | %-10s\n", "ID", "Title", "Author", "Status");
    printf("%s\n", LINE);

    for (int i = 0; i < n; i++)
    {
        if (strstr(books[i].title, keyword) != NULL ||
            strstr(books[i].author, keyword) != NULL)
        {
            printf("%-5d | %-30s | %-20s | %-10s\n",
                   books[i].id,
                   books[i].title,
                   books[i].author,
                   books[i].isBorrowed == 0 ? "Available" : "Borrowed");
            found = 1;
        }
    }

    if (!found)
    {
        return BOOK_SERCH_NOT_FOUND;
    }

    printf("%s\n", LINE);
    return BOOK_SERCH_OK;
}

/**
 * @brief   Search for users by name keyword.
 */
UserRetCode_t searchUser(User_t users[], int n)
{
    char keyword[100];
    int found = 0;

    printf("\nEnter keyword (user name): ");
    getchar();
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0;
    printf("\n============================ USER SEARCH RESULT =============================\n");
    printf("%-5s | %-25s | %-15s\n", "ID", "Name", "Books Borrowed");
    printf("%s\n", LINE);
    for (int i = 0; i < n; i++)
    {
        if (strstr(users[i].name, keyword) != NULL)
        {
            printf("%-5d | %-25s | %-15d\n",
                   users[i].id,
                   users[i].name,
                   users[i].borrowedCount);
            found = 1;
        }
    }

    if (!found)
    {
        return USER_SEARCH_NOT_FOUND;
    }

    printf("%s\n", LINE);
    return USER_SEARCH_OK;
}