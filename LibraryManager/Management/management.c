#include "management.h" 
#include "../Book/book.h"
#include "../User/user.h"
#include "../Ultils/ultils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static Book_t s_books[MAX_BOOKS];
static int s_bookCount = 0;
static User_t s_users[MAX_USERS];
static int s_userCount = 0;
static char s_choice;                /* choice to selection fucntion */
static char s_newline;               /* variable to check a character is '\n'or not */
static int s_retCode;

/**
*@brief        function manage the book in the library
*@param        no
*@return       no
*/
static void manageBook()
{
    // system("clear");
    showMenu(MENU_BOOK);
    do
    {
        printf("\nENTER YOUR CHOICE: ");
        fflush(stdin);
        if ((scanf("%c%c", &s_choice, &s_newline)) != 2 ||
            (s_newline != '\n'))
        {
            // system("clear");
            showMenu(MENU_BOOK);
            printf("\n\t\t\t-> ERROR: YOUR CHOICE FORMAT WRONG.\n");
        }
        else
        {
            // system("clear"); 
            showMenu(MENU_BOOK);
            switch (s_choice)
            {
                case 'A':   /* Fall through */
                case 'a':
                    s_retCode = addBook(s_books, &s_bookCount);
                    break;
                case 'E':   /* Fall through */
                case 'e':
                    s_retCode = editBook(s_books, s_bookCount);
                    break;
                case 'D':   /* Fall through */
                case 'd':
                    s_retCode = deleteBook(s_books, &s_bookCount);
                    break;
                case 'S':   /* Fall through */
                case 's':
                    showBooks(s_books, s_bookCount);
                    break;
                case 'M':   /* Fall through */
                case 'm':
                    break;
                default:
                    printf("\t\t\t-> CAN'T FIND ANY SUITABLE CHOICE. RE-ENTER YOUR CHOICE !!!!\n");
                    break;
            }
        }
        printf("Gioa tri cuar choice la %c\n", s_choice);
    } while ((s_choice != 'M') && s_choice != 'm');

}

/**
*@brief        function manage user in the library
*@param        no
*@return       no
*/
static void manageUser()
{
    system("clear");
    showMenu(MENU_USER);
    do
    {
        printf("\nENTER YOUR CHOICE: ");
        fflush(stdin);
        if ((scanf("%c%c", &s_choice, &s_newline)) != 2 ||
            (s_newline != '\n'))
        {
            system("clear");
            showMenu(MENU_USER);
            printf("\n\t\t\t-> ERROR: YOUR CHOICE FORMAT WRONG.\n");
        }
        else
        {
            system("clear");
            showMenu(MENU_USER);
            switch (s_choice)
            {
                case 'A':   /* Fall through */
                case 'a':
                    s_retCode = addUser(s_users, &s_userCount);
                    break;
                case 'E':   /* Fall through */
                case 'e':
                    s_retCode = editUser(s_users, s_userCount);
                    break;
                case 'D':   /* Fall through */
                case 'd':
                    s_retCode = deleteUser(s_users, &s_userCount);
                    break;
                case 'S':   /* Fall through */
                case 's':
                    showUsers(s_users, s_userCount);
                    break;
                case 'M':   /* Fall through */
                case 'm':
                    break;
                default:
                    printf("\t\t\t-> CAN'T FIND ANY SUITABLE CHOICE. RE-ENTER YOUR CHOICE !!!!\n");
                    break;
            }
        }
    } while ((s_choice != 'M') && s_choice != 'm');

}

