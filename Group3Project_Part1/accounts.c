#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 15
#define MAX_PASSWORD 25
#define MAX_USERS 10

typedef struct
{
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    int isAdmin; // boolean. Only the root user can change this for users
    int isRoot; // boolean. Only one user will have this = 1
    int lineNumber;//Contains what line user is found in file
} User;

int rootExists = 0; // 0 if there isn't a root account, 1 if there is. Once this is 1, it should never change.
User currentUser;

// function to intialize a user
User initializeUser(char username[], char password[])
{
    User user;
    strcpy(user.username, username);
    strcpy(user.password, password);
    user.isAdmin = 0;
    user.isRoot = 0;

    return user;
}
// function to check if a user already exists. Return the index of the user if it exists, -1 if it does not.
int checkUserExists(User* database, char username[])
{
    for(int i = 0; i < MAX_USERS; i++)
    {
        if(strcmp(username, database[i].username) == 0)
        {
            return i;
        }
    }
    return -1;
}
// checks if a user is an administrator. Returns 1 if it is, 0 if it is not.
int checkUserAdmin(User* database, char username[])
{
    int index = checkUserExists(database, username);
    // if the user exists the index will be greater than -1
    if(index >= 0)
    {
        if(database[index].isAdmin == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        printf("\nThis user does not exist.\n\n");
        return 0;
    }
}
// function to check if a user is the root
int checkUserRoot(User* database, char username[])
{
    if(rootExists = 0)
    {
        return 0;
    }
    
    int index = checkUserExists(database, username);

    if(index >= 0)
    {
        if(database[index].isRoot = 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        printf("\nThis user does not exists.\n\n");
        return 0;
    }
}
// function to check if the password is correct
int checkPassword(User user, char password[])
{
    if(strcmp(password, user.password) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
// function to login to the system
void login(User* database)
{
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    
    printf("\nUsername: ");
    scanf(" %s" , username);

    printf("Password: ");
    scanf(" %s", password);

    int index = checkUserExists(database, username);
    if(index >= 0) // if the user exists
    {
        if(checkPassword(database[index], password)) // if the entered password is correct
        {
            currentUser = database[index]; // change the current user to this user
            printf("\nLogging in...\n");
            printf("Successfully logged in.\n\n");
        }
        else
        {
            printf("\nThe password entered is incorrect.\n\n");
        }
    }
    else
    {
        printf("\nEither the user does not exist, or the username entered is incorrect.\n\n");
    }
}
// function to make a user the root. This should only be run once
void makeRoot(User user)
{
    user.isRoot = 1;
    rootExists = 1;
}
// function to make a user an administrator. Only the root can do this
void makeAdmin(User* database, User root)
{
    char username[MAX_USERNAME];
    char rootPassword[MAX_PASSWORD];
    if(root.isRoot && root.isAdmin)
    {
        printf("\nEnter the user you wish to make an administrator: ");
        scanf(" %s", username);

        int index = checkUserExists(database, username);
        if(index >= 0)
        {
            printf("\nEnter password to confirm: ");
            scanf(" %s", rootPassword);
            if(checkPassword(root, rootPassword))
            {
                database[index].isAdmin = 1;
                printf("\n%s is now an administrator.\n\n", username);
            }
            else
            {
                printf("\nEntered password is incorrect.\n\n");
            }
        }
        else
        {
            printf("\nThis user does not exist.\n");
        }
    }
    else
    {
        printf("\nThis user is not the root or an administrator.\n\n");
    }
}

void removeAdmin(User* database, User root)
{
    char username[MAX_USERNAME];
    char rootPassword[MAX_PASSWORD];

    if(root.isRoot)
    {
        printf("\nEnter the user you wish to remove as an administrator: ");
        scanf(" %s", username);

        int index = checkUserExists(database, username);
        if(index >= 0)
        {
            if(database[index].isAdmin == 0 && database[index].isRoot == 0)
            {
                printf("%s is not an administrator\n\n", database[index].username);
            }
            else
            {
                printf("\nEnter password to confirm: ");
                scanf(" %s", rootPassword);
                if(checkPassword(root, rootPassword))
                {
                    database[index].isAdmin = 0;
                    printf("\n%s is now removed as an administrator.\n\n", username);
                }
                else
                {
                    printf("\nEntered password is incorrect.\n\n");
                }
            }
        }
        else
        {
            printf("\nThis user does not exist.\n");
        }
    }   
    
    else
    {
        printf("\nThis user is not the root or an administrator.\n\n");
    }         
    
}

int main()
{
    // database to store the users
    User* database = (User*)malloc(MAX_USERS * sizeof(User));

    User user1 = initializeUser("user1", "user1pass");
    User user2 = initializeUser("user2", "user2pass");
    database[0] = user1;
    database[1] = user2;
    makeRoot(user1);

    login(database);
    printf("%d", currentUser.isRoot);
    makeAdmin(database, currentUser);
    return 1;
}