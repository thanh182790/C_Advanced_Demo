#include "book.h"
#include <stdio.h>
#include <string.h>

BookRetCode_t addBook(Book_t books[], int *count)
{
    Book_t b;

    if (*count >= MAX_BOOKS)
    {
        return BOOK_ADD_FAILED_FULL;
    }

    b.id = *count + 1;
    printf("\n===== ADD A NEW BOOK =====\n");
    printf("→ Enter title book: ");
    fgets(b.title, MAX_LENGHT_TITLE, stdin);
    b.title[strcspn(b.title, "\n")] = 0;
    printf("→ Enter author name: ");
    fgets(b.author, LENGHT_NAME_AUTHOR, stdin);
    b.author[strcspn(b.author, "\n")] = 0;
    b.isBorrowed = 0;
    books[(*count)++] = b;

    return BOOK_SUCCESS_ADD;
}

BookRetCode_t editBook(Book_t books[], int count)
{
    int id;
    char buf[MAX_LENGHT_TITLE];

    printf("\n===== EDIT BOOK INFORMATION =====\n");
    printf("→ Enter book ID to edit: ");
    scanf("%d", &id);
    getchar();
    for (int i = 0; i < count; i++)
    {
        if (books[i].id == id)
        {
            printf("\t→ Enter new title (leave empty to keep): ");
            fgets(buf, MAX_LENGHT_TITLE, stdin);
            if (buf[0] != '\n')
            {
                buf[strcspn(buf, "\n")] = 0;
                strcpy(books[i].title, buf);
            }

            printf("\t→ Enter new author (leave empty to keep): ");
            fgets(buf, LENGHT_NAME_AUTHOR, stdin);
            if (buf[0] != '\n')
            {
                buf[strcspn(buf, "\n")] = 0;
                strcpy(books[i].author, buf);
            }

            return BOOK_SUCCESS_EDIT;
        }
    }

    return BOOK_EDIT_FAILED_NOT_FOUND;
}

BookRetCode_t deleteBook(Book_t books[], int *count)
{
    int id;

    printf("\n===== DELETE BOOK =====\n");
    printf("→ Enter book ID to delete: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < *count; i++)
    {
        if (books[i].id == id)
        {
            if (books[i].isBorrowed)
            {
                return BOOK_DELETE_FAILED_BORROWED;
            }

            /* Shift remaining books left */
            for (int j = i; j < *count - 1; j++)
            {
                books[j] = books[j + 1];
            }

            (*count)--;
            return BOOK_SUCCESS_DELETE;
        }
    }

    return BOOK_DELETE_FAILED_NOT_FOUND;
}

BookRetCode_t borrowReturnBook(Book_t books[], int countBook,
                               User_t users[], int countUser,
                               int isBorrow)
{
    User_t *u = NULL;
    Book_t *b = NULL;
    int uid, bid;
    int found = 0;

    printf("\n===== %s A BOOK =====\n", \
            (isBorrow == BORROW_BOOK) ? "BORROW" : "RETURN");
    printf("→ Enter user id: ");
    scanf("%d", &uid);
    getchar();
    printf("→ Enter book id: ");
    scanf("%d", &bid);
    getchar();
    for (int i = 0; i < countUser; i++)
    {
        if (users[i].id == uid)
        {
            u = &users[i];
            break;
        }
    }
    
    if (u == NULL)
    {
        return BOOK_BORROW_RETURN_FAILED_USER_NOT_FOUND;
    }

    for (int i = 0; i < countBook; i++)
    {
        if (books[i].id == bid)
        {
            b = &books[i];
            break;
        }
    }

    if(b == NULL)
    {
        return BOOK_BORROW_RETURN_FAILED_BOOK_NOT_FOUND;
    }

    switch (isBorrow)
    {
    case BORROW_BOOK:
    {
        if (b->isBorrowed == 1)
        {
            return BOOK_BORROW_RETURN_FAILED_BOOK_HAS_BEEN_BORROW;
        }

        if (u->borrowedCount >= MAX_BORROW_BOOKS)
        {
            return BOOK_BORROW_RETURN_FAILED_USER_LIMITED;
        }

        b->isBorrowed = 1;
        u->borrowedBooks[u->borrowedCount++] = b->id;
        return BOOK_BORROW_OK;
    }
    case RETURN_BOOK:
    {
        if (b->isBorrowed == 0)
        {
            return BOOK_BORROW_RETURN_FAILED_BOOK_EXISTED;
        }

        for (int i = 0; i < u->borrowedCount; i++)
        {
            if (u->borrowedBooks[i] == bid)
            {
                found = 1;
                for (int j = i; j < u->borrowedCount - 1; j++)
                {
                    u->borrowedBooks[j] = u->borrowedBooks[j + 1];
                }

                u->borrowedCount--;
                break;
            }
        }

        if (!found)
        {
            return BOOK_BORROW_RETURN_FAILED_USER_NOT_BORROW;
        }
        
        b->isBorrowed = 0;
        return BOOK_RETURN_OK;
    }
        break;
    default:
        break;
    }

    return BOOK_BORROW_RETURN_FAILED_UNKNOWN_MODE;
}

void bookRetCodeToString(BookRetCode_t code)
{
    switch (code)
    {
#define X(code, msg) \
    case code:       \
        printf("\t--->>> %s", msg); \
        break;
        BOOK_ERROR_LIST(X)
#undef X
    default:
        printf ("Unknown book error code.");
        break;
    }
}
