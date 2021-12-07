#include "commands.h"



int main()
{
    char userFile[] = "users.txt";
    userList = (User*)malloc(sizeof(User));
    numberofaccounts = load_all_accounts(userFile);
    login(userList, numberofaccounts);
    return 0;
}

void commandHandler(User user, User* userList, int numberofaccounts)
{
    time_t t;
    srand(time(&t));
    char line[MAX_LINE];
    char currentCommand[MAX_COMMAND];
    char arguments[MAX_COMMAND];
    char argument2[MAX_COMMAND];
    char argument3[MAX_COMMAND];
    char argument4[MAX_COMMAND];
    char argument5[MAX_COMMAND];
    char argument6[MAX_COMMAND];
    char argument7[MAX_COMMAND];
    char argument8[MAX_COMMAND];
    char argument9[MAX_COMMAND];
    char argument10[MAX_COMMAND];
    char argument11[MAX_COMMAND];
    char argument12[MAX_COMMAND];
    char argument13[MAX_COMMAND];
    char argument14[MAX_COMMAND];
    char argument15[MAX_COMMAND];
    char argument16[MAX_COMMAND];
    char argument17[MAX_COMMAND];
    char argument18[MAX_COMMAND];
    char argument19[MAX_COMMAND];
    struct PCB* readyQueueHead = setupPCB("readyHead", 0, 0);
    struct PCB* blockQueueHead = setupPCB("blockHead", 0, 0);
    struct PCB* suspendedReadyHead = setupPCB("susReadyHead", 0, 0);
    struct PCB* suspendedBlockHead = setupPCB("susBlockHead", 0, 0);
    printWelcome();
    int reenterOS = 0;
    while(1)
    {   
        // display terminal prompt
        green();
        printf("TechOS:");
        reset();
        blue();
        printf("> ");
        reset();
        fgets(line, MAX_LINE, stdin);
        sscanf(line, "%s %s %s %s %s %s", currentCommand, arguments, argument2, argument3, argument4);
        // command handler code
        if(strcmp(currentCommand,"help") == 0)
        {
            showFunctionHelp(arguments);
        }
        else if(strcmp(currentCommand,"version") == 0)
        {
            showVersion();
        }
        else if(strcmp(currentCommand,"display-time") == 0)
        {
            displayTime(arguments);
        }
        else if(strcmp(currentCommand,"change-date") == 0)
        {
            changeDate(arguments);
        }
        else if(strcmp(currentCommand,"display-date") == 0)
        {
            displayDate(arguments);
        }
        else if(strcmp(currentCommand, "suspend") == 0)
        {
            suspend(arguments, readyQueueHead, blockQueueHead, suspendedReadyHead, suspendedBlockHead);
        }
        else if(strcmp(currentCommand, "resume") == 0)
        {
            resume(arguments, readyQueueHead, blockQueueHead, suspendedReadyHead, suspendedBlockHead); 
        }
        else if(strcmp(currentCommand, "set-priority") == 0)
        {
            setPriority(arguments, argument2, readyQueueHead, blockQueueHead, suspendedReadyHead, suspendedBlockHead);
        }
        else if(strcmp(currentCommand, "show-pcb") == 0)
        {
            showPCB(arguments, readyQueueHead, blockQueueHead, suspendedReadyHead, suspendedBlockHead);
        }
        else if(strcmp(currentCommand, "show-ready-processes") == 0)
        {
            showQueuePCB(readyQueueHead);
        }
        else if(strcmp(currentCommand, "show-blocked-processes") == 0)
        {
            showQueuePCB(blockQueueHead);
        }
        else if(strcmp(currentCommand, "show-processes") == 0)
        {
            showAllPCB(readyQueueHead, blockQueueHead);
        }
        else if(strcmp(currentCommand, "load-process") == 0)
        {
            createPCB(arguments, argument2, argument3, argument4, readyQueueHead, blockQueueHead, suspendedReadyHead, suspendedBlockHead);
        }
        else if(strcmp(currentCommand, "dispatch") == 0)
        {
            dispatch(readyQueueHead, blockQueueHead, suspendedReadyHead, suspendedBlockHead);
        }
        else if(strcmp(currentCommand, "mkdir") == 0)
        {
            // create a one word name directory
            if(arguments[0] != '"' && argument2 == "") // will only create the one word directory if the input is really only one word
            {
                createDirectory(arguments);
            }
            // create a multiple word name directory
            // will only create if the name is enclosed in quotation marks.
            else if(arguments[0] == '"')
            {
                char fullName[MAX_LINE];
                char trimmedName[MAX_LINE];
                sprintf(fullName, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", arguments, argument2, argument3, argument4, argument5, argument6, argument7, argument8, argument9, argument10, argument11, argument12, argument13, argument14, argument15, argument16, argument17, argument18, argument19);
                int j = 0;
                int count = 0;
                int quotesClosed = 0;
                // trim the input for the create directory function
                for(int i = 0; i < strlen(fullName); i++)
                {
                    // if the character isn't a quotation mark
                    if(fullName[i] != '"')
                    {
                        trimmedName[j] = fullName[i]; // copy the character to the trimmed version
                        j++;
                        if(fullName[i] == '\0') // if we've reached the end of the input string, break out of the loop
                        {
                            break;
                        }
                    }
                    else
                    {
                        count++;
                        if(count == 2) // if two quotation marks have been found
                        {
                            quotesClosed = 1;
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
                // if the quotes are closed, then we can attempt to create the directory
                if(quotesClosed)
                {
                    createDirectory(trimmedName);
                }
                else
                {
                    red();
                    printf("\nFile names with spaces must be enclosed by quotation marks.\n");
                    reset();
                }
            }
            else
            {
                red();
                printf("\nMultiple word names for folders must be enclosed in quotation marks.\n");
                reset();
            }
        }
        else if(strcmp(currentCommand, "rmdir") == 0)
        {
            // this is functionally similar to createDirectory
            if(arguments[0] != '"' && argument2 != "") // will only delete the one word directory if the input is really only one word
            {
                deleteDirectory(arguments);
            }
            else if(arguments[0] == '"')
            {
                char fullName[MAX_LINE];
                char trimmedName[MAX_LINE];
                sprintf(fullName, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", arguments, argument2, argument3, argument4, argument5, argument6, argument7, argument8, argument9, argument10, argument11, argument12, argument13, argument14, argument15, argument16, argument17, argument18, argument19);
                int j = 0;
                int count = 0;
                int quotesClosed = 0;
                for(int i = 0; i < strlen(fullName); i++)
                {
                    if(fullName[i] != '"')
                    {
                        trimmedName[j] = fullName[i];
                        j++;
                        if(fullName[i] == '\0')
                        {
                            break;
                        }
                    }
                    else
                    {
                        count++;
                        if(count == 2)
                        {
                            quotesClosed = 1;
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
                if(quotesClosed)
                {
                    deleteDirectory(trimmedName);
                }
                else
                {
                    red();
                    printf("\nFile names with spaces must be enclosed by quotation marks.\n");
                    reset();
                }
            }
            else
            {
                red();
                printf("\nMultiple word names for folders must be enclosed in quotation marks.\n");
                reset();
            }
        }
        else if(strcmp(currentCommand, "view-dir") == 0)
        {
            if(strcmp(arguments, "") == 0)
            {
                viewDirectory(".");
            }
            else
            {
                if(arguments[0] != '"')
                {
                    viewDirectory(arguments);
                }
                else if(arguments[0] == '"')
                {
                    char fullName[MAX_LINE];
                    char trimmedName[MAX_LINE];
                    sprintf(fullName, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", arguments, argument2, argument3, argument4, argument5, argument6, argument7, argument8, argument9, argument10, argument11, argument12, argument13, argument14, argument15, argument16, argument17, argument18, argument19);
                    int j = 0;
                    int count = 0;
                    for(int i = 0; i < strlen(fullName); i++)
                    {
                        if(fullName[i] != '"')
                        {
                            trimmedName[j] = fullName[i];
                            j++;
                            if(fullName[i] == '\0')
                            {
                                break;
                            }
                        }
                        else
                        {
                            count++;
                            if(count == 2)
                            {
                                break;
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }
                    viewDirectory(trimmedName);
                }
            }
        }
        else if(strcmp(currentCommand, "change-dir") == 0)
        {
            if(arguments[0] != '"')
            {
                changeDirectory(arguments);
            }
            else if(arguments[0] == '"')
            {
                char fullName[MAX_LINE];
                char trimmedName[MAX_LINE];
                sprintf(fullName, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", arguments, argument2, argument3, argument4, argument5, argument6, argument7, argument8, argument9, argument10, argument11, argument12, argument13, argument14, argument15, argument16, argument17, argument18, argument19);
                int j = 0;
                int count = 0;
                for(int i = 0; i < strlen(fullName); i++)
                {
                    if(fullName[i] != '"')
                    {
                        trimmedName[j] = fullName[i];
                        j++;
                        if(fullName[i] == '\0')
                        {
                            break;
                        }
                    }
                    else
                    {
                        count++;
                        if(count == 2)
                        {
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
                changeDirectory(trimmedName);
            }
            else
            {
                printf("\nMultiple word names for folders must be enclosed in quotation marks.\n");
            }
        }
        else if(strcmp(currentCommand, "createf") == 0)
        {
            if(arguments[0] != '"')
            {
                createFile(arguments);
            }
            else if(arguments[0] == '"')
            {
                char fullName[MAX_LINE];
                char trimmedName[MAX_LINE];
                sprintf(fullName, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", arguments, argument2, argument3, argument4, argument5, argument6, argument7, argument8, argument9, argument10, argument11, argument12, argument13, argument14, argument15, argument16, argument17, argument18, argument19);
                int j = 0;
                int count = 0;
                for(int i = 0; i < strlen(fullName); i++)
                {
                    if(fullName[i] != '"')
                    {
                        trimmedName[j] = fullName[i];
                        j++;
                        if(fullName[i] == '\0')
                        {
                            break;
                        }
                    }
                    else
                    {
                        count++;
                        if(count == 2)
                        {
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
                createFile(trimmedName);
            }
            else
            {
                printf("\nMultiple word names for folders must be enclosed in quotation marks.\n");
            }
        }
        else if(strcmp(currentCommand, "deletef") == 0)
        {
            if(arguments[0] != '"')
            {
                removeFile(arguments);
            }
            else if(arguments[0] == '"')
            {
                char fullName[MAX_LINE];
                char trimmedName[MAX_LINE];
                sprintf(fullName, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", arguments, argument2, argument3, argument4, argument5, argument6, argument7, argument8, argument9, argument10, argument11, argument12, argument13, argument14, argument15, argument16, argument17, argument18, argument19);
                int j = 0;
                int count = 0;
                for(int i = 0; i < strlen(fullName); i++)
                {
                    if(fullName[i] != '"')
                    {
                        trimmedName[j] = fullName[i];
                        j++;
                        if(fullName[i] == '\0')
                        {
                            break;
                        }
                    }
                    else
                    {
                        count++;
                        if(count == 2)
                        {
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
                removeFile(trimmedName);
            }
            else
            {
                printf("\nMultiple word names for folders must be enclosed in quotation marks.\n");
            }
        }
        else if(strcmp(currentCommand, "createu") == 0) //Unable to finish implementation, took too long writing the functions
        { 
            char uname[MAX_USERNAME];
            for(int i = 0; i < MAX_USERNAME; i++)
            {
                uname[i] = user.username[i];
            }
            if(checkUserAdmin(userList, uname)) //Will need to change when we have admin permissions using checkUserAdmin(User* database, char username[])
            {      
                addNewUser(numberofaccounts, "users.txt");
                numberofaccounts++;
            }
            else 
            {
                red();
                printf("Must have admin permissions to perform this action\n");
                reset();
            }
        }
        else if(strcmp(currentCommand, "deleteu") == 0)
        {
            //see above command for similar layout to delete user rules
            char uname[MAX_USERNAME];
            for(int i = 0; i < MAX_USERNAME; i++)
            {
                uname[i] = user.username[i];
            }
            if(checkUserAdmin(userList, uname))
            {
                if(deleteUser(numberofaccounts, "users.txt", user.isRoot) == 1)
                {
                    printf("User removed.\n");
                }
                else
                {
                    printf("User not removed\n");
                }
                
            }
            else
            {
                red();
                printf("Must have admin permissions to perform this action\n");
                reset();
            }
        }
        else if(strcmp(currentCommand, "changepass") == 0)
        {
            changePassword(userList, user);
        }
        else if(strcmp(currentCommand, "setadmin") == 0)
        {
            makeAdmin(userList, user);
        }
        else if(strcmp(currentCommand, "remadmin") == 0)
        {
            removeAdmin(userList, user);
        }
        else if(strcmp(currentCommand, "logout") == 0)
        {
            fflush(stdin);
            reenterOS = 1;
            break;
        }
        else if(strcmp(currentCommand,"exit") == 0)
        {
            // confirm that the user wishes to exit
            printf("\nAre you sure you want to exit (y/n)?\n");
            char answer = getchar();

            if(answer == 'y' || answer == 'Y')
            {
                fflush(stdin);
                printf("\nThank you for using TechOS\n");
                break;
                blue();
                printf("If the program gets here contact support at 111 111 111111111111111111111111111111111\n\n\n\n\n\n\n\n\n");
                reset();
            }
            else
            {
                fflush(stdin);
            }
                      
        }
        // if an invalid command is entered
        else
        {
            red();
            printf("Invalid command entered\n");
            reset();
        }

        strcpy(currentCommand, "");
        strcpy(arguments, "");
        strcpy(argument2, "");
        strcpy(argument3, "");
        strcpy(argument4, "");
        strcpy(argument5, "");
        strcpy(argument6, "");
        strcpy(argument7, "");
        strcpy(argument8, "");
        strcpy(argument9, "");
        strcpy(argument10, "");
        strcpy(argument11, "");
        strcpy(argument12, "");
        strcpy(argument13, "");
        strcpy(argument14, "");
        strcpy(argument15, "");
        strcpy(argument16, "");
        strcpy(argument17, "");
        strcpy(argument18, "");
        strcpy(argument19, "");
    }
    if(reenterOS)
    {
        login(userList, numberofaccounts);
    }
}