#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <time.h>


void changeDate(char arguments[]);
void displayDate();
void printWelcome();
void printHelpMenu();
void showVersion();
void displayTime(char* arguments);
void commandHandler();
void red();
void blue();
void green();
void reset();


#endif

