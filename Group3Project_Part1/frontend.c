/*
File for all front end functions
*/

#include "commands.h"

//this function will require an argument in the form MM-DD-YYYY, EX "changeDate 11 20, 2013" would change the date to November 20, 2013
void changeDate(char* arguments)
{
    if(strcmp(arguments,"help") == 0)
    {
        printf("\nThe change-date command allows the user to change the current system date.\n");
        printf("The desired date must be entered in-line with the command in MM-DD-YYYY format.\n");
        printf("\nExample format: change-date 12-12-2021\n\n");
    }
    else
    {
        time_t rawTime;
        time(&rawTime);
        struct tm* sysTime = localtime(&rawTime);
        struct tm* locTime = gmtime(&rawTime);
        int inputMon, inputYear;
        sscanf(arguments, "%d-%d-%d", &inputMon, &sysTime->tm_mday, &inputYear); //If we decide that the argument needs to a continuous string, we can replace the spaces with - or _
        int valid = 1;
        inputMon--;
        if(inputYear < 1900) //unable to take a year prior to 1900
        {
            valid = 0;
        }
        else
        {
            switch(inputMon) //ensures the correct number of days in a given month
                {
                    case 0:
                    case 2:
                    case 4:
                    case 6:
                    case 7:
                    case 9:
                    case 11:
                        if(sysTime->tm_mday <= 0 || sysTime->tm_mday > 31)
                            valid = 0;
                        break;
                    case 3:
                    case 5:
                    case 8:
                    case 10:
                        if(sysTime->tm_mday <= 0 || sysTime->tm_mday > 30)
                            valid = 0;
                        break;
                    case 1:
                        if((((inputYear % 4) == 0 ) && !((inputYear % 100) == 0)) || ((inputYear % 400) == 0))
                        {
                            if(sysTime->tm_mday <= 0 || sysTime->tm_mday > 29)
                                valid = 0;
                        }
                        else
                        {
                            if(sysTime->tm_mday <= 0 || sysTime->tm_mday > 28)
                                valid = 0;
                        }
                        break;
                    default:
                        valid = 0; //if it gets here, then the entered month is invalid
                }
        }

        if(valid == 1)
        {
        sysTime->tm_mon = inputMon;
            sysTime->tm_year = inputYear - 1900;
            printf("The date has been changed to %d/%d/%d\n", sysTime->tm_mon + 1, sysTime->tm_mday, sysTime->tm_year + 1900);

            //from here, this is where the date change will be saved to a text file so that it can be read in the future
            FILE* sysDate;
            sysDate = fopen("sysDate.txt", "w");
            /*note that the format is M D Y based on the values of the structure with the first 3 being the new date on the day it was set, and the second 3 being the system time on the day it was set,
            you can take this system time and subtract it from the current system time to get the number of days that has passed */
            fprintf(sysDate, "%d %d %d %d %d %d", sysTime->tm_mon + 1, sysTime->tm_mday, sysTime->tm_year + 1900, locTime->tm_mon + 1, locTime->tm_mday, locTime->tm_year + 1900);
            fclose(sysDate);
        }
        else
        {
            red();
            printf("Invalid date argument, please enter in format \"mm-dd-yyyy\"\nUse valid dates only\n");
            reset();
        }
        }
}

