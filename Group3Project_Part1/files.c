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

void deleteDirectory(char folderName[])
{
    int isDeleted = rmdir(folderName);
    if(isDeleted == 0) // folder was successfully deleted
    {
        printf("\nFolder successfully deleted.\n");
    }
    else if(errno != EEXIST)
    {
        red();
        printf("\nFolder does not exist.\n");
        reset();
    }
    else
    {
        red();
        printf("\nError when deleting directory.\n");
        reset();
    }
}

void viewDirectory(char directoryName[]) 
//currently can only read files and subdirectories within the directory files.c is saved in 
{
    DIR *localFolder;
    struct dirent *files;

    localFolder = opendir(directoryName);
    if(localFolder == NULL)
    {
        red();
        printf("Directory read error\n");
        reset();
    }
    else
    {
        while ((files=readdir(localFolder)))
        {
            if(strcmp(files->d_name, ".") != 0 && strcmp(files->d_name, "..") != 0)
            {
                struct stat currentFile;
                stat(files->d_name, &currentFile);
                printf("%s", files->d_name);
                for(int i = 1; i <= 3-(files->d_namlen / 8); i++)
                {
                    printf("\t");
                }
                long sizeKB = round(currentFile.st_size / 1024.0);
                printf("\t%10ld KB\n", sizeKB);
            }
        }
    }
    
    closedir(localFolder);
}

char changeDirectory(char currentDir[], char argument[])
{
    printf("Current location: %s\n", currentDir);
    if(strcmp(argument, "~") == 0) //This will be the up directory argument, if anyone wants to change this, just swap out the ~ with the desired argument
    {
        int originalLength = strlen(currentDir); //gets the original length of the directory string
        char *revDir = malloc(originalLength); //creates a temporary copy of the directory, reverses it and stores it
        strcpy(revDir, currentDir);
        char *tempRevDir = strrev(revDir);
        char slash = '/'; //I just didn't want to look up the int represenation of /
        char *invLocation = strchr(revDir, slash); //finds the first instance of / in the string (which because it's reversed is acaully the last)
        char *output = NULL; //pointer for the ouput directory

        if(invLocation)
        {
            int location = invLocation - tempRevDir+1; //figures out the offset of the / in the string
            output = malloc(originalLength - location+1); //allocates the correct ammount of memory for the output
            memcpy(output, currentDir, originalLength - location); //makes a copy of the string from the current, not reversed, directory, going to the original lenght - location of hte character - 2 (2 was just always needed in my testing, and always worked)
        } 
        else
        {
            red();
            printf("Already in root directory\n");
            reset();
        }
        printf("New location: %s\n", output);
        return *output;
    }
    else if(strncmp(argument, "/", 1) == 0)
    {
        char *output;
        strcpy(output, currentDir);
        strcat(output, argument);
        
        printf("New location: %s\n", output);
        return *output;
    }
    else 
    {
        char *output = argument;
        printf("New location: %s\n", output);
        return *output;
    }
}