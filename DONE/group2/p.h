/// Brogan Crist, Christine Lee, Hunter Salada
/// Paging Simulator 2019
/// p.h

#ifndef P_H
#define P_H

#define TRUE 1
#define FALSE 0

/// TYPEDEFS
typedef enum{
    FIFO,
    LRU,
    MFU,
    RANDOM
} TYPE;

typedef int BOOL;

typedef struct{
    int frameI;
    BOOL validBit;
} ENTRY;

typedef struct{
    int uses;
    int lastUsed;
} FRAMEINFO;


/// INCLUDES
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

//comments from our presentation relating to the functions:

//Returns the max number of pages based on input memory and pageSize.
int findMaxPages(int memory, int pageSize);

//Takes in a file name and an int array, then returns the number of locations read. 
// Works well for its purpose, but we're not sure how to adapt it to read from a 
// section in the middle of a file. It might not be possible
int readFromFile(FILE* ifp, int* fc);

//found out that we have to initialize each FRAMEINFO and ENTRY structure by 
// calling these functions on them individually, done by running through an 
// array in a for loop.
void initializeEntry(ENTRY* entry);
void initializeFrame(FRAMEINFO* frame);

//changes a TYPE struct to the appropriate value based on a string, not case sensitive.
TYPE setType(char* typeString);

//returns what page a certain memory location is on. It also prints it out to the screen.
int whatPageAmIOn(int memoryAdd, int pageSize);

//did not use due to somewhat unclear parameters and no documentation
void resetValidBits(ENTRY pageTable[], int frameNo, int maxPages);

//did not use due to unfinished paging
int findFrame(TYPE type, int maxFrames, FRAMEINFO frames[], int* frameNo);

//mfu and lru did not function for us
int mfu(int maxFrames, FRAMEINFO frames[]);
int lru(int maxFrames, FRAMEINFO frames[]);

#endif
