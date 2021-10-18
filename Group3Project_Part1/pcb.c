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
int removePcb(struct PCB* toPull, struct PCB* head);

//Commands used in TechOS.c
void suspend(char arguments[MAX_COMMAND], struct PCB* readyQueueHead, struct PCB* blockQueueHead, struct PCB* suspendReadyHead, struct PCB* suspendBlockHead)
{
    struct PCB* toSuspend = findPcb(arguments, readyQueueHead, blockQueueHead);
    if(toSuspend != NULL)
    {
        if(toSuspend->p_state == 1)
        {
            removePcb(toSuspend, readyQueueHead);
            toSuspend->isSuspended = 1;
            toSuspend->next = NULL;
            enqueue(&suspendReadyHead, &toSuspend);
        }
        else if(toSuspend->p_state == 2)
        {
            removePcb(toSuspend, blockQueueHead);
            toSuspend->isSuspended = 1;
            toSuspend->next = NULL;
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
            removePcb(unsuspend, suspendedReadyHead);
            unsuspend->isSuspended = 0;
            unsuspend->next = NULL;
            enqueuePriority(&readyQueueHead, &unsuspend);
        }
        else if(unsuspend->p_state ==2)
        {
            removePcb(unsuspend, suspendedBlockHead);
            unsuspend->isSuspended = 0;
            unsuspend->next = NULL;
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

void setPriority(char name[MAX_COMMAND], char priority[MAX_COMMAND], struct PCB* readyQueue, struct PCB* blockQueue, struct PCB* readySuspend, struct PCB* blockSuspend)
{
    int newPriority = atoi(priority);
    if(newPriority >= 0 && newPriority <= 9)
    {
        struct PCB* pChange = findPcb(name, readyQueue, blockQueue);
        if(pChange == NULL)
        {
            pChange = findPcb(name, readySuspend, blockSuspend);
        }
        if(pChange != NULL)
        {
            if(pChange->p_state == 1 && pChange->isSuspended == 0)
            {
                removePcb(pChange, readyQueue);
                pChange->p_priority = newPriority;
                enqueuePriority(&readyQueue, &pChange);
            }
            else
            {
                pChange->p_priority = newPriority;
            }
        }
        else
        {
            red();
            printf("Process not found\n");
            reset();
        }
    }
    else
    {
        red();
        printf("Priority out of bounds\n");
        reset();
    }
}

void outputPCBInfo(struct PCB* displayable) //actually prints out different info for the processes
{
    printf("Name: %s\n", displayable->p_name);
    if(displayable->p_class == 0)
        printf("Class: Application\n");
    else
        printf("Class: System\n");
    if(displayable->p_state == 1)
        printf("State: Ready\n");
    else if(displayable->p_state == 2)
        printf("State: Blocked\n");
    else    
        printf("State: Running\n");
    if(displayable->isSuspended == 1)
        printf("Currently Suspended\n");
    else
        printf("Currently Not Suspended\n");
    printf("Priority: %d\n", displayable->p_priority);
}

void showPCB(char name[MAX_COMMAND], struct PCB* readyQueue, struct PCB* blockQueue, struct PCB* readySuspend, struct PCB* blockSuspend)
{
    struct PCB* displayable = findPcb(name, readyQueue, blockQueue);
    if(displayable == NULL)
    {
        displayable = findPcb(name, readySuspend, blockSuspend);
    }
    if(displayable != 0)
    {
        outputPCBInfo(displayable);
    }
    else
    {
        red();
        printf("Process not found\n");
        reset();
    }
}

void showQueuePCB(struct PCB* head)
{
    printf("\n");
    head = head->next; // skip the head node
    while(head != NULL)
    {
        printf("\n");
        outputPCBInfo(head);
        head = head->next;
    }
    printf("\n");
}

void showAllPCB(struct PCB* readyHead, struct PCB* blockHead)
{
    showQueuePCB(readyHead);
    showQueuePCB(blockHead);
    printf("\n");
}

void createPCB(char arguments[], char argument2[], char argument3[], struct PCB* readyQueueHead, struct PCB* blockQueueHead, struct PCB* suspendedReadyHead, struct PCB* suspendedBlockHead)
{
    if(strcmp(arguments, "") != 0 && strcmp(argument2, "") != 0 && strcmp(argument3, "") != 0)
    {
        if(findPcb(arguments, readyQueueHead, blockQueueHead) == NULL && findPcb(arguments, suspendedReadyHead, suspendedBlockHead) == NULL)
        {
            int class = atoi(argument2);
            int priority = atoi(argument3);
            if(class == 0 || class == 1)
            {
                if(priority >= 0 & priority <= 9)
                {
                    struct PCB* newProcess = setupPCB(arguments, class, priority);
                    insertPcb(newProcess, readyQueueHead, blockQueueHead);
                    printf("Process entered into the ready queue\n");
                }
                else
                {
                    red();
                    printf("Priority must be between 0 and 9, lower numbers are higher priority\n");
                    reset();
                }
            }
            else
            {
                red();
                printf("Process class requires argument of 0 or 1\n");
                reset();
            }
        }
        else
        {
            red();
            printf("A process by that name already exists\n");
            reset();
        }
    }
    else{
        red();
        printf("Invalid arguments, requires arguments [Name] [Class (0/1)] [Priority (0-9)]\n");
        reset();
    }
}

void deletePCB(char name[], struct PCB* readyQueueHead, struct PCB* blockQueueHead, struct PCB* suspendedReadyHead, struct PCB* suspendedBlockHead)
{
    struct PCB* toRemove = findPcb(name, readyQueueHead, blockQueueHead);
    if(toRemove == NULL)
    {
        toRemove = findPcb(name, suspendedReadyHead, suspendedBlockHead);
        if(toRemove != NULL)
        {
            if(removePcb(toRemove, suspendedReadyHead) == 0)
            {
                if(removePcb(toRemove, suspendedBlockHead) == 0)
                {
                    red();
                    printf("Error in queue removal\n");
                    reset();
                }
            }
        }
    }
    else
    {
        if(removePcb(toRemove, readyQueueHead) == 0)
        {
            if(removePcb(toRemove, blockQueueHead) == 0)
            {
                red();
                printf("Error in queue removal\n");
                reset();
            }
        }
    }
    if(toRemove != NULL)
    {
        freePCB(toRemove);
    }
    else
    {
        red();
        printf("Process by that name unfound\n");
        reset();
    }
}

void blockPCB(char name[], struct PCB* readyQueue, struct PCB* readySuspend, struct PCB* blockQueue, struct PCB* blockSuspend)
{
    struct PCB* toBlock = findPcb(name, readyQueue, readySuspend);
    if(toBlock != NULL)
    {

        //removePcb(toBlock, readyQueue, readySuspend);
        if(removePcb(toBlock, readyQueue) == 0)
        {
            if(removePcb(toBlock, readySuspend) == 0)
            {
                red();
                printf("There has been an error in queue removal\n");
                reset();
            }
        }
        toBlock->p_state = 2;
        if(toBlock->isSuspended == 0)
        {
            toBlock->next = NULL;
            enqueue(&blockQueue, &toBlock);
        }
        else
        {
            toBlock->next = NULL;
            enqueue(&blockSuspend, &toBlock);
        }
    }
    else
    {
        red();
        printf("No process ready by that name\n");
        reset();
    }
}

void unblockPCB(char name[], struct PCB* readyQueue, struct PCB* readySuspend, struct PCB* blockQueue, struct PCB* blockSuspend)
{
    struct PCB* unblock = findPcb(name, blockQueue, blockSuspend);
    if(unblock != NULL)
    {
        if(removePcb(unblock, blockQueue) == 0)
        {
            if(removePcb(unblock, blockSuspend) == 0)
            {
                red();
                printf("Error in queue removal\n"); 
                reset();
            }
        }
        if(unblock->isSuspended == 0)
        {
            unblock->next = NULL;
            enqueuePriority(&readyQueue, &unblock);
        }
        else
        {
            unblock->next = NULL;
            enqueue(&readySuspend, &unblock);
        }
        unblock->p_state = 1;
    }
    else
    {
        red();
        printf("No process blocked with that name\n");
        reset();
    }
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

struct PCB* allocatePCB()
{
    struct PCB* newProcess = (struct PCB*)malloc(sizeof(struct PCB));

    return newProcess;
}

int freePCB(struct PCB* process)
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


struct PCB* setupPCB(char* name, int pClass, int priority)
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

int removePcb(struct PCB* toPull, struct PCB* head) //removes the PCB from it's queue, and returns a success/failure notice of 1/0 respectively
{
    if(head != NULL && strcmp(toPull->p_name, head->p_name) == 0)
    {
        head = toPull->next;
        return 1;
    }
    else if(head != NULL)
    {
        struct PCB* current = head;
        while(current->next != NULL)
        {
            if(strcmp(current->next->p_name, toPull->p_name) == 0) 
            {
                current->next = toPull->next;
                return 1;
            }
            current = current->next;
        }
    }
    return 0;
}

void dispatch(char name[], struct PCB* readyQueueHead, struct PCB* blockQueueHead, struct PCB* suspendedReadyHead, struct PCB* suspendedBlockHead)
{
    struct PCB* current = readyQueueHead;
    char fileName[MAX_PNAME];
    char executeCommand[] = "./execute ";
    int lock;

    if(current == NULL)//Displays error message if ready queue is empty
    {
        red();
        printf("Error. Ready Queue is empty\n");
        reset();
    }
    else
    {
        strcpy(current->p_data, fileName);//Copy process file path and offset
        strcat(executeCommand, fileName);//Concatenates both strings to have full command: "./execute filename+offset"
        lock = system(executeCommand);//System will return 0 if process is done executing
        current->p_state = 0;//Set dispatched process to running

        while(current->next != NULL)
        {
            if(lock == 0)//lock does not allow another process to be dispatched until current running process is finished
            {
                memset(executeCommand, 0, sizeof executeCommand);//Just in case executeCommand needs to be reset so new file path can be added
                char executeCommand[] = "./execute ";
                
                //Displays message that process completed execution, then delete it.
                printf("Process %s is done.\n", current->p_name);
                deletePCB(current->p_name, readyQueueHead, blockQueueHead, suspendedReadyHead, suspendedBlockHead);

                //Go to next process in ready queue
                current = current->next;
                strcpy(current->p_data, fileName);
                strcat(executeCommand, fileName);

                //Use system to execute process
                lock = system(executeCommand);
                current->p_state = 0;
            }   

        }
    }
    //Make sure the execution order is correct?
}

void loadPCB(char pName[], char class[], char priority[], char filePath[], struct PCB* readyHead, struct PCB* blockedHead, struct PCB* susReadyHead, struct PCB* susBlockedHead)
{
    if(findPcb(pName, readyHead, blockedHead) == NULL && findPcb(pName, susReadyHead, susBlockedHead) == NULL)
    {
        FILE *file;

        file = fopen(filePath, "r");

        if(file != NULL)
        {
            // the process can be inserted
            int pClass = atoi(class);
            int pPriority = atoi(priority);
            struct PCB* toInsert = setupPCB(pName, pClass, pPriority);
            strcpy(toInsert->p_path, filePath);
            insertPcb(toInsert, readyHead, blockedHead);
            printf("\nProcess loaded successfully.\n");
        }
        fclose(file);
    }
    else
    {
        red();
        printf("\nA process with this name has already been created.\n");
        reset();
    }
}

//Commented out, will remove if testing with new removePcb function goes well
// int removePcbBlocked(struct PCB* toPull, struct PCB* blockHead, struct PCB* susBlockHead)
// {
//     if(susBlockHead != NULL && toPull->isSuspended == 1 && strcmp(toPull->p_name, susBlockHead->p_name) == 0)
//     {
//         susBlockHead = toPull->next;
//         return 1;
//     }
//     else if(blockHead != NULL && toPull->isSuspended == 0 && strcmp(toPull->p_name, blockHead->p_name) == 0)
//     {
//         blockHead = toPull->next;
//         return 1;
//     }
//     else
//     {
//         if(susBlockHead != NULL && toPull->isSuspended == 1)
//         {
//             struct PCB* current = susBlockHead;
//             while(current->next != NULL)
//             {
//                 current = current->next;
//                 if(strcmp(current->next->p_name, toPull->p_name) == 0)
//                 {
//                     current->next = toPull->next;
//                 }
//             }
//         }
//         if(blockHead != NULL && toPull->isSuspended == 0)
//         {
//             struct PCB* current = blockHead;
//             while(current->next != NULL)
//             {
//                 current = current->next;
//                 if(strcmp(current->next->p_name, toPull->p_name) == 0)
//                 {
//                     current->next = toPull->next;
//                 }
//             }
//         }
//     }
//     return 0;
// } 