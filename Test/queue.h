/*
Adriaan EngelBrecht & Kellen Casey
CPUsched
CS 3074
queue.h
*/

#ifndef QUEUE_H
#define QUEUE_H

typedef struct Node
{
  pcb* process;
  struct Node* next;
} node_t;

//make sure to initialize the head and tail to NULL
typedef struct
{
  struct Node* head;
  struct Node* tail;
} queue_t;

//push doesn't work with FCFS, push_**** are called w/in push, depending on type parameter
void push(queue_t* queue, pcb* process, int type);
void push_fcfs(queue_t* queue, pcb* process);
void push_sjf(queue_t* queue, pcb* process);
void push_pri(queue_t* queue, pcb* process);
pcb* pop(queue_t* queue);

BOOL isComplete(queue_t* queue, pcb* pcbArray, int procCount);
void pushNewArrivals(queue_t* queue, pcb* procs, int* cpuTime, int procCount, int type);
void incrementWaitTime(queue_t* queue, pcb* pcbArray, int procCount, cpu_t runningProc);

#endif
