#include <stdio.h>
#include "fifo.h"

void FIFO(struct jobs *prcs, int size)
{
    for (int i = 0; i < (size - 1); i++)
    {
        for (int j = 1; j < size; j++)
        {
            if (prcs[i].arrivalTime > prcs[j].arrivalTime)
            {
                char tc[11];
                int arr, dur, id;
                id = prcs[i].PID;
                strcpy(tc, prcs[i].processName);
                // tc = prcs[i].processName;
                arr = prcs[i].arrivalTime;
                dur = prcs[i].processRunTime;

                prcs[i].PID = prcs[j].PID;
                strcpy(prcs[i].processName, prcs[j].processName);
                prcs[i].arrivalTime = prcs[j].arrivalTime;
                prcs[i].processRunTime = prcs[j].processRunTime;

                prcs[j].PID = id;
                strcpy(prcs[j].processName, tc);

                prcs[j].arrivalTime = arr;
                prcs[j].processRunTime = dur;
            }
        }
    }
    printf("Processes completed in this order using FIFO: \n");
    printf("P_name PID    P_dur  P_arriv\n");
    for (int i = 0; i < size; i++)
    {
        printf("%s\t%d\t%d\t%d\n", prcs[i].processName, prcs[i].PID, prcs[i].processRunTime, prcs[i].arrivalTime);
    }
    free(prcs);
}