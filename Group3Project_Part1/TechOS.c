#include "commands.h"

int main()
{
    commandHandler();
    return 0;
}

void commandHandler()
{
    char line[MAX_LINE];
    char currentCommand[MAX_COMMAND];
    char arguments[MAX_COMMAND];
    char argument2[MAX_COMMAND];
    char argument3[MAX_COMMAND];
    struct PCB* readyQueueHead = NULL;
    struct PCB* blockQueueHead = NULL;
    struct PCB* suspendedReadyHead = NULL;
    struct PCB* suspendedBlockHead = NULL;
    printWelcome();

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
        sscanf(line, "%s %s %s %s", currentCommand, arguments, argument2, argument3);


        // command handler code
        if(strcmp(currentCommand,"help") == 0)
        {
            printHelpMenu();
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
        //The following until the next lone line coment are only temporary
        else if(strcmp(currentCommand, "create-pcb") == 0) 
        {
            createPCB(arguments, argument2, argument3, readyQueueHead, blockQueueHead, suspendedReadyHead, suspendedBlockHead);
        }
        else if(strcmp(arguments, "delete-pcb") == 0)
        {
            deletePCB(arguments, readyQueueHead, blockQueueHead, suspendedReadyHead, suspendedBlockHead);
        }
        else if(strcmp(currentCommand, "block-pcb") == 0)
        {
            blockPCB(arguments, readyQueueHead, suspendedReadyHead, blockQueueHead, suspendedBlockHead);
        }
        else if(strcmp(currentCommand, "unblock-pcb") == 0)
        {
            unblockPCB(arguments, readyQueueHead, suspendedReadyHead, blockQueueHead, suspendedBlockHead);
        }
        //end of the temporary commands
        else if(strcmp(currentCommand,"exit") == 0)
        {
            // confirm that the user wishes to exit
            printf("\nAre you sure you want to exit (y/n)?\n");
            char answer = getchar();

            if(answer == 'y' || answer == 'Y')
            {
                printf("\nThank you for using TechOS\n");
                break;
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
    }
}

// function to print the welcome message
void printWelcome()
{
    printf("            Welcome to TechOS.\n");
    printf("Begin entering commands whenever you're ready.\n");
    printf("If you would like a list of commands, type help.\n\n");
}

// function to print the list of commands
void printHelpMenu()
{
    FILE *fp;

    fp = fopen("commands.txt","r");

    if(fp != NULL)
    {
        printf("\nAvailable commands:\n");
        printf("-------------------\n");
        char command[MAX_COMMAND];
        while(!feof(fp))
        {
            fscanf(fp,"%[^,] %s", command);
            printf(" %s\n", command);
        }
        printf("\n");
    }
    else
    {
        printf("ERROR. Input file is missing");
    }

    fclose(fp);
}

// function to print the version information
void showVersion()
{
    FILE *fp;

    fp = fopen("version.txt", "r");
    char line[128];
    if(fp != NULL)
    {
        printf("\n");
        while(!feof(fp))
        {
            fscanf(fp, "%[^,] %s", line);
            printf("%s", line);
        } 
    }
    printf("\n\n");
    fclose(fp);
}
