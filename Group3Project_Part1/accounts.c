#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

/*  PASSWORD REQUIREMENTS
    1. Should not contain spaces
    2. Should contain at one digit (0-9)
    3. Length must be @ least 8 characters long
    4. Must contain @ least one special character:
        (Using Oracle ID Manager & Microsoft Active Dir standards, also includes extra's '*')
        -> @    -> %    -> +    -> \    -> /
        -> '    -> !    -> #    -> $    -> ^
        -> ?    -> :    -> ,    -> (    -> )
        -> {    -> }    -> [    -> ]    -> ~
        -> -    -> _    -> .    -> *    -> `
    5. Must contain @ least one lower case letter (a-z)
    6. Must contain @ least one upper case letter (A-Z)
*/

//Validates a new password in separate checks with requirements above
void validate_password(char pwd[])
{
    if(verify_pass_len(pwd) == 1)//Checks length  of password >= 8
    {
        if(verify_char_rules(pwd) == 1)//Checks that password contains at least one lower case and upper case letter
        {
            if(verify_int_rule(pwd) == 1)//Checks that password contains at least one integer (0-9)
            {
                if(verify_specialChar_rule(pwd) == 1)//Checks that password contains at least one of the valid special char's listed above
                {
                    printf("Valid password.\n");
                }
            }
        }
    }

}

//Checks that password is at least 8 characters long
int verify_pass_len(char pwd[])
{
    int result;
    int count = 0;
    while(pwd[count] != '\0')//Counts until it reaches end of password
    {
        count++;
    }
    if(count < 7)
    {
        result = 0;//Sets password as invalid
        printf("Password must be at least 8 characters long.\n");

    }
    else
    {
        result = 1;//Sets password at this point as valid
    }

    return result;
}

//Checks that password contains at least one lower case and upper case letter.
int verify_char_rules(char pwd[])
{
    int result;
    int lowerCharExists = 0;//Boolean check for lower case letter
    int upperCharExists = 0;//Boolean check for upper case letter
    int isInvalidPwd = 0;
    int index = 0;
    while(pwd[index] != '\0')
    {
        if(pwd[index + 1] == '\0')//Checks if reached end of password
        {
            isInvalidPwd = 1;
        }
        if((int)pwd[index] > 64 && (int)pwd[index] < 91)//Checks for upper case ASCII values
        {
            upperCharExists = 1;

        }
        if((int)pwd[index] > 96 && (int)pwd[index] < 123)//Checks for lower case ASCII values
        {
            lowerCharExists = 1;

        }

        index++;
    }

    if(isInvalidPwd == 1 && (lowerCharExists == 0 && upperCharExists == 0))
    {
        result = 0;
        printf("Password requires at least one lower case and upper case letter.\n");
    }
    else
    {
        if(lowerCharExists == 0 && upperCharExists == 1)
        {
            result = 0;
            printf("Password requires at least one lower case letter.\n");
        }
        else if(upperCharExists == 0 && lowerCharExists == 1)
        {
            result = 0;
            printf("Password requires at least one upper case letter.\n");
        }
        else
        {
           result = 1;
        }
    }

    return result;
}

//Checks that password contains at least one integer between 0-9
int verify_int_rule(char pwd[])
{
    int result;
    int containsDigit = 0;//Boolean check if there is digit in password
    int index = 0;
    while(pwd[index] != '\0')
    {
        if(isdigit(pwd[index]))//Checks if each index of password is digit
        {
            containsDigit = 1;
        }

        index++;
    }

    if(containsDigit == 1)
    {
        result = 1;
    }
    else
    {
        result = 0;
        printf("Password must contain at least one digit between 0 and 9\n");
    }

    return result;
}

//Checks if password contains at least one valid special character
int verify_specialChar_rule(char pwd[])
{
    int result;
    int index = 0;
    int hasSpecChar = 0;//Boolean check if password contains a special character
    int isInvalidChar = 0;//Boolean check if password contains an invalid special character
    while(pwd[index] != '\0')
    {
        //If current index of password is not a digit or a letter, checks for invalid characters
        if(!isdigit(pwd[index]) && !isalpha(pwd[index]))
        {
            switch(pwd[index])
            {
            case ' ':
                printf("Spaces are not allowed in password.\n");
                isInvalidChar = 1;
                break;
            case ';':
                printf("Semicolon not allowed in password.\n");
                isInvalidChar = 1;
                break;
            case '|':
                printf("Vertical slash not allowed in password.\n");
                isInvalidChar = 1;
                break;
            case '"':
                printf("Quotation not allowed in password.\n");
                isInvalidChar = 1;
                break;
            case '<':
                printf("Left angle bracket not allowed in password.\n");
                isInvalidChar = 1;
                break;
            case '>':
                printf("Right angle bracket not allowed in password.\n");
                isInvalidChar = 1;
                break;
            default:
                hasSpecChar = 1;//No invalid characters found, then valid special character was found
                break;
            }
        }

        index++;
    }

    if(isInvalidChar == 1)
    {
        result = 0;
    }
    else
    {
        if(hasSpecChar == 0)
        {
            printf("Password requires at least one special character.\n");
            result = 0;
        }
        else
        {
            result = 1;
        }
    }

    return result;
}

int load_all_accounts(char* fileName, User *accountArray) //Takes the relative or absolute file path for the user accounts file and returns the number of accounts, adn the array passed in will contain User struct type filled with all accounts' information
{
    accountArray = realloc(accountArray, sizeof(User));
    FILE *fi;
    fi = fopen(fileName, "r");
    if(fi != NULL)
    {
        char command[10000];
        char uname[10000];
        char pswd[10000];
        int root;
        int admin;
        int eoftest;
        int currentRead = 0;
        while(fgets(command, 10000, fi))
        {
            if(currentRead > 0)
            {
                accountArray = realloc(accountArray, (currentRead+1)*sizeof(User))
            }
            int round = 0;
            int lastIdx = 0;
            for(int i = 0; i < strlen(command); i++)
            {
                if(command[i] == ',')
                {
                    switch (round)
                    {
                    case 0:
                        // get user name
                        strncpy(uname, command, i);
                        lastIdx = i+1;
                        round++;
                        break;
                    case 1:
                        //get password
                        strncpy(pswd, command+lastIdx, i-lastIdx);
                        lastIdx = i+1;
                        round++;
                    case 2:
                        //get root permission
                        root = atoi(command+lastIdx);
                        lastIdx = i+1;
                        round++;
                        break;
                    case 3: 
                        //get admin permission
                        admin = atoi(command+lastIdx);
                        break;
                    default:
                        break;
                    }
                }
            }
            strcpy(accountArray[currentRead].username, uname);
            strcpy(accountArray[currentRead].password, pswd);
            accountArray[currentRead].isAdmin = admin;
            accountArray[currentRead].isRoot = root;
            accountArray[currentRead].lineNumber = currentRead;
            currentRead++;
        }
    }
    fclose(fi);
    return currentRead;
}

User load_active_account(int line_number, char* filename) //takes the line number (starting from 0) for the user in the user info file, and will return just the info for that user
{
    User currentAccount;
    FILE *fi;
    fi = fopen(filename, "r");
    if(fi != NULL)
    {
        // printf("\nAvailable commands:\n");
        // printf("-------------------\n");
        char command[10000];
        char uname[10000];
        char pswd[10000];
        int root;
        int admin;
        int eoftest;
        //created with aid from tutorialkart.com in C - Read Text File, https://www.tutorialkart.com/c-programming/c-read-text-file/#:~:text=C%20%E2%80%93%20Read%20Text%20File%20Character%20by%20Character,Close%20the%20text%20file%20using%20fclose%20%28%29%20function.
        int currentRead = 0;
        while(fgets(command, 10000, fi))
        {
            int round = 0;
            int lastIdx = 0;
            for(int i = 0; i < strlen(command); i++)
            {
                if(command[i] == ',')
                {
                    switch (round)
                    {
                    case 0:
                        // get user name
                        strncpy(uname, command, i);
                        lastIdx = i+1;
                        round++;
                        break;
                    case 1:
                        //get password
                        strncpy(pswd, command+lastIdx, i-lastIdx);
                        lastIdx = i+1;
                        round++;
                    case 2:
                        //get root permission
                        root = atoi(command+lastIdx);
                        lastIdx = i+1;
                        round++;
                        break;
                    case 3: 
                        //get admin permission
                        admin = atoi(command+lastIdx);
                        break;
                    default:
                        break;
                    }
                }
            }
            if(currentRead == findLine)
            {
                strcpy(currentAccount.username, uname);
                strcpy(currentAccount.password, pswd);
                currentAccount.isAdmin = admin;
                currentAccount.isRoot = root;
                currentAccount.lineNumber = currentRead;
            }
            currentRead++;
        }
    }
    fclose(fi);
    return currentAccount;
}

void accounts2file(int numOfAccounts, User *arrayTest, char *filename) //writes the appropriate number of accounts to a file, completely removing whatever was in there before, or creating it if non-existant
{
    FILE *writeTo;
    writeTo = fopen(filename, "w");
    for(int i =0; i < numOfAccounts; i++)
    {
        fprintf(writeTo, "%s,%s,%d,%d\n", arrayTest[i].username, arrayTest[i].password, arrayTest[i].isRoot, arrayTest[i].isAdmin);
    }
}

// function to change the password of a user
void changePassword(User* database, User user)
{
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("\nEnter the user whose password you wish to change: ");
    scanf(" %s", username);
    
    int index = checkUserExists(database, username); // ensure the user exists

    // any user can change their own password, so check this first
    if (strcmp(username, user.username) == 0)
    {
        // ask the user for the new password
        printf("Please enter the new password: ");
        scanf(" %s", password);
        // check that it is a valid password
        validate_password(password);
        // change the password if valid
        // print success or error message
    }
    // if the user is not changing their own password, check if they are the root first
    else if(user.isRoot)
    {
        // if the user exists, the index will be 0 or greater
        if(index >= 0)
        {
            printf("Please enter the new password: ");
            scanf(" %s", password);

            // check if the password is valid
            validate_password(password);
            // change the password if valid
            // print success or error message
        }
    }
    else if(user.isAdmin)
    {
        if(index >= 0)
        {
            // if the admin is trying to change the password of another admin, print error message
            if(database[index].isAdmin)
            {
                red();
                printf("\nYou cannot change the password of other administrators.\n\n");
                reset();
            }
            else if(database[index].isRoot)
            {
                red();
                printf("\nYou cannot change the password of the Root user.\n\n");
                reset();
            }
            // the admin wishes to change a basic user's password
            else
            {
                printf("Please enter the new password: ");
                scanf(" %s", password);

                // check if the password is valid
                validate_password(password);
                // change the password if valid
                // print success or error message
            }
        }
    }
    else
    {
        red();
        printf("\nYou may not change the password of this user.\n\n");
        reset();
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
    return 0;
}