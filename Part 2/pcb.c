#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Group3Project_Part1/commands.h"
#define MAX_PNAME 50

struct PCB* allocatePCB();
int freePcb(struct PCB* process);
struct PCB* setupPcb(char* name, int class, int priority);
struct PCB* findPcb(char pName[MAX_PNAME], struct PCB* readyHead, struct PCB* blockHead);
void insertPcb(struct PCB* toIn, struct PCB* readyHead, struct PCB* blockHead);
int removePcb(struct PCB* toPull, struct PCB* readyHead, struct PCB* blockHead);

//Commands used in TechOS.c
void suspend(char arguments[MAX_COMMAND], struct PCB* readyQueueHead, struct PCB* blockQueueHead, struct PCB* suspendReadyHead, struct PCB* suspendBlockHead)
{
    struct PCB* toSuspend = findPcb(arguments, readyQueueHead, blockQueueHead);
    if(toSuspend != NULL)
    {
        if(toSuspend->p_state == 1)
        {
            toSuspend->isSuspended = 1;
            enqueue(&suspendReadyHead, &toSuspend);
        }
        else if(toSuspend->p_state == 2)
        {
            toSuspend->isSuspended = 1;
            enqueue(&suspendBlockHead, &toSuspend);
        }
    }
    else
    {
        red();
        printf("Currently no queued process by that name\n");
        reset();
    }
}

void resume(char arguments[MAX_COMMAND], struct PCB* readyQueueHead, struct PCB* blockQueueHead, struct PCB* suspendedReadyHead, struct PCB* suspendedBlockHead)
{
    struct PCB* unsuspend = findPcb(arguments, suspendedReadyHead, suspendedBlockHead);
    if(unsuspend != NULL)
    {
        if(unsuspend->p_state ==1)
        {
            unsuspend->isSuspended = 0;
            enqueuePriority(&readyQueueHead, &unsuspend);
        }
        else if(unsuspend->p_state ==2)
        {
            unsuspend->isSuspended = 0;
            enqueue(&blockQueueHead, &unsuspend);
        }
    }
    else
    {
        red();
        printf("Currenlty no suspended process by that name\n");
        reset();
    }
}

void setPriority(char arguments[MAX_COMMAND], struct PCB* readyQueue)
{
    
}

// struct Pcb
// {
//     char p_name[MAX_PNAME];
//     int p_class; //0 = application, 1 = system
//     int p_priority; // 0-9
//     int p_state; //0 = running, 1 = ready, 2 = blocked
//     int isSuspended; // 0 = not suspended, 1 = suspended
//     struct Pcb* next;
// };

// int main()
// {
//     printf("Starting test\n");
//     struct Node* head = NULL;
//     char name[MAX_PNAME] = "tester";
//     struct PCB* p1 = setupPcb(name, 0, 6);
//     enqueue(head, p1);

//     printf("Created PCB: \n");
//     printf("Name: %s\n", p1->p_name);
//     printf("Class: %d\n", p1->p_class);
//     printf("Priority: %d\n", p1->p_priority);
//     printf("State: %d\n", p1->p_state);
//     printf("is it suspended? %d\n", p1->isSuspended);

//     char name2[MAX_PNAME] = "test2";
//     struct PCB* p2 = setupPcb(name2, 0, 8);
//     enqueue(head, p2);
//     char name3[MAX_PNAME] = "randolf";
//     struct PCB* p3 = setupPcb(name3, 0, 2);
//     enqueue(head, p3);
//     char name4[MAX_PNAME] = "Geralt";
//     struct PCB* p4 = setupPcb(name4, 0, 5);
//     enqueue(head, p4);
    
//     struct PCB* temp = findPcb("randolf", head, head);
//     printf("%d\n", temp->p_priority);
// }

struct PCB* allocatePCB()
{
    struct PCB* newProcess = (struct PCB*)malloc(sizeof(struct PCB));

    return newProcess;
}

int freePcb(struct PCB* process)
{
    int isSuccess;
    if(process == NULL)
    {
        isSuccess = 0;
    }
    else
    {
        free(process);
        process = NULL;
        isSuccess = 1;
    }

    return isSuccess;
}


struct PCB* setupPcb(char* name, int pClass, int priority)
{
    int error = 0;
    struct PCB* newProcess = allocatePCB();

    if(pClass != 0 && pClass != 1)
    {
        error = 1;
        printf("Invalid class. Please use 0 for application or 1 for system.\n");
    }

    if(priority < 0 || priority > 9)
    {
        error = 1;
        printf("Invalid priority. Please use a number between 0 and 9.\n");
    }

    if(strlen(name) > MAX_PNAME)
    {
        error = 1;
        printf("Entered process name too large, try using a smaller name.\n");
    }

    if(error == 1)
    {
        newProcess = NULL;
    }
    else
    {
        strcpy(newProcess->p_name, name);
        newProcess->p_class = pClass;
        newProcess->p_priority = priority;
        newProcess->p_state = 1;
        newProcess->isSuspended = 0;
        newProcess->next = NULL;
    }

    return newProcess;
}

struct PCB* findPcb(char pName[MAX_PNAME], struct PCB* readyHead, struct PCB* blockHead) //finds the PCB with the matching name in one of the queues and returns the pointer, returns null if nonexistant
{
    if(readyHead != NULL)
    {
        if(strcmp(readyHead->p_name, pName) == 0)
        {
            return readyHead;
        }
        struct PCB* current = readyHead;
        while(current->next != NULL)
        {
            current = current->next;
            if(strcmp(current->p_name, pName) == 0)
            {
                return current;
            }
        }
    }

    if(blockHead != NULL)
    {
        if(strcmp(blockHead->p_name, pName) == 0)
        {
            return blockHead;
        }
        struct PCB* current = blockHead;
        while(current->next != NULL)
        {
            current = current->next;
            if(strcmp(current->p_name, pName) == 0)
            {
                return current;
            }
        }
    }

    return NULL;
}

void insertPcb(struct PCB* toIn, struct PCB* readyHead, struct PCB* blockHead) //adds the PCB to the appropriate queue 
{
    if(toIn->p_state == 1)
    {
        enqueuePriority(&readyHead, &toIn);
    }
    else if(toIn->p_state == 2)
    {
        enqueue(&blockHead, &toIn);
    }
}

int removePcb(struct PCB* toPull, struct PCB* readyHead, struct PCB* blockHead) //removes the PCB from it's queue, and returns a success/failure notice of 1/0 respectively
{
    if(readyHead != NULL && toPull->p_state == 1 && strcmp(toPull->p_name, readyHead->p_name) == 0)
    {
        readyHead = toPull->next;
        return 1;
    }
    else if(blockHead != NULL && toPull->p_state == 2 && strcmp(toPull->p_name, blockHead->p_name) == 0)
    {
        blockHead = toPull->next;
        return 1;
    }
    else
    {
        if(readyHead != NULL && toPull->p_state ==1)
        {
            struct PCB* current = readyHead;
            while(current->next != NULL)
            {
                current = current->next;
                if(strcmp(current->next->p_name, toPull->p_name) == 0)
                {
                    current->next = toPull->next;
                }
            }
        }

        if(blockHead != NULL && toPull->p_state == 2)
        {
            struct PCB* current = blockHead;
            while(current->next != NULL)
            {
                current = current->next;
                if(strcmp(current->next->p_name, toPull->p_name) == 0)
                {
                    current->next = toPull->next;
                }
            }
        }
    }
    return 0;
}