/**
*@brief        function manage borrow book in the library
*@param        no
*@return       no
*/
static void manageBorrow()
{
    int choice;
    do
    {
        printf("\n== QUAN LY MUON TRA ==\n");
        printf("1. Muon sach\n");
        printf("2. Tra sach\n");
        printf("0. Quay lai\n");
        printf("Chon: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
        {
            int uid, bid;
            printf("Nhap ID nguoi muon: ");
            scanf("%d", &uid);
            getchar();
            printf("Nhap ID sach muon: ");
            scanf("%d", &bid);
            getchar();
            User_t *u = NULL;
            Book_t*b = NULL;
            for (int i = 0; i < s_userCount; i++)
                if (s_users[i].id == uid)
                    u = &s_users[i];
            for (int i = 0; i < s_bookCount; i++)
                if (s_books[i].id == bid)
                    b = &s_books[i];
            if (!u || !b)
            {
                printf("Khong tim thay sach hoac nguoi dung.\n");
                break;
            }
            if (b->isBorrowed == 1)
            {
                printf("Sach da duoc muon.\n");
                break;
            }
            if (u->borrowedCount >= 10)
            {
                printf("Nguoi dung da muon toi da 10 sach.\n");
                break;
            }
            b->isBorrowed = 1;
            u->borrowedBooks[u->borrowedCount++] = b->id;
            printf("Muon sach thanh cong.\n");
        }
        break;
        case 2:
        {
            int uid, bid;
            printf("Nhap ID nguoi tra: ");
            scanf("%d", &uid);
            getchar();
            printf("Nhap ID sach tra: ");
            scanf("%d", &bid);
            getchar();
            User_t *u = NULL;
            Book_t*b = NULL;
            for (int i = 0; i < s_userCount; i++)
                if (s_users[i].id == uid)
                    u = &s_users[i];
            for (int i = 0; i < s_bookCount; i++)
                if (s_books[i].id == bid)
                    b = &s_books[i];
            if (!u || !b)
            {
                printf("Khong tim thay sach hoac nguoi dung.\n");
                break;
            }
            if (b->isBorrowed == 0)
            {
                printf("Sach da o thu vien.\n");
                break;
            }
            int found = 0;
            for (int i = 0; i < u->borrowedCount; i++)
            {
                if (u->borrowedBooks[i] == bid)
                {
                    found = 1;
                    for (int j = i; j < u->borrowedCount - 1; j++)
                        u->borrowedBooks[j] = u->borrowedBooks[j + 1];
                    u->borrowedCount--;
                    break;
                }
            }
            if (!found)
            {
                printf("Nguoi dung khong muon sach nay.\n");
                break;
            }
            b->isBorrowed = 0;
            printf("Tra sach thanh cong.\n");
        }
        break;
        }
    } while (choice != 0);
}

/**
*@brief        function manage the library
*@param        no
*@return       no
*/
static void manageSearch()
{
    int choice;
    do
    {
        printf("\n== TIM KIEM & HIEN THI ==\n");
        printf("1. Tim sach theo tieu de/tac gia\n");
        printf("2. Hien thi sach dang duoc muon\n");
        printf("3. Hien thi nguoi dung dang muon sach\n");
        printf("4. Tim nguoi dung\n");
        printf("0. Quay lai\n");
        printf("Chon: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            searchBook(s_books, s_bookCount);
            break;
        case 2:
            showBorrowedBooks(s_books, s_bookCount);
            break;
        case 3:
            showBorrowingUsers(s_users, s_userCount);
            break;
        case 4:
            searchUser(s_users, s_userCount);
            break;
        }
    } while (choice != 0);
}

void manageLibrary()
{
    showMenu(MENU_MAIN);
    do
    {
        printf("\nENTER YOUR CHOICE: ");
        fflush(stdin);
        if ((scanf("%c%c", &s_choice, &s_newline)) != 2 ||
            (s_newline != '\n'))
        {
            // system("clear");
            showMenu(MENU_MAIN);
            printf("\n\t\t\t-> ERROR: YOUR CHOICE FORMAT WRONG.\n");
        }
        else
        {

            switch (s_choice)
            {
                case 'B':   /* Fall through */
                case 'b':
                    manageBook();
                    break;
                case 'U':   /* Fall through */
                case 'u':
                    manageUser();
                    break;
                case 'P':   /* Fall through */
                case 'p':
                    manageBorrow();
                    break;
                case 'S':   /* Fall through */
                case 's':
                    manageSearch();
                    break;
                case 'E':   /* Fall through */
                case 'e':  
                    printf("\n\t\t\tEXIT PROGRAM SUCEESSFULL!!!\n");  
                    break;
                default:
                    printf("\t\t\t-> CAN'T FIND ANY SUITABLE CHOICE. RE-ENTER YOUR CHOICE !!!!\n");
                    break;
            }
        }
    } while ((s_choice != 'E') && s_choice != 'e');
}
