#include <stdio.h>
#include "rr.h"

void RR(struct jobs j[], int size)
{
    int slice = 1;
    int done_size = 0, timer = 0;
    int done[size];
    int dur[size];
    for (int i = 0; i < size; i++)
    {
        done[i] = 0;
        dur[i] = j[i].processRunTime;
    }
    struct jobs *doneQ = malloc(sizeof(struct jobs));

    while (done_size < size)
    {
        for (int i = 0; i < size; i++)
        {
            if (j[i].arrivalTime < timer && done[i] == 0)
            {
                j[i].processRunTime -= slice;
                timer += 2;
                if (j[i].processRunTime <= 0)
                {
                    done_size++;
                    doneQ = realloc(doneQ, sizeof(struct jobs) * done_size);
                    doneQ[done_size - 1] = j[i];
                    done[i] = 1;
                }
            }
        }
        timer++;
    }
    printf("Processes completed in this order using RR: \n");
    printf("P_name PID    P_dur  P_arriv\n");
    for (int i = 0; i < size; i++)
    {
        printf("%s\t%d\t%d\t%d\n", doneQ[i].processName, doneQ[i].PID, dur[i], doneQ[i].arrivalTime);
    }
}