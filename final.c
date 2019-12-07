#include "final.h"

int main(int argc, char *argv[])
{
    if (argc > 18)
    {
        printf("ERROR: TOO MANY ARGUMENTS.\n");
        return 0;
    }

    char scheduler[10] = "FCFS";
    int quanta = 10;
    BOOL preemptive = FALSE;
    char infile[100] = "infile.txt";
    char outfile[100] = "processes.out";
    char pager[10] = "FIFO";
    int numFrames = 3;
    int memorySize = 4096;
    int pagesize = 512;

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-infile") == FALSE)
        {
            if (argc <= i + 1)
            {
                printf("ERROR: MISSING PARAMETER.\n");
                return 0;
            }
            strcpy(infile, argv[i + 1]);
        }
        if (strcmp(argv[i], "-outfile") == FALSE)
        {
            if (argc <= i + 1)
            {
                printf("ERROR: MISSING PARAMETER.\n");
                return 0;
            }
            strcpy(outfile, argv[i + 1]);
        }
        if (strcmp(argv[i], "-scheduler") == FALSE)
        {
            if (argc <= i + 1)
            {
                printf("ERROR: MISSING PARAMETER.\n");
                return 0;
            }
            strcpy(scheduler, argv[i + 1]);
            if (!((!strcasecmp(argv[i + 1], "FCFS")) || (!strcasecmp(argv[i + 1], "RR")) || (!strcmp(argv[i + 1], "SJF")) || (!strcmp(argv[i + 1], "priority"))))
            {
                printf("ERROR: INVALID SCHEDULER TYPE. VALID TYPES INCLUDE: FCFS, RR, SJF, priority\n");
                return 0;
            }
        }
        if (strcmp(argv[i], "-quanta") == FALSE)
        {
            if (argc <= i + 1)
            {
                printf("ERROR: MISSING PARAMETER.\n");
                return 0;
            }
            // Code for testing non-digits in specified quanta from https://stackoverflow.com/questions/10166157/check-if-entire-array-of-characters-in-c-are-only-numbers-return-true-if-yes
            int j;
            const int len = strlen(argv[i + 1]);
            char quantaString[len];
            strcpy(quantaString, argv[i + 1]);
            for (j = 0; j < len; j++)
            {
                if (!isdigit(quantaString[j]))
                {
                    printf("ERROR: NON_DIGITS IN QUANTA. QUANTA MUST BE A POSITIVE, NON-ZERO INTEGER.\n");
                    return 0;
                }
            }
            quanta = atoi(argv[i + 1]);
            if (quanta == 0)
            {
                printf("ERROR: QUANTA MUST BE A POSITIVE, NON-ZERO INTEGER\n");
                return 0;
            }
        }
        if (strcmp(argv[i], "-preemptive") == FALSE)
        {
            preemptive = TRUE;
        }
        if (strcmp(argv[i], "-pager") == FALSE)
        {
            if (argc <= i + 1)
            {
                printf("ERROR: MISSING PARAMETER.\n");
                return 0;
            }

            strcpy(pager, argv[i + 1]);
            if (!((!strcasecmp(argv[i + 1], "FIFO")) || (!strcasecmp(argv[i + 1], "LRU")) || (!strcmp(argv[i + 1], "MFU")) || (!strcmp(argv[i + 1], "RANDOM"))))
            {
                printf("ERROR: INVALID PAGER TYPE. VALID TYPES INCLUDE: FIFO, LRU, MFU, RANDOM\n");
                return 0;
            }
        }
        if (strcmp(argv[i], "-frames") == FALSE)
        {
            if (argc <= i + 1)
            {
                printf("ERROR: MISSING PARAMETER.\n");
                return 0;
            }
            int j;
            const int len = strlen(argv[i + 1]);
            char numFramesStr[len];
            strcpy(numFramesStr, argv[i + 1]);
            for (j = 0; j < len; j++)
            {
                if (!isdigit(numFramesStr[j]))
                {
                    printf("ERROR: NON DIGITS IN FRAMES. FRAMES MUST BE A POSITIVE, NON-ZERO INTEGER.\n");
                    return 0;
                }
            }
            numFrames = atoi(argv[i + 1]);
            if (numFrames == 0)
            {
                printf("ERROR: FRAMES MUST BE A POSITIVE, NON-ZERO INTEGER\n");
                return 0;
            }
        }
        if (strcmp(argv[i], "-memory") == FALSE)
        {
            if (argc <= i + 1)
            {
                printf("ERROR: MISSING PARAMETER.\n");
                return 0;
            }
            int j;
            const int len = strlen(argv[i + 1]);
            char memorySizeStr[len];
            strcpy(memorySizeStr, argv[i + 1]);
            for (j = 0; j < len; j++)
            {
                if (!isdigit(memorySizeStr[j]))
                {
                    printf("ERROR: NON DIGITS IN MEMORY. MEMORY MUST BE A POSITIVE, NON-ZERO INTEGER.\n");
                    return 0;
                }
            }
            memorySize = atoi(argv[i + 1]);
            if (memorySize == 0)
            {
                printf("ERROR: MEMORY MUST BE A POSITIVE, NON-ZERO INTEGER\n");
                return 0;
            }
        }
        if (strcmp(argv[i], "-pagesize") == FALSE)
        {
            if (argc <= i + 1)
            {
                printf("ERROR: MISSING PARAMETER.\n");
                return 0;
            }
            int j;
            const int len = strlen(argv[i + 1]);
            char pagesizeStr[len];
            strcpy(pagesizeStr, argv[i + 1]);
            for (j = 0; j < len; j++)
            {
                if (!isdigit(pagesizeStr[j]))
                {
                    printf("ERROR: NON DIGITS IN PAGESIZE. PAGESIZE MUST BE A POSITIVE, NON-ZERO INTEGER.\n");
                    return 0;
                }
            }
            pagesize = atoi(argv[i + 1]);
            if (pagesize == 0)
            {
                printf("ERROR: PAGESIZE MUST BE A POSITIVE, NON-ZERO INTEGER\n");
                return 0;
            }
        }
    }

    FILE *file;
    int c, numProcesses = 0;
    BOOL textFound = FALSE;
    char *processID;
    PROCESS processes[500];
    PROCESS process;
    file = fopen(infile, "r");
    if (file)
    {
        while (fscanf(file, "%s", process.PID) != EOF)
        {
            textFound = TRUE;
            fscanf(file, "%d", &process.arrival);
            fscanf(file, "%d", &process.burst);
            fscanf(file, "%d", &process.priority);
            for (int i = 0; i < process.burst; i++)
            {
                fscanf(file, "%d", &process.memLocations[i]);
            }
            numProcesses++;
            processes[numProcesses - 1] = process;
        }
    }
    fclose(file);

    if (!textFound)
    {
        printf("ERROR: INPUT FILE CONTAINS NO TEXT.\n");
        return 0;
    }

    pcb *pcbs;
    pcbs = malloc(numProcesses * sizeof(pcb));
    makePCBs(pcbs, processes, numProcesses);
    //Do CPU Scheduling based on input parameters
    double avgWaitTime = CPUScheduling(scheduler, quanta, preemptive, pcbs, numProcesses);
    printf ("Average Wait Time: %f\n", avgWaitTime);

    TYPE pagerType = setType(pager);
    int maxPages = findMaxPages(memorySize, pagesize);

    //Initialize arrays of ENTRYs and FRAMEINFOs
    ENTRY entries[maxPages];
    FRAMEINFO frames[numFrames];
    initializePaging(entries, frames, maxPages, numFrames);
    /*for (int i=0; i<numProcesses; i++)
    {
        printf ("PID: %s\nArrival: %d\nBurst: %d\nPriority: %d\n", processes[i].PID, processes[i].arrival, processes[i].burst, processes[i].priority);
        printf ("name: %s\nArrival: %d\nBurst: %d\nPriority: %d\n", pcbs[i].name, pcbs[i].arrival, pcbs[i].burst, pcbs[i].priority);
    }*/

    return 0;
}

void makePCBs(pcb pcbs[], PROCESS processes[], int numProcesses)
{
    for (int i = 0; i < numProcesses; i++)
    {

        printf("PID: %s Arrival: %d\n", processes[i].PID, processes[i].arrival);

        pcbs[i].name = malloc(4 * sizeof(char));
        strcpy(pcbs[i].name, processes[i].PID);
        pcbs[i].arrival = processes[i].arrival;
        pcbs[i].burst = processes[i].burst;
        pcbs[i].priority = processes[i].priority;
        pcbs[i].runTime = 0;
        pcbs[i].waitTime = 0;
    }
}

double CPUScheduling(char typeString[], int quanta, BOOL preemptive, pcb pcbs[], int numProcesses)
{
    int type = setSchedulerType(typeString);
    //make a queue, initializing head and tail to null
    queue_t queue;
    queue.head = NULL;
    queue.tail = NULL;
    printf("Pushing PCBs to Queue\n");
    for (int i = 0; i < numProcesses; i++)
    {
        push(&queue, &pcbs[i], type);
        printf("Current Head of Queue: %s\n", queue.head->process->name);
    }
    pcb tempPCB;
    double waitTime = calcAverageWait(&queue, numProcesses);
    return waitTime;
}

int setSchedulerType(char typeString[])
{
    if (strcmp(typeString, "FCFS") == 0)
    {
        return 0;
    }
    else if (strcmp(typeString, "RR") == 0)
    {
        return 1;
    }
    else if (strcmp(typeString, "SJF") == 0)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

//from group2 CPUScheduler, queue.c
double calcAverageWait(queue_t* queue, int numProcesses)
{
    int burstSum = 0, indvWait;
    double avgWait, waitSum = 0, count = 0;
    pcb tempPCB;
    for (int i = 0; i < numProcesses; i++)
    {
        tempPCB = *pop(queue);
        indvWait = burstSum - tempPCB.arrival;
        //a condition to compensate for idle time that could arise in the execution of the queue
        if (indvWait < 0)
        {
            indvWait = 0;
            burstSum = burstSum + (tempPCB.arrival - burstSum);
        }
        burstSum = burstSum + tempPCB.burst;
        waitSum = waitSum + indvWait;
        count++;
    }
    avgWait = waitSum / count;
    return avgWait;
}

void initializePaging(ENTRY entries[], FRAMEINFO frames[], int maxPages, int numFrames)
{
    for (int i = 0; i < maxPages; i++)
    {
        initializeEntry(&entries[i]);
    }
    for (int i = 0; i < numFrames; i++)
    {
        initializeFrame(&frames[i]);
    }
}