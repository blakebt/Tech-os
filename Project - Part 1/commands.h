#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

#define MAX_LINE 128
#define MAX_COMMAND 64

#include <stdio.h>
#include <string.h>
#include <time.h>


void printWelcome();
void printHelpMenu();
void showVersion();
void displayTime(char* arguments);
void commandHandler();
void red();
void blue();
void green();
void reset();
void changeDate(char* arguments);
void displayDate(char* arguments);



#endif

