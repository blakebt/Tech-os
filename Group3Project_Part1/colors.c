#include "commands.h"

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
