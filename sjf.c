#include <stdio.h>
#include "sjf.h"

void SJF(struct jobs j[], int size)
{
    int count = 1;
    int timer = 0;
    int done[size];
    for (int i = 0; i < size; i++)
        done[i] = 0;

    struct jobs *doneQ = malloc(sizeof(struct jobs));
    int done_size = 0;
    while (count <= size)
    {
        struct jobs *ready = malloc(sizeof(struct jobs));
        int ready_size = 0;
        for (int i = 0; i < size; i++)
        {
            if (j[i].arrivalTime <= timer && done[i] == 0)
            {
                ready_size++;
                ready = realloc(ready, sizeof(struct jobs) * ready_size);
                ready[ready_size - 1] = j[i];
            }
        }
        if (ready_size == 0)
        {
            timer++;
            continue;
        }

        for (int i = 0; i < (ready_size - 1); i++)
        {
            for (int k = 1; k < ready_size; k++)
            {
                if (ready[i].processRunTime > ready[k].processRunTime)
                {
                    char tc[11];
                    int arr, dur, id;
                    id = ready[i].PID;
                    strcpy(tc, ready[i].processName);
                    // tc = prcs[i].processName;
                    arr = ready[i].arrivalTime;
                    dur = ready[i].processRunTime;

                    ready[i].PID = ready[k].PID;
                    strcpy(ready[i].processName, ready[k].processName);
                    ready[i].arrivalTime = ready[k].arrivalTime;
                    ready[i].processRunTime = ready[k].processRunTime;

                    ready[k].PID = id;
                    strcpy(ready[k].processName, tc);
                    ready[k].arrivalTime = arr;
                    ready[k].processRunTime = dur;
                }
            }
        }

        done_size++;
        timer += ready[0].processRunTime;
        doneQ = realloc(doneQ, sizeof(struct jobs) * done_size);
        doneQ[done_size - 1] = ready[0];
        count++;

        for (int i = 0; i < size; i++)
        {
            if (ready[0].PID == j[i].PID)
                done[i] = 1;
            // printf("%d ", done[i]);
        }
    }
    printf("Processes completed in this order using SJF: \n");
    printf("P_name PID    P_dur  P_arriv\n");
    for (int i = 0; i < size; i++)
    {
        printf("%s\t%d\t%d\t%d\n", doneQ[i].processName, doneQ[i].PID, doneQ[i].processRunTime, doneQ[i].arrivalTime);
    }
    printf("\n\n");
}