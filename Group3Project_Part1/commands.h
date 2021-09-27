#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

#define MAX_LINE 128
#define MAX_COMMAND 64
#define MAX_PNAME 50

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

struct PCB
{
    char p_name[MAX_PNAME];
    int p_class; //0 = application, 1 = system
    int p_priority; // 0-9
    int p_state; //0 = running, 1 = ready, 2 = blocked
    int isSuspended; // 0 = not suspended, 1 = suspended
    struct PCB* next;
};

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
struct PCB* allocatePCB();
int freePCB(struct PCB* process);
struct PCB* setupPCB(char* name, int class, int priority);
void enqueue(struct PCB** head, struct PCB** pcb);
void enqueuePriority(struct PCB** head, struct PCB** PCB);
struct PCB* dequeue(struct PCB** head);
//From Ppcb.c
struct PCB* allocatePCB();
int freePcb(struct PCB* process);
struct PCB* setupPcb(char* name, int class, int priority);
struct PCB* findPcb(char pName[MAX_PNAME], struct PCB* readyHead, struct PCB* blockHead);
void insertPcb(struct PCB* toIn, struct PCB* readyHead, struct PCB* blockHead);
int removePcb(struct PCB* toPull, struct PCB* readyHead, struct PCB* blockHead);



#endif

