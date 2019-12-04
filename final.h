#ifndef FINAL_H
#define FINAL_H
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <ctype.h>
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

void makePCBs (pcb pcbs[], PROCESS processes[], int numProcesses);

#endif