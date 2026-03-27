#include <stdio.h>

int main() {
    int n, i, time = 0, remain, quantum;
    int bt[20], wt[20], tat[20], rt[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    remain = n;

    printf("Enter burst time for each process:\n");
    for(i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    int done;
    while(remain != 0) {
        done = 1;

        for(i = 0; i < n; i++) {
            if(rt[i] > 0) {
                done = 0;

                if(rt[i] > quantum) {
                    time += quantum;
                    rt[i] -= quantum;
                } else {
                    time += rt[i];
                    wt[i] = time - bt[i];
                    rt[i] = 0;
                    remain--;
                }
            }
        }

        if(done == 1)
            break;
    }

    for(i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }

    float total_wt = 0, total_tat = 0;

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
