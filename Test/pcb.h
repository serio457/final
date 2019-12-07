/*
Adriaan EngelBrecht & Kellen Casey
CPUsched
CS 3074
pcb.h
*/

#ifndef PCB_H
#define PCB_H

// A structure to hold data of processes in a linked list
typedef struct
{
  char* name;
  int arrival;
  int burst;
  int priority;
  int runTime;
  int waitTime;
}pcb;

typedef pcb* cpu_t;

//reads from infile with specifed fileName, procCount is sent in as 0 and is incremented
//for every process read in, returns a pointer to a pcb that is also put into an array in
//the function
pcb* readFile(char* fileName, int* procCount);

#endif