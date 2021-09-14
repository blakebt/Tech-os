#include <time.h>
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
        else if(strcmp(currentCommand,"change-date") == 0)
        {
            changeDate(arguments);
        }
        else if(strcmp(currentCommand,"display-date") == 0)
        {
            displayDate();
        }
        else if(strcmp(currentCommand,"exit") == 0)
        {
            printf("\nAre you sure you want to exit(y/n)?\n");
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