// function to display time in either 12 hour format or 24 hour format
void displayTime(char* arguments)
{
    time_t rawTime;
    struct tm* timeInfo;

    time(&rawTime);
    timeInfo = localtime (&rawTime);

    if(strcmp(arguments,"12") == 0 && timeInfo->tm_hour > 12)
    {
        timeInfo->tm_hour = timeInfo->tm_hour - 12;
        printf("The current time is: %d:%d:%d\n", timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
    }
    else
    {
        printf("The current time is: %d:%d:%d\n", timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
    }

}

//function to display the current date
void displayDate(char* arguments)
{
    time_t timeData;
    time(&timeData);
    struct tm* currentDate;
    currentDate = localtime(&timeData);
    // struct tm* changedDate;
    char dayOfWeek[10], day[3], month[10], year[5], changedDate[26];
    int changedMonth, changedDay, changedYear;
    int actualMonth, actualDay, actualYear;
    FILE* fPtr;

    if(strcmp(arguments, "help") == 0)
    {
        printf("\nThe display-date command displays the current system time in MM-DD-YYYY format\n");
        printf("\nExample format: display-date\n\n");
    }
    else
    {
        if(fPtr = fopen("sysDate.txt","r"))
        {
            fgets(changedDate, 26, fPtr);
            sscanf(changedDate, "%d %d %d %d %d %d", &changedMonth, &changedDay, &changedYear, &actualMonth, &actualDay, &actualYear);

            currentDate->tm_mon = actualMonth - 1;
            currentDate->tm_mday = actualDay;
            currentDate->tm_year = actualYear - 1900;

            strftime(month, 10,"%B", currentDate);
            strftime(day, 3, "%d", currentDate);
            strftime(year ,5, "%Y", currentDate);
        }
        else
        {
            strftime(month, 10, "%B", currentDate);
            strftime(day, 3, "%d", currentDate);
            strftime(year, 5, "%Y", currentDate);
        }
        printf("The current date is: %s %s, %s\n", month,day,year);
    }
}

// functions for changing the color of text in the system
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

// function to print the welcome message
void printWelcome()
{
    printf("\n");
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

// function to handle help functionality for all commands
void showFunctionHelp(char* arguments)
{
    if(strcmp(arguments, "version") == 0)
    {
        blue();
        printf("\nversion ");
        reset();
        printf("displays the current version of TechOS.\n\n");
        printf("Example of command:\n");
        printf("version\n\n");
    }
    else if(strcmp(arguments, "display-date") == 0)
    {
        blue();
        printf("\ndisplay-date ");
        reset();
        printf("displays the current date in MM-DD-YYYY formt.\n\n");
        printf("Example of command:\n");
        printf("display-date\n\n");
    }
    else if(strcmp(arguments, "change-date") == 0)
    {
        blue();
        printf("\nchange-date ");
        reset();
        printf("allows for the system date to be changed.\n New date must be entered in MM-DD-YYYY format\n\n");
        printf("Example of command:\n");
        printf("change-date MM-DD-YYYY\n\n");
    }
    else if(strcmp(arguments, "display-time") == 0)
    {
        blue();
        printf("\ndisplay-time ");
        reset();
        printf("displays the current system time in 12 hour or 24 hour format.\n Enter 12 as the argument to recieve the time in 12 hour format.\n\n");
        printf("Example of command:\n");
        printf("display-time 12\n\n");
    }
    else if(strcmp(arguments, "suspend") == 0)
    {
        blue();
        printf("\nsuspend ");
        reset();
        printf("will suspend a process and insert the process into the suspended ready queue or suspended block queue depending on it's blocked status.\n\n");
        printf("Example of command:\n");
        printf("suspend [process name]\n\n");
    }
    else if(strcmp(arguments, "resume") == 0)
    {
        blue();
        printf("\nresume ");
        reset();
        printf("will resume a suspended process, remove the process from the suspened ready/block queue, and insert the process into it's respective queue.\n\n");
        printf("Example of command:\n");
        printf("resume [process name]\n\n");
    }
    else if(strcmp(arguments, "set-priority") == 0)
    {
        blue();
        printf("\nset-priority ");
        reset();
        printf("will set the priority of a process to the provided priority.\n\n");
        printf("Example of command:\n");
        printf("set-priority [process name] [new priority]\n\n");
    }
    else if(strcmp(arguments, "show-pcb") == 0)
    {
        blue();
        printf("\nshow-pcb ");
        reset();
        printf("shows the status information about the chosen process.\n\n");
        printf("Example of command:\n");
        printf("show-pcb [process name]\n\n");
    }
    else if(strcmp(arguments, "show-ready-processes") == 0)
    {
        blue();
        printf("\nshow-ready-processes ");
        reset();
        printf("shows all the processes in the ready queue.\n\n");
        printf("Example of command:\n");
        printf("show-ready-processes\n\n");
    }
    else if(strcmp(arguments, "show-blocked-processes") == 0)
    {
        blue();
        printf("\nshow-blocked-processes ");
        reset();
        printf("shows ll the processes in the blocked queue.\n\n");
        printf("Example of command:\n");
        printf("show-blocked-processes\n\n");
    }
    else if(strcmp(arguments, "load-process") == 0)
    {
        blue();
        printf("\nload-process ");
        reset();
        printf("loads a process into the ready queue.\n\n");
        printf("Example of command:\n");
        printf("load-process [name] [class] [priority] [file path]\n\n");
    }
    else if(strcmp(arguments, "dispatch") == 0)
    {
        blue();
        printf("\ndispatch ");
        reset();
        printf("begins execution of processes in the queues.\n\n");
        printf("Example of command:\n");
        printf("dispatch\n\n");
    }
    else if(strcmp(arguments, "createf") == 0)
    {
        blue();
        printf("\ncreatef ");
        reset();
        printf("creates a file in current directory or in specified directory.\n\n");
        printf("Example of command:\n");
        printf("createf [file name]  or  createf [./directory name/file name]\n\n");
    }
    else if(strcmp(arguments, "deletef") == 0)
    {
        blue();
        printf("\ndeletef ");
        reset();
        printf("removes file from system.\n\n");
        printf("Example of command:\n");
        printf("deletef [file name]  or  deletef [./directory name/file name]\n\n");
    }
    else if(strcmp(arguments, "view-dir") == 0)
    {
        blue();
        printf("\nview-dir ");
        reset();
        printf("shows files in the current directory or specified directory\n\n");
        printf("Example of command:\n");
        printf("view-dir [directory path]\n\n");
    }
    else if(strcmp(arguments, "change-dir") == 0)
    {
        blue();
        printf("\nchange-dir ");
        reset();
        printf("changes the current directory using a full path, relative path, or use '~' to go up a directory\n\n");
        printf("Example of command:\n");
        printf("change-dir [directory path]\n\n");
    }
    else if(strcmp(arguments, "createu") == 0)
    {
        blue();
        printf("\ncreateu ");
        reset();
        printf("Adds new user to the system. Only the root admin and admins can create users.\n\n");
        printf("Example of command:\n");
        printf("createu\n\n");
    }
    else if(strcmp(arguments, "deleteu") == 0)
    {
        blue();
        printf("\ndeleteu ");
        reset();
        printf("Removes user from the system. Only the root admin and admins can basic users. Only root admin can remove admins.\n\n");
        printf("Example of command:\n");
        printf("deleteu\n\n");
    }
    else
    {
        printHelpMenu();
    }
}