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
    char p_data[MAX_LINE];//Holds path and offset
    int p_class; //0 = application, 1 = system
    int p_priority; // 0-9
    int p_state; //0 = running, 1 = ready, 2 = blocked
    int isSuspended; // 0 = not suspended, 1 = suspended
    char p_path[MAX_LINE]; // file path for the process
    int offset; // offset for the process
    struct PCB* next;
};

void printWelcome();
void printHelpMenu();
void showFunctionHelp(char* arguments);
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
void suspend(char arguments[MAX_COMMAND], struct PCB* readyQueueHead, struct PCB* blockQueueHead, struct PCB* suspendReadyHead, struct PCB* suspendBlockHead);
void resume(char arguments[MAX_COMMAND], struct PCB* readyQueueHead, struct PCB* blockQueueHead, struct PCB* suspendedReadyHead, struct PCB* suspendedBlockHead);
void setPriority(char name[MAX_COMMAND], char priority[MAX_COMMAND], struct PCB* readyQueue, struct PCB* blockQueue, struct PCB* readySuspend, struct PCB* blockSuspend);
void showPCB(char name[MAX_COMMAND], struct PCB* readyQueue, struct PCB* blockQueue, struct PCB* readySuspend, struct PCB* blockSuspend);
void showQueuePCB(struct PCB* head);
void showAllPCB(struct PCB* readyHead, struct PCB* blockHead);
void createPCB(char arguments[], char argument2[], char argument3[], struct PCB* readyQueueHead, struct PCB* blockQueueHead, struct PCB* suspendedReadyHead, struct PCB* suspendedBlockHead);
void deletePCB(char name[], struct PCB* readyQueueHead, struct PCB* blockQueueHead, struct PCB* suspendedReadyHead, struct PCB* suspendedBlockHead);
void blockPCB(char name[], struct PCB* readyQueue, struct PCB* readySuspend, struct PCB* blockQueue, struct PCB* blockSuspend);
void unblockPCB(char name[], struct PCB* readyQueue, struct PCB* readySuspend, struct PCB* blockQueue, struct PCB* blockSuspend);
struct PCB* allocatePCB();
int freePCB(struct PCB* process);
struct PCB* setupPCB(char* name, int class, int priority);
struct PCB* findPcb(char pName[MAX_PNAME], struct PCB* readyHead, struct PCB* blockHead);
void insertPcb(struct PCB* toIn, struct PCB* readyHead, struct PCB* blockHead);
int removePcb(struct PCB* toPull, struct PCB* head);
void dispatch(char name[], struct PCB* readyQueueHead, struct PCB* blockQueueHead, struct PCB* suspendedReadyHead, struct PCB* suspendedBlockHead);
//int removePcbBlocked(struct PCB* toPull, struct PCB* blockHead, struct PCB* susBlockHead);


#endif

