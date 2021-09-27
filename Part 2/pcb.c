#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pcbHeader.h"
#define MAX_PNAME 50

struct Pcb* allocatePCB();
int freePcb(struct Pcb* process);
struct Pcb* setupPcb(char* name, int class, int priority);
struct Pcb* findPcb(char pName[MAX_PNAME], struct Node* readyHead, struct Node* blockHead);
void insertPcb(struct Pcb* toIn, struct Node* readyHead, struct Node* blockHead);
int removePcb(struct Pcb* toPull, struct Node* readyHead, struct Node* blockHead);

// struct Pcb
// {
//     char p_name[MAX_PNAME];
//     int p_class; //0 = application, 1 = system
//     int p_priority; // 0-9
//     int p_state; //0 = running, 1 = ready, 2 = blocked
//     int isSuspended; // 0 = not suspended, 1 = suspended
//     struct Pcb* next;
// };

int main()
{
    printf("Starting test\n");
    struct Node* head = NULL;
    char name[MAX_PNAME] = "tester";
    struct Pcb* p1 = setupPcb(name, 0, 6);
    enqueue(head, p1);

    printf("Created PCB: \n");
    printf("Name: %s\n", p1->p_name);
    printf("Class: %d\n", p1->p_class);
    printf("Priority: %d\n", p1->p_priority);
    printf("State: %d\n", p1->p_state);
    printf("is it suspended? %d\n", p1->isSuspended);

    char name2[MAX_PNAME] = "test2";
    struct Pcb* p2 = setupPcb(name2, 0, 8);
    enqueue(head, p2);
    char name3[MAX_PNAME] = "randolf";
    struct Pcb* p3 = setupPcb(name3, 0, 2);
    enqueue(head, p3);
    char name4[MAX_PNAME] = "Geralt";
    struct Pcb* p4 = setupPcb(name4, 0, 5);
    enqueue(head, p4);
    
    struct Pcb* temp = findPcb("randolf", head, head);
    printf("%d\n", temp->p_priority);
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

struct Pcb* findPcb(char pName[MAX_PNAME], struct Node* readyHead, struct Node* blockHead) //finds the PCB with the matching name in one of the queues and returns the pointer
{
    if(readyHead != NULL)
    {
        if(strcmp(readyHead->data->p_name, pName) == 0)
        {
            return readyHead->data;
        }
        struct Pcb* current = readyHead->data;
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
        if(strcmp(blockHead->data->p_name, pName) == 0)
        {
            return blockHead->data;
        }
        struct Pcb* current = blockHead->data;
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

void insertPcb(struct Pcb* toIn, struct Node* readyHead, struct Node* blockHead) //adds the PCB to the appropriate queue 
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

int removePcb(struct Pcb* toPull, struct Node* readyHead, struct Node* blockHead) //removes the PCB from it's queue, and returns a success/failure notice of 1/0 respectively
{
    if(readyHead != NULL && toPull->p_state == 1 && strcmp(toPull->p_name, readyHead->data->p_name) == 0)
    {
        readyHead->data = toPull->next;
        return 1;
    }
    else if(blockHead != NULL && toPull->p_state == 2 && strcmp(toPull->p_name, blockHead->data->p_name) == 0)
    {
        blockHead->data = toPull->next;
        return 1;
    }
    else
    {
        if(readyHead != NULL && toPull->p_state ==1)
        {
            struct Pcb* current = readyHead->data;
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
            struct Pcb* current = blockHead->data;
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