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