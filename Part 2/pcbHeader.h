#ifndef PCBHEADER_H_INCLUDED
#define PCBHEADER_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_PNAME 50

struct Node
{
    struct Pcb* data;
    struct Node* next;
};
struct Pcb
{
    char p_name[MAX_PNAME];
    int p_class; //0 = application, 1 = system
    int p_priority; // 0-9
    int p_state; //0 = running, 1 = ready, 2 = blocked
    int isSuspended; // 0 = not suspended, 1 = suspended
    struct Pcb* next;
};

void enqueue(struct Node* head, struct Pcb* node);
void enqueuePriority(struct Node* head, struct Pcb* node);

#endif 