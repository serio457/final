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


int findMaxPages(int memory, int pageSize);
int readFromFile(FILE* ifp, int* fc);
void initializeEntry(ENTRY* entry);
void initializeFrame(FRAMEINFO* frame);
TYPE setType(char* typeString);
int whatPageAmIOn(int memoryAdd, int pageSize);
void resetValidBits(ENTRY pageTable[], int frameNo, int maxPages);
int findFrame(TYPE type, int maxFrames, FRAMEINFO frames[], int* frameNo);
int mfu(int maxFrames, FRAMEINFO frames[]);
int lru(int maxFrames, FRAMEINFO frames[]);

#endif
