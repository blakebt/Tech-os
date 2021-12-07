#include "commands.h"

//make sure to increment the number of users after running this program
void addNewUser(User *allUsers, int numUsers, char *fileLocation)
{
    //Gets username
    printf("Please enter a unique user name, keep name shorter than %d characters:\n", MAX_USERNAME);
    char username[MAX_USERNAME];
    scanf("%[^\n]%*c", username);
    while(checkValidName(allUsers, username)== 0)
    {
        red();
        printf("Invalid user name, the name must be unique and not include \"|\"\n");
        reset();
        scanf("%[^\n]%*c", username);
    }
    //Gets password
    printf("Please select a password\nIt must be between 8 and %d characters long, with at least one of each of the following:\n An upper case letter\n A lower case letter\n A number\n A special character");
    char password[MAX_PASSWORD];
    scanf("%[^\n]%*c", password);
    while(validate_password(password) == 0)
    {
        red();
        printf("Password failed to meet the above criteria\n");
        reset();
        scanf("%[^\n]%*c", username);
    }
    User newUser = initializeUser(username, password);
    //Adds newUser to the array of all users, then outputs it to the user file
    allUsers = realloc(allUsers, (numUsers+1)*sizeof(User));
    allUsers[numUsers] = newUser;
    accounts2file(numUsers+1, allUsers, fileLocation);
}

//removes user from the array, make sure to dencrement the number of users if the function returns 1, otherwise if 0 nothing happened 
int deleteUser(User *allUsers, int numUsers, char *fileLocation, int callerIsRoot)
{
    printf("Enter the name to remove\n");
    char deleteName[MAX_USERNAME];
    scanf("%[^\n]%*c", deleteName);
    if(checkUserExists(allUsers, deleteName))
    {
        for(int i = 0; i < MAX_USERS; i++)
        {
            if(strcmp(deleteName, allUsers[i].username) == 0 && allUsers[i].isRoot == 0)
            {
                if(allUsers[i].isAdmin == 0 || callerIsRoot == 1)
                {
                    //what follows is a work of insanity, we realloc the allUsers array to one less than the old number of users, read to file to this 
                    //array, ignoring the name that matches the user, then print out the new array back to the file
                    printf("User found, do you wish to continue? y/n:");
                    char answer;
                    scanf("%c", &answer);
                    if(answer == 'y')
                    {
                        //reallocates the proportionally less memory 
                        allUsers = realloc(allUsers, (numUsers-1)*sizeof(User));
                        //reads all but the name to be removed to the array
                        FILE *fi;
                        fi = fopen(fileLocation, "r");
                        int currentRead = 0;
                        if(fi != NULL)
                        {
                            char command[10000];
                            char uname[10000];
                            char pswd[10000];
                            int root;
                            int admin;
                            int eoftest;
                            while(fgets(command, 10000, fi))
                            {
                                int round = 0;
                                int lastIdx = 0;
                                for(int i = 0; i < strlen(command); i++)
                                {
                                    if(command[i] == '|')
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
                                if(strcmp(deleteName, uname))
                                {
                                    strcpy(allUsers[currentRead].username, uname);
                                    strcpy(allUsers[currentRead].password, pswd);
                                    allUsers[currentRead].isAdmin = admin;
                                    allUsers[currentRead].isRoot = root;
                                    allUsers[currentRead].lineNumber = currentRead;
                                    currentRead++;
                                }
                            }
                        }
                        fclose(fi);
                        //prints out the new list of users
                        accounts2file(numUsers-1, allUsers, fileLocation);
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    red();
                    printf("Only the root account can remove admin accounts\n");
                    reset();
                    return 0;
                }
            }
            else if(allUsers[i].isRoot == 1)
            {
                red();
                printf("Cannot remove root user\n");
                reset();
                return 0;
            }
        }
    }
    else
    {
        red();
        printf("User does not exist\n");
        reset();
        return 0;
    }
}