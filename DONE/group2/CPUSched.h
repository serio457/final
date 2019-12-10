/*
Adriaan EngelBrecht & Kellen Casey
CPUsched
CS 3074
CPUsched.h
*/

//Header file for CPUsched

#ifndef CPUSCHED_H
#define CPUSCHED_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include "pcb.h"

typedef int BOOL;

#define FALSE 0
#define TRUE 1

#define FCFS 0
#define RR 1
#define SJF 2
#define PRI 3

//writes to an infile "process.in" with simulated processes
//Bounds: arrival: 0-100, burst: 1-100, priority: 0-50
//Defaults: arrival: increment by 5, burst: 20, priority: -1
void simulate(BOOL arrival, BOOL burst, BOOL priority, int simCount);

#endif