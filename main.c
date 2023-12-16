#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jobs.h"
#include "fifo.h"
#include "sjf.h"
#include "stcf.h"
#include "rr.h"
// struct jobs
// {
//     char processName[11];
//     int PID;
//     int processRunTime;
//     int arrivalTime;
// };

// void FIFO(struct jobs *prcs, int size)
// {
//     for (int i = 0; i < (size - 1); i++)
//     {
//         for (int j = 1; j < size; j++)
//         {
//             if (prcs[i].arrivalTime > prcs[j].arrivalTime)
//             {
//                 char tc[11];
//                 int arr, dur, id;
//                 id = prcs[i].PID;
//                 strcpy(tc, prcs[i].processName);
//                 // tc = prcs[i].processName;
//                 arr = prcs[i].arrivalTime;
//                 dur = prcs[i].processRunTime;

//                 prcs[i].PID = prcs[j].PID;
//                 strcpy(prcs[i].processName, prcs[j].processName);
//                 prcs[i].arrivalTime = prcs[j].arrivalTime;
//                 prcs[i].processRunTime = prcs[j].processRunTime;

//                 prcs[j].PID = id;
//                 strcpy(prcs[j].processName, tc);

//                 prcs[j].arrivalTime = arr;
//                 prcs[j].processRunTime = dur;
//             }
//         }
//     }
//     printf("Processes completed in this order using FIFO: \n");
//     printf("P_name PID    P_dur  P_arriv\n");
//     for (int i = 0; i < size; i++)
//     {
//         printf("%s\t%d\t%d\t%d\n", prcs[i].processName, prcs[i].PID, prcs[i].processRunTime, prcs[i].arrivalTime);
//     }
// }

// void SJF(struct jobs j[], int size)
// {
//     int count = 1;
//     int timer = 0;
//     int done[size];
//     for (int i = 0; i < size; i++)
//         done[i] = 0;

//     struct jobs *doneQ = malloc(sizeof(struct jobs));
//     int done_size = 0;
//     while (count <= size)
//     {
//         struct jobs *ready = malloc(sizeof(struct jobs));
//         int ready_size = 0;
//         for (int i = 0; i < size; i++)
//         {
//             if (j[i].arrivalTime <= timer && done[i] == 0)
//             {
//                 ready_size++;
//                 ready = realloc(ready, sizeof(struct jobs) * ready_size);
//                 ready[ready_size - 1] = j[i];
//             }
//         }
//         if (ready_size == 0)
//         {
//             timer++;
//             continue;
//         }

//         for (int i = 0; i < (ready_size - 1); i++)
//         {
//             for (int k = 1; k < ready_size; k++)
//             {
//                 if (ready[i].processRunTime > ready[k].processRunTime)
//                 {
//                     char tc[11];
//                     int arr, dur, id;
//                     id = ready[i].PID;
//                     strcpy(tc, ready[i].processName);
//                     // tc = prcs[i].processName;
//                     arr = ready[i].arrivalTime;
//                     dur = ready[i].processRunTime;

//                     ready[i].PID = ready[k].PID;
//                     strcpy(ready[i].processName, ready[k].processName);
//                     ready[i].arrivalTime = ready[k].arrivalTime;
//                     ready[i].processRunTime = ready[k].processRunTime;

//                     ready[k].PID = id;
//                     strcpy(ready[k].processName, tc);
//                     ready[k].arrivalTime = arr;
//                     ready[k].processRunTime = dur;
//                 }
//             }
//         }

//         done_size++;
//         timer += ready[0].processRunTime;
//         doneQ = realloc(doneQ, sizeof(struct jobs) * done_size);
//         doneQ[done_size - 1] = ready[0];
//         count++;

//         for (int i = 0; i < size; i++)
//         {
//             if (ready[0].PID == j[i].PID)
//                 done[i] = 1;
//             // printf("%d ", done[i]);
//         }
//     }
//     printf("Processes completed in this order using SJF: \n");
//     printf("P_name PID    P_dur  P_arriv\n");
//     for (int i = 0; i < size; i++)
//     {
//         printf("%s\t%d\t%d\t%d\n", doneQ[i].processName, doneQ[i].PID, doneQ[i].processRunTime, doneQ[i].arrivalTime);
//     }
//     printf("\n\n");
// }

// void STCF(struct jobs j[], int size)
// {
//     int done_size = 0, timer = 0;
//     int done[size];
//     int dur[size];
//     for (int i = 0; i < size; i++)
//     {
//         done[i] = 0;
//         dur[i] = j[i].processRunTime;
//     }
//     struct jobs *doneQ = malloc(sizeof(struct jobs));

//     while (done_size < size)
//     {
//         struct jobs *ready = malloc(sizeof(struct jobs));
//         int ready_size = 0;

//         for (int i = 0; i < size; i++)
//         {
//             if (j[i].arrivalTime <= timer && done[i] == 0)
//             {
//                 ready_size++;
//                 ready = realloc(ready, sizeof(struct jobs) * ready_size);
//                 ready[ready_size - 1] = j[i];
//             }
//         }

//         // printf("%d\n", ready_size);
//         if (ready_size == 0)
//         {
//             timer++;
//             continue;
//         }
//         int minTimeComp = 1000;
//         int pNo;
//         for (int i = 0; i < ready_size; i++)
//         {
//             if (ready[i].processRunTime < minTimeComp)
//             {
//                 minTimeComp = ready[i].processRunTime;
//                 pNo = ready[i].PID;
//             }
//         }
//         for (int i = 0; i < size; i++)
//         {

//             if (pNo == j[i].PID)
//             {
//                 j[i].processRunTime--;
//                 // printf("time left: %d\n", j[i].processRunTime);
//                 timer++;

//                 if (j[i].processRunTime == 0)
//                 {
//                     done_size++;
//                     doneQ = realloc(doneQ, sizeof(struct jobs) * done_size);
//                     doneQ[done_size - 1] = j[i];
//                     done[i] = 1;
//                 }
//             }
//         }
//     }
//     printf("Processes completed in this order using STCF: \n");
//     printf("P_name PID    P_dur  P_arriv\n");
//     for (int i = 0; i < size; i++)
//     {
//         printf("%s\t%d\t%d\t%d\n", doneQ[i].processName, doneQ[i].PID, dur[i], doneQ[i].arrivalTime);
//     }
// }

// void RR(struct jobs j[], int size)
// {
//     int slice = 1;
//     int done_size = 0, timer = 0;
//     int done[size];
//     int dur[size];
//     for (int i = 0; i < size; i++)
//     {
//         done[i] = 0;
//         dur[i] = j[i].processRunTime;
//     }
//     struct jobs *doneQ = malloc(sizeof(struct jobs));

//     while (done_size < size)
//     {
//         for (int i = 0; i < size; i++)
//         {
//             if (j[i].arrivalTime < timer && done[i] == 0)
//             {
//                 j[i].processRunTime -= slice;
//                 timer += 2;
//                 if (j[i].processRunTime <= 0)
//                 {
//                     done_size++;
//                     doneQ = realloc(doneQ, sizeof(struct jobs) * done_size);
//                     doneQ[done_size - 1] = j[i];
//                     done[i] = 1;
//                 }
//             }
//         }
//         timer++;
//     }
//     printf("Processes completed in this order using RR: \n");
//     printf("P_name PID    P_dur  P_arriv\n");
//     for (int i = 0; i < size; i++)
//     {
//         printf("%s\t%d\t%d\t%d\n", doneQ[i].processName, doneQ[i].PID, dur[i], doneQ[i].arrivalTime);
//     }
// }

/*

NOTE: All functions are running correctly in the main file but there are some integration issues when functions are called from other files.




*/

int main(int argc, char *argv[])
{

    FILE *file;
    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("File not found!\n");
        return 1;
    }

    char l[100];
    struct jobs *j = (struct jobs *)malloc(sizeof(struct jobs) * 20);
    int count = 0;

    while (fgets(l, sizeof(l), file))
    {
        // printf("%d\n", count);

        if (l[0] == '#' || l[0] == ' ')
            continue;
        else
        {
            // j = (struct jobs *)realloc(j, (sizeof(struct jobs) * (count + 1)));
            // printf("%s\n", l);
            sscanf(l, "%[^:]:%d:%d:%d", j[count].processName, &j[count].PID, &j[count].processRunTime, &j[count].arrivalTime);

            count++;
        }
    }

    // FIFO(j, count);

    // SJF(j, count);

    // STCF(j, count);

    // RR(j, count);
    return 0;
}
