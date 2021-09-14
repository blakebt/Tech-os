#include "commands.h"

void displayDate()
{
    time_t timeData;
    struct tm *currentDate;
    //struct tm *changedDate;
    char dayOfWeek[10], day[3], month[10], year[5], changedDate[26];
    int changedMonth, changedDay, changedYear;
    int actualMonth, actualDay, actualYear;
    FILE* fPtr;

    if(fPtr = fopen("sysDate.txt","r"))
    {
        fgets(changedDate, 26, fPtr);
        fscanf(changedDate, "%d %d %d %d %d %d", &changedMonth, &changedDay, &changedYear, &actualMonth, &actualDay, &actualYear);

        currentDate->tm_mon = (currentDate->tm_mon - actualMonth) + changedMonth;
        currentDate->tm_mday = (currentDate->tm_mday - actualDay) + changedDay;
        currentDate->tm_year = (currentDate->tm_year - actualYear) + changedYear;

        strftime(dayOfWeek, 10, "%A", currentDate->tm_wday);
        strftime(month, 10, "%B", currentDate->tm_mon);
        strftime(day, 3, "%d", currentDate->tm_mday);
        strftime(year, 5, "%Y", currentDate->tm_year);

        if(currentDate->tm_mon > 11)
        {
            currentDate->tm_year += 1;
            currentDate->tm_mon -= 12;
        }

        switch(currentDate->tm_mon)
        {
            case 0:
            case 2:
            case 4:
            case 6:
            case 7:
            case 9:
            case 11:
                if(currentDate->tm_mday > 31)
                {
                    currentDate->tm_mon += 1;
                    currentDate->tm_mday -= 31;
                }
                break;
            case 3:
            case 5:
            case 8:
            case 10:
                if(currentDate->tm_mday > 30)
                {
                    currentDate->tm_mon += 1;
                    currentDate->tm_mday -= 30;
                }
                break;
            case 1:
                if((((changedYear % 4) == 0 ) && !((changedYear % 100) == 0)) || ((changedYear % 400) == 0))
                {
                    if(currentDate->tm_mday > 29)
                    {
                        currentDate->tm_mon += 1;
                        currentDate->tm_mday -= 29; 
                    }
                }
                else
                {
                    if(currentDate->tm_mday > 28)
                    {
                        currentDate->tm_mon += 1;
                        currentDate->tm_mday -= 28;
                    }
                }
            default:
                //if it gets here, then the entered month is invalid
        }

    }
    else
    {
        time(&timeData);
        currentDate = localtime(&timeData);

        strftime(dayOfWeek, 10, "%A", currentDate);
        strftime(month, 10, "%B", currentDate);
        strftime(day, 3, "%d", currentDate);
        strftime(year, 5, "%Y", currentDate);
    }
    printf("%s %s %s, %s\n", dayOfWeek, day, month, year);
}
