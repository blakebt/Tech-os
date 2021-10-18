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
    char argument4[MAX_COMMAND];
    struct PCB* readyQueueHead = setupPCB("readyHead", 0, 0);
    struct PCB* blockQueueHead = setupPCB("blockHead", 0, 0);
    struct PCB* suspendedReadyHead = setupPCB("susReadyHead", 0, 0);
    struct PCB* suspendedBlockHead = setupPCB("susBlockHead", 0, 0);
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

        strcpy(currentCommand, "");
        strcpy(arguments, "");
        strcpy(argument2, "");
        strcpy(argument3, "");
        strcpy(argument4, "");
    }
}