#include "commands.h"

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
