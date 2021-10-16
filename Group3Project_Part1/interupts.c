#include "commands.h"

//This function moves an interupted process to the blocked queue
void interupt_handler(int interupt_val, struct PCB* process,  struct PCB* readyQueueHead, struct PCB* blockQueueHead, struct PCB* suspendReadyHead, struct PCB* suspendBlockHead)
{
    int offset = interupt_val % 256; //This gets the offset, Dr G noted in class that he made a mistake with the offset, where we actually need the remainder, not the outcome of the division
    process->offset = offset; 
    suspend(process->p_name, readyQueueHead, blockQueueHead, suspendReadyHead, suspendBlockHead);
    blockPCB(process->p_name, readyQueueHead, suspendReadyHead, blockQueueHead, suspendBlockHead);
    resume(process->p_name, readyQueueHead, blockQueueHead, suspendReadyHead, suspendBlockHead);
}

//This is the function that will unblock Processes if the ready queue is empty, or on a 50% chance if called and there are items in the block queue 
void reintegrater( struct PCB* readyQueueHead, struct PCB* blockQueueHead, struct PCB* suspendReadyHead, struct PCB* suspendBlockHead)
{
    if(readyQueueHead->next == NULL)
    {
        unblockPCB(blockQueueHead->next->p_name, readyQueueHead, suspendReadyHead, blockQueueHead, suspendBlockHead);
    }
    else if(blockQueueHead != NULL)
    {
        time_t t;
        srand(time(&t));
        int chance = (int)(rand()*2);
        if(chance == 1)
        {
            unblockPCB(blockQueueHead->next->p_name, readyQueueHead, suspendReadyHead, blockQueueHead, suspendBlockHead);
        }
    }
}