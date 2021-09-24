#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pcbHeader.h"
#define MAX_PNAME 50

struct Pcb* allocatePCB();
int freePcb(struct Pcb* process);
struct Pcb* setupPcb(char* name, int class, int priority);


struct Pcb
{
    char p_name[MAX_PNAME];
    int p_class; //0 = application, 1 = system
    int p_priority; // 0-9
    int p_state; //0 = running, 1 = ready, 2 = blocked
    int isSuspended; // 0 = not suspended, 1 = suspended
    struct Pcb* next;
};

int main()
{
    char name[MAX_PNAME] = "tester";
    struct Pcb* p1 = setupPcb(name, 0, 6);

    printf("Created PCB: \n");
    printf("Name: %s\n", p1->p_name);
    printf("Class: %d\n", p1->p_class);
    printf("Priority: %d\n", p1->p_priority);
    printf("State: %d\n", p1->p_state);
    printf("is it suspended? %d\n", p1->isSuspended);
}

struct Pcb* allocatePCB()
{
    struct Pcb* newProcess = (struct Pcb*)malloc(sizeof(struct Pcb));

    return newProcess;
}

int freePcb(struct Pcb* process)
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


struct Pcb* setupPcb(char* name, int pClass, int priority)
{
    int error = 0;
    struct Pcb* newProcess = allocatePCB();

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
    }

    return newProcess;
}

struct Pcb* findPcb(char pName[MAX_PNAME], struct Pcb* readyHead, struct Pcb* blockHead) //finds the PCB with the matching name in one of the queues and returns the pointer
{
    if(readyHead != NULL)
    {
        if(strcmp(readyHead->p_name, pName) == 0)
        {
            return readyHead;
        }
        struct Pcb* current = readyHead;
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
        struct Pcb* current = blockHead;
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

void insertPcb(struct Pcb* toIn, struct Pcb* readyHead, struct Pcb* blockHead) //adds the PCB to the appropriate queue 
{
    if(toIn->p_state == 1)
    {
        enqueuePriority(readyHead, toIn);
    }
    else if(toIn->p_state == 2)
    {
        enqueue(blockHead, toIn);
    }
}

int removePcb(struct Pcb* toPull) //removes the PCB from it's queue, and returns a success/failure notice of 1/0 respectively
{

}