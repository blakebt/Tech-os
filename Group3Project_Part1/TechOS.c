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
        sscanf(line, "%s %s", currentCommand, arguments);


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
            struct PCB* toSuspend = findPcb(arguments, readyQueueHead, blockQueueHead);
            if(toSuspend != NULL)
            {
                if(toSuspend->p_state == 1)
                {
                    toSuspend->isSuspended = 1;
                    enqueue(&suspendedReadyHead, &toSuspend);
                }
                else if(toSuspend->p_state == 2)
                {
                    toSuspend->isSuspended = 1;
                    enqueue(&suspendedBlockHead, &toSuspend);
                }
            }
            else
            {
                red();
                printf("Currently no queued process by that name\n");
                reset();
            }
        }
        else if(strcmp(currentCommand, "resume") == 0)
        {
            struct PCB* unsuspend = findPcb(arguments, suspendedReadyHead, suspendedBlockHead);
            if(unsuspend != NULL)
            {
                if(unsuspend->p_state ==1)
                {
                    unsuspend->isSuspended = 0;
                    enqueuePriority(&readyQueueHead, &unsuspend);
                }
                else if(unsuspend->p_state ==2)
                {
                    unsuspend->isSuspended = 0;
                    enqueue(&blockQueueHead, &unsuspend);
                }
            }
            else
            {
                red();
                printf("Currenlty no suspended process by that name\n");
                reset();
            }
        }
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
