#ifndef USER_H
#define USER_H

#define MAX_USERS 50
#define LENGHT_NAME 100
#define MAX_BORROW_BOOKS 10
#define USER_ERROR_LIST(X) \
    X(USER_SUCCESS_ADD, "User added successfully.") \
    X(USER_ADD_FAILED_FULL, "ERROR: Cannot add new user — library user list is full.") \
    X(USER_EDIT_FAILED_NOT_FOUND, "ERROR: Cannot edit user — user not found in the library.") \
    X(USER_SUCCESS_EDIT, "User information updated successfully.") \
    X(USER_DELETE_FAILED_NOT_FOUND, "ERROR: Cannot delete user — user not found in the library.") \
    X(USER_DELETE_FAILED_BORROWING, "ERROR: Cannot delete user — user currently has borrowed books.") \
    X(USER_SUCCESS_DELETE, "User deleted successfully.") \
    X(USER_SEARCH_NOT_FOUND, "Seacrh user not found.") \
    X(USER_SEARCH_OK, "") \
    X(USER_BORROWING_SHOW_NOT_FOUND, "ERROR: There is no user borrowing book.") \
    X(USER_BORROWING_SHOW_OK, "")

typedef enum {
#define X(code, msg) code,
    USER_ERROR_LIST(X)
#undef X
    USER_ERROR_COUNT
} UserRetCode_t;

typedef struct
{
    int id;
    char name[LENGHT_NAME];
    int borrowedBooks[MAX_BORROW_BOOKS];
    int borrowedCount;
} User_t;

/**
 * @brief   Adds a new user to the system.
 * @param   users   Array of User_t structures representing the user database.
 * @param   count   Pointer to the current number of users (incremented after successful addition).
 * @return  int     Error code defined in UserRetCode_t (e.g., USER_SUCCESS_ADD, USER_ADD_FAILED_FULL).
 */
UserRetCode_t addUser(User_t users[], int *count);

/**
 * @brief   Edits the information of an existing user.
 * @param   users   Array of User_t structures representing the user database.
 * @param   count   Current number of users in the system.
 * @return  int     Error code defined in UserRetCode_t (e.g., USER_SUCCESS_EDIT, USER_EDIT_FAILED_NOT_FOUND).
 */
UserRetCode_t editUser(User_t users[], int count);

/**
 * @brief   Deletes a user from the system.
 * @param   users   Array of User_t structures representing the user database.
 * @param   count   Pointer to the current number of users (decremented after successful deletion).
 * @return  int     Error code defined in UserRetCode_t (e.g., USER_SUCCESS_DELETE, USER_DELETE_FAILED_NOT_FOUND).
 */
UserRetCode_t deleteUser(User_t users[], int *count);

/**
 * @brief   Returns a descriptive error message for a given user-related error code.
 * @param   code    Error code defined in UserRetCode_t (e.g., USER_SUCCESS_ADD, USER_ADD_FAILED_FULL).
 * @return  void.
 */
void userRetCodeToString(UserRetCode_t code);

#endif
