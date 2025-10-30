#include "user.h"
#include <stdio.h>
#include <string.h>

UserRetCode_t addUser(User_t users[], int *count)
{
    User_t u;
    if (*count >= MAX_USERS)
    {
        return USER_ADD_FAILED_FULL;
    }

    u.id = *count + 1;
    printf("Enter user name: ");
    fgets(u.name, 100, stdin);
    u.name[strcspn(u.name, "\n")] = 0;
    u.borrowedCount = 0;
    users[(*count)++] = u;

    return USER_SUCCESS_ADD;
}

UserRetCode_t editUser(User_t users[], int count)
{
    int id;

    printf("Enter user id need edit: ");
    scanf("%d", &id);
    getchar();
    for (int i = 0; i < count; i++)
    {
        if (users[i].id == id)
        {
            printf("Enter new user name: ");
            char buf[100];
            fgets(buf, 100, stdin);
            if (buf[0] != '\n')
            {
                buf[strcspn(buf, "\n")] = 0;
                strcpy(users[i].name, buf);
            }
            return USER_SUCCESS_EDIT;
        }
    }

    return USER_EDIT_FAILED_NOT_FOUND;
}

UserRetCode_t deleteUser(User_t users[], int *count)
{
    int id;
    
    printf("Enter user id need delete: ");
    scanf("%d", &id);
    getchar();
    for (int i = 0; i < *count; i++)
    {
        if (users[i].id == id)
        {
            if (users[i].borrowedCount > 0)
            {
                return USER_DELETE_FAILED_BORROWING;
            }

            for (int j = i; j < *count - 1; j++)
            {
                users[j] = users[j + 1];
            }

            (*count)--;

            return USER_SUCCESS_DELETE;
        }
    }

    return USER_DELETE_FAILED_NOT_FOUND;
}
