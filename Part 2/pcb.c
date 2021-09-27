#include "../Group3Project_Part1/commands.h"

struct PCB* allocatePCB();
int freePCB(struct PCB* process);
struct PCB* setupPCB(char* name, int class, int priority);


// int main()
// {
//     char name[MAX_PNAME] = "tester";
//     struct PCB* p1 = setupPCB(name, 0, 6);

//     printf("Created PCB: \n");
//     printf("Name: %s\n", p1->p_name);
//     printf("Class: %d\n", p1->p_class);
//     printf("Priority: %d\n", p1->p_priority);
//     printf("State: %d\n", p1->p_state);
//     printf("is it suspended? %d\n", p1->isSuspended);
// }

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