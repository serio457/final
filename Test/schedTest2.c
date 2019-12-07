#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include "CPUSched.h"
#include "pcb.h"
#include "queue.h"
#include "p.h"


int main (void)
{
    //Simulate Test
    printf ("In main\n");
    BOOL arrival = TRUE;
    BOOL burst = TRUE;
    BOOL priority = TRUE;
    int simulationCount = 20;
    simulate(arrival, burst, priority, simulationCount);

    int numProcesses = 0;
    pcb* testPCB;
    testPCB = readFile("processes.in", &numProcesses);
    printf("Processes Read: %d\n\n", numProcesses);

    queue_t queue;
    queue.head = NULL;
    queue.tail = NULL;
    printf ("Pushing PCBs to Queue\n");
    for (int i=0; i<numProcesses; i++)
    {
        push(&queue, &testPCB[i], SJF);
        //push_sjf(&queue, &testPCB[i]);
        printf ("Current Head of Queue: %s\n", queue.head->process->name);
    }
    printf("\nPopping PCBs (pcb.h struct)\n");

    pcb tempPCB;
    for (int i=0; i<numProcesses; i++)
    {
        tempPCB = *pop (&queue);
        //pop(&queue);
        printf ("Process %d: %s %d %d %d %d %d\n", i, tempPCB.name, tempPCB.arrival, tempPCB.burst, tempPCB.priority, tempPCB.runTime, tempPCB.waitTime);
    }

    FILE* file;
    file = fopen("memory.txt", "r");
    int memoryLocation[100];


    int thisResult = readFromFile(file, memoryLocation);
    printf ("MemLoc count %d\n", thisResult);
    for (int i = 0; i < thisResult; i++)
    {
        printf ("location: %d\n", memoryLocation[i]);
    }
    

    printf ("\nwhatPageAmIOn:");
    int result = whatPageAmIOn(700, 512);
    printf ("\n");
    //printf ("Location of file %d\n", file); //Wanted to see if it was possible to start reading in the middle of the file. Unclear results (for reading the memory locations instead of making a new function)

    return 0;
}