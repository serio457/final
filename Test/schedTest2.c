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
    printf("Processes Read: %d\n", numProcesses);

    queue_t queue;
    queue.head = NULL;
    queue.tail = NULL;
    for (int i=0; i<numProcesses; i++)
    {
        push(&queue, &testPCB[i], 0);
        //push_sjf(&queue, &testPCB[i]);
        printf ("Queue: %s\n", queue.head->process->name);
    }

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
    int result = whatPageAmIOn(700, 512);
    printf ("%d\n", result);

    int thisResult = readFromFile(file, memoryLocation);
    printf ("MemLoc count %d\n", thisResult);
    for (int i = 0; i < thisResult; i++)
    {
        printf ("location: %d\n", memoryLocation[i]);
    }
    
    printf ("Location of file %d\n", file);

    return 0;
}