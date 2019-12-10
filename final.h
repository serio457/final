#ifndef FINAL_H
#define FINAL_H
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <ctype.h>
#include <errno.h>
#include "CPUSched.h"
#include "pcb.h"
#include "queue.h"
#include "p.h"

typedef struct {
    char PID[4];
    int arrival;
    int burst;
    int priority;
    int memLocations[500];
} PROCESS;

//takes in an empty array of pcb structs, an array of PROCESS structs, and an int number of processes
//that indicates how many processes are read in. Fills pcbs[] with appropriate values from processes[], so pcbs[i]
//corresponds to processes[i].
void makePCBs (pcb pcbs[], PROCESS processes[], int numProcesses);

//takes in a string indicating scheduler type, an int number of quanta, a BOOL for if preemptive or not,
//a filled array of pcb structs, and an int number of processes needing to be scheduled.
//Returns the average wait time of the scheduled processes as a double.
double CPUScheduling(char typeString[], int quanta, BOOL preemptive, pcb pcbs[], int numProcesses);

//converts the typeString into an defined int (See CPUSched.h). Called within CPUScheduling
int setSchedulerType(char typeString[]);

//takes in pointer to a populated and ordered queue_t, as well as integer number of processes in queue.
//returns the average wait time of the processes in queue. Called within CPUScheduling
double calcAverageWait (queue_t* queue, int numProcesses);

//takes in char array indicating the scheduling type, prints out message indicating that
//scheduler type typeString is not implemented.
void printSchedulerTypeErrors(char typeString[]);

//takes in empty arrays of types ENTRY and FRAMEINFO, as well as the int maximum number of pages
//and number of frames. Fills entries[] with maxPages number of initialized ENTRY structs, and
//fills frames[] with numFrames number of FRAMEINFO structs.
void initializePaging(ENTRY entries[],FRAMEINFO frames[], int maxPages, int numFrames);

//takes in PROCESS array, number of processes, number of frames, size of a page, memory size, and pager type
//prints paging information to the screen 
//does not page because p.h does not include helpful documentation for running the pager
void paging(PROCESS processes[], int numProcesses, int numFrames, int pagesize, int memorySize, char typeString[]);

#endif