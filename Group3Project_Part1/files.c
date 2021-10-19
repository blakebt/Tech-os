#include "commands.h"

void createDirectory(char folderName[])
{
    int isCreated = mkdir(folderName);
    if(isCreated == 0) // directory was successfully created
    {
        printf("\nFolder successfully created.\n");
    }
    else if(errno == EEXIST)
    {
        red();
        printf("\nDirectory already exists.\n");
        reset();
    }
    else
    {
        red();
        printf("\nError when creating directory.\n");
        reset();
    }
}