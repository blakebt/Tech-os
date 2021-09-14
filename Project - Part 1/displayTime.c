#include "commands.h"

void displayTime(char* arguments)
{
    time_t rawTime;
    struct tm* timeInfo;

    time(&rawTime);
    timeInfo = localtime (&rawTime);

    if(strcmp(arguments,"help") == 0)
    {
        printf("\nThe display-time command gives the time in 24hr format by default.\nUse the argument '12' to display in 12hr format.\n");
        printf("\nExample format: display-time 12\n\n");
    }
    else if(strcmp(arguments,"12") == 0 && timeInfo->tm_hour > 12)
    {
        timeInfo->tm_hour = timeInfo->tm_hour - 12;
        printf("The current time is: %d:%d:%d\n", timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
    }
    else if(strcmp(arguments,"12") != 0)
    {
        red();
        printf("Invalid argument(s) for display-time command\n");
        reset();
    }
    else
    {
        printf("The current time is: %d:%d:%d\n", timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);
    }

}