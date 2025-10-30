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

void showBooks(Book_t books[], int n)
{
    printf("\n--- Danh sach sach ---\n");
    for (int i = 0; i < n; i++)
    {
        printf("ID: %d | %s | %s | %s\n",
               books[i].id, books[i].title, books[i].author,
               books[i].isBorrowed == 0 ? "Con" : "Muon");
    }
}

void showUsers(User_t users[], int n)
{
    printf("\n--- Danh sach nguoi dung ---\n");
    for (int i = 0; i < n; i++)
    {
        printf("ID: %d | %s | Dang muon %d sach\n",
               users[i].id, users[i].name, users[i].borrowedCount);
    }
}

void showBorrowedBooks(Book_t books[], int n)
{
    printf("\n--- Sach dang duoc muon ---\n");
    int found = 0;
    for (int i = 0; i < n; i++)
    {
        if (books[i].isBorrowed == 1)
        {
            printf("ID: %d | %s | %s\n", books[i].id, books[i].title, books[i].author);
            found = 1;
        }
    }
    if (!found)
        printf("Khong co sach nao dang duoc muon.\n");
}

void showBorrowingUsers(User_t users[], int n)
{
    printf("\n--- Nguoi dung dang muon sach ---\n");
    int found = 0;
    for (int i = 0; i < n; i++)
    {
        if (users[i].borrowedCount > 0)
        {
            printf("ID: %d | %s | Dang muon %d sach\n", users[i].id, users[i].name, users[i].borrowedCount);
            found = 1;
        }
    }
    if (!found)
        printf("Khong co nguoi dung nao dang muon sach.\n");
}

BookRetCode_t searchBook(Book_t books[], int n)
{
    char keyword[100];
    int found = 0;

    printf("Nhap tu khoa tieu de/tac gia: ");
    getchar();
    fgets(keyword, 100, stdin);
    keyword[strcspn(keyword, "\n")] = 0;

    for (int i = 0; i < n; i++)
    {
        if (strstr(books[i].title, keyword) || strstr(books[i].author, keyword))
        {
            printf("ID: %d | %s | %s | %s\n",
                   books[i].id, books[i].title, books[i].author,
                   books[i].isBorrowed == 0 ? "Con" : "Muon");
            found = 1;
        }
    }

    if (!found)
    {
        return BOOK_SERCH_NOT_FOUND;
    }
    
    return BOOK_SERCH_OK;
}

UserRetCode_t searchUser(User_t users[], int n)
{
    char keyword[100];
    printf("Nhap tu khoa ten nguoi dung: ");
    getchar();
    fgets(keyword, 100, stdin);
    keyword[strcspn(keyword, "\n")] = 0;
    int found = 0;
    for (int i = 0; i < n; i++)
    {
        if (strstr(users[i].name, keyword))
        {
            printf("ID: %d | %s | Dang muon %d sach\n",
                   users[i].id, users[i].name, users[i].borrowedCount);
            found = 1;
        }
    }
    if (!found)
    {
        return USER_SEARCH_NOT_FOUND;
    }

    return USER_SEARCH_OK;
}
