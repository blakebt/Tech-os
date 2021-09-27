#include "../Group3Project_Part1/commands.h"


void enqueue(struct PCB** head, struct PCB** pcb)
{
    struct PCB* current = *head;
    while(current->next != NULL)
    {
        current = current->next;
    }
    current->next = *pcb;
    
}

// Enqueue for a priority queue structure
void enqueuePriority(struct PCB** head, struct PCB** PCB)
{
    // if the list is empty, then insert then the new PCB is the head node
    if((*head) == NULL)
    {
        (*head) = (*PCB);
    }
    // if the new process has a higher priority then the head, insert the new process at the beginning of the list
    else if((*head)->p_priority > (*PCB)->p_priority)
    {
        struct PCB* temp = (*head);
        (*PCB)->next = *head;
        (*head) = *PCB;
    }
    // otherwise, find where the process belongs in the queue, based on priority, and insert it at the end of those processes
    // by inserting at the end of like priorities, we're still giving processes that were in the queue before the new one more
    // priority
    else
    {
        struct PCB* current = (*head);

        while(current->next != NULL && (current->next)->p_priority < (*PCB)->p_priority)
        {
            current = current->next;   
        }
        (*PCB)->next = current->next;
        current->next = *PCB;
    }
}
// a simple dequeue function that will remove the first node in the queue
struct PCB* dequeue(struct PCB** head)
{
    struct PCB* temp = *head;
    (*head) = (*head)->next;
    freePCB(temp);
}

// a function to print the list, can be modified to print whatever information we would like
// not sure this needs to be in the final product
void printList(struct PCB* head)
{
    struct PCB* current = head;
    while(current != NULL)
    {
        printf("%d ", current->p_priority);
        current = current->next;
    }
}

// TEST MAIN
// int main()
// {
//     int count = 0;
//     struct PCB* head = setupPCB("name", 0, 0);
//     struct PCB* temp = setupPCB("name", 0, 1);
//     enqueuePriority(&head, &temp);
//     printList(head);
//     printf("\n");
//     struct PCB* third = setupPCB("name", 0, 2);
//     enqueue(&head, &third);
//     printList(head);
//     printf("\n");
//     dequeue(&head);
//     printList(head);

// }
