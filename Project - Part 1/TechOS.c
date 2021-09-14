#include "commands.h"

int main()
{
    commandHandler();
    return 0;
}

void commandHandler()
{
    char line[128];
    char currentCommand[64];
    char arguments[64];
    printWelcome();

    while(1)
    {
        green();
        printf("TechOS:");
        reset();
        blue();
        printf("~");
        reset();
        printf("$ ");
        fgets(line, 128, stdin);
        sscanf(line, "%s %s", currentCommand, arguments);

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
        else if(strcmp(currentCommand,"display-date") == 0)
        {
            displayDate();
        }
        else if(strcmp(currentCommand, "change-date") == 0)
        {
            changeDate(arguments);
        }
        else if(strcmp(currentCommand,"exit") == 0)
        {
            printf("\nAre you sure you want to exit(y/n)?\n");
            char answer = getchar();

            if(answer == 'y' || answer == 'Y')
            {
                printf("Thank you for using TechOS\n");
                break;
            }
            
            fflush(stdin);          
        }
        else
        {
            red();
            printf("Invalid command entered\n");
            reset();
        }
    }
}
void printWelcome()
{
    printf("            Welcome to TechOS.\n");
    printf("Begin entering commands whenever you're ready.\n");
    printf("If you would like a list of commands, type help.\n\n");
}
void printHelpMenu()
{
    FILE *fp;

    fp = fopen("commands.txt","r");

    if(fp != NULL)
    {
        printf("\nAvailable commands:\n");
        printf("-------------------\n");
        char command[128];
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
}

void showVersion()
{
    FILE *fp;

    fp = fopen("version.txt", "r");
    char line[128];
    if(fp != NULL)
    {
        while(!feof(fp))
        {
            fscanf(fp, "%[^,] %s", line);
            printf("%s", line);
        } 
    }
    printf("\n");
    fclose(fp);
}

void displayTime(char* arguments)
{
    time_t rawTime;
    struct tm* timeInfo;

    time(&rawTime);
    timeInfo = localtime (&rawTime);

    if(strcmp(arguments,"help") == 0)
    {
        blue();
        printf("display-time ");
        reset();
        printf("gives the time in 24hr format by default.\nUse the argument '12' to display in 12hr format.\n");
    }
    else if(strcmp(arguments,"12") == 0 && timeInfo->tm_hour > 12)
    {
        timeInfo->tm_hour = timeInfo->tm_hour - 12;
        printf("The current time is: %d:%d:%d\n", timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
    }
    else
    {
        printf("The current time is: %d:%d:%d\n", timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
    }

}
void red()
{
    printf("\033[1;31m");
}

void blue()
{
    printf("\033[0;34m");
}

void green()
{
    printf("\033[0;32m");
}

void reset()
{
    printf("\033[0m");
}
