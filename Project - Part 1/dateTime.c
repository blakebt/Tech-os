#include "commands.h"

//this function will require an argument in the form MM-DD-YYYY, EX "changeDate 11 20, 2013" would change the date to November 20, 2013
void changeDate(char* arguments)
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
        printf("Invalid date argument, please enter in format \"mm-dd-yyyy\"\nUse valid dates only\n");
    }
}
