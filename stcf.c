#include <stdio.h>
#include "stcf.h"

void STCF(struct jobs j[], int size)
{
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

        // printf("%d\n", ready_size);
        if (ready_size == 0)
        {
            timer++;
            continue;
        }
        int minTimeComp = 1000;
        int pNo;
        for (int i = 0; i < ready_size; i++)
        {
            if (ready[i].processRunTime < minTimeComp)
            {
                minTimeComp = ready[i].processRunTime;
                pNo = ready[i].PID;
            }
        }
        for (int i = 0; i < size; i++)
        {

            if (pNo == j[i].PID)
            {
                j[i].processRunTime--;
                // printf("time left: %d\n", j[i].processRunTime);
                timer++;

                if (j[i].processRunTime == 0)
                {
                    done_size++;
                    doneQ = realloc(doneQ, sizeof(struct jobs) * done_size);
                    doneQ[done_size - 1] = j[i];
                    done[i] = 1;
                }
            }
        }
    }
    printf("Processes completed in this order using STCF: \n");
    printf("P_name PID    P_dur  P_arriv\n");
    for (int i = 0; i < size; i++)
    {
        printf("%s\t%d\t%d\t%d\n", doneQ[i].processName, doneQ[i].PID, dur[i], doneQ[i].arrivalTime);
    }
}