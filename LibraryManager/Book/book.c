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
    printf("Enter book's tiltle: ");
    fgets(b.title, MAX_LENGHT_TITLE, stdin);
    b.title[strcspn(b.title, "\n")] = 0;
    printf("Enter name author: ");
    fgets(b.author, LENGHT_NAME_AUTHOR, stdin);
    b.author[strcspn(b.author, "\n")] = 0;
    b.isBorrowed = 0;
    books[(*count)++] = b;

    return BOOK_SUCCESS_ADD;
}

BookRetCode_t editBook(Book_t books[], int count)
{
    int id;

    printf("Enter book's id need edit: ");
    scanf("%d", &id);
    getchar();
    for (int i = 0; i < count; i++)
    {
        if (books[i].id == id)
        {
            printf("Enter new book's tiltle: ");
            char buf[MAX_LENGHT_TITLE];
            fgets(buf, MAX_LENGHT_TITLE, stdin);
            if (buf[0] != '\n')
            {
                buf[strcspn(buf, "\n")] = 0;
                strcpy(books[i].title, buf);
            }

            printf("Enter new name author: ");
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

    printf("Enter book's id need delete: ");
    scanf("%d", &id);
    getchar();
    for (int i = 0; i < *count; i++)
    {
        if (books[i].id == id)
        {
            if (books[i].isBorrowed == 1)
            {
                return BOOK_DELETE_FAILED_BORROWED;
            }

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
