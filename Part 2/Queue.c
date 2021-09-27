#include <stdio.h>
#include <stdlib.h>
#include "pcbHeader.h"

// struct Node
// {
//     struct Pcb* data;
//     struct Node* next;
// };

struct Node* initializeNode(int* count, struct PCB* pcb)
{
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->data = pcb;
    n->next = NULL;

    *count = *count + 1;
    return n;
}

void enqueue(struct Node* head, struct PCB* node)
{
    if(head == NULL)
    {
        head->data = node;
    }
    else
    {
        struct PCB* current = head->data;
        while(current->next != NULL)
        {
            current = current->next;
        }
        current->next = node;
    }
}

void enqueuePriority(struct Node* head, struct PCB* node)
{
    if(head == NULL)
    {
        head->data = node;
    }
    else
    {
        struct PCB* current = head->data;
        while(node->p_priority > current->p_priority)
        {
            current = current->next;
        }
        
    }
}
struct Node* dequeue(struct Node* head, int* count)
{
    count--;
    return head->next;
}

void printList(struct Node* head)
{
    struct Node* current = head;
    while(current != NULL)
    {
        printf("%s ", current->data->p_name);
        current = current->next;
    }
}
// int main()
// {
//     int count = 0;
//     struct Node* head = initializeNode(&count);

//     for(int i = 0; i < 10; i++)
//     {
//         struct Node* temp = initializeNode(&count);
//         enqueue(head, temp);
//     }
//     printList(head);
//     for(int i = 0; i < 5; i++)
//     {
//         head = dequeue(head,&count);
//         printList(head);
//         printf("\n");
//     }

// }
