#ifndef BOOK_H
#define BOOK_H

#define MAX_BOOKS 100
#define MAX_LENGHT_TITLE MAX_BOOKS
#define LENGHT_NAME_AUTHOR MAX_BOOKS
#define BOOK_ERROR_LIST(X)         \
    X(BOOK_SUCCESS_ADD, "Book added successfully.") \
    X(BOOK_ADD_FAILED_FULL, "ERROR: Cannot add new book — library storage is full.") \
    X(BOOK_EDIT_FAILED_NOT_FOUND, "ERROR: Cannot edit book — book not found in library.") \
    X(BOOK_SUCCESS_EDIT, "Book information updated successfully.") \
    X(BOOK_DELETE_FAILED_NOT_FOUND, "ERROR: Cannot delete book — book not found in library.") \
    X(BOOK_DELETE_FAILED_BORROWED, "ERROR: Cannot delete book — the book is currently borrowed.") \
    X(BOOK_SUCCESS_DELETE, "Book deleted successfully.")

typedef enum {
#define X(code, msg) code,
    BOOK_ERROR_LIST(X)
#undef X
    BOOK_ERROR_COUNT
} BookRetCode_t;

typedef struct
{
    int id;
    char title[MAX_LENGHT_TITLE];
    char author[LENGHT_NAME_AUTHOR];
    int isBorrowed;             /* 0: available, 1: borrowed */
} Book_t;

/**
 * @brief   Adds a new book record to the library.
 * @param   books   Array of Book_t structures representing all current books.
 * @param   n       Pointer to the current number of books in the library.
 * @return  BookRetCode_t  Status code indicating the operation result.
 * 
 * @details This function inserts a new book entry into the library system.
 *          Returns BOOK_SUCCESS_ADD on success, or BOOK_ADD_FAILED_FULL if the library is full.
 */
BookRetCode_t addBook(Book_t books[], int *n);

/**
 * @brief   Updates information of an existing book.
 * @param   books   Array of Book_t structures representing all current books.
 * @param   n       Current number of books in the library.
 * @return  BookRetCode_t  Status code indicating the operation result.
 * 
 * @details The function modifies book information identified by its unique ID or index.
 *          Returns BOOK_SUCCESS_EDIT on success, or BOOK_EDIT_FAILED_NOT_FOUND if the book does not exist.
 */
BookRetCode_t editBook(Book_t books[], int n);

/**
 * @brief   Removes a book record from the library.
 * @param   books   Array of Book_t structures representing all current books.
 * @param   n       Pointer to the current number of books (decremented after deletion).
 * @return  BookRetCode_t  Status code indicating the operation result.
 * 
 * @details This function deletes a book from the collection based on its ID.
 *          Returns BOOK_SUCCESS_DELETE on success,
 *          BOOK_DELETE_FAILED_NOT_FOUND if the book is missing,
 *          or BOOK_DELETE_FAILED_BORROWED if the book is currently borrowed.
 */
BookRetCode_t deleteBook(Book_t books[], int *n);


#endif
