#ifndef PCBHEADER_H_INCLUDED
#define PCBHEADER_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_PNAME 50

struct Node;

void enqueue(struct Node* head, struct Node* node);
void enqueuePriority(struct Node* head, struct Node* node);

#endif 