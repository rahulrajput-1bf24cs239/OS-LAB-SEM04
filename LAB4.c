#include <stdio.h>
#include <math.h>

#define MAX 10

typedef struct {
    int id;
    int burst;
    int deadline;
    int period;
    int weight;
    int ct, wt, tat;
} Process;

/* ---------- Sorting Functions ---------- */
void sortByDeadline(Process p[], int n) {
    for(int i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++)
            if(p[i].deadline > p[j].deadline) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
}

void sortByPeriod(Process p[], int n) {
    for(int i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++)
            if(p[i].period > p[j].period) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
}

/* ---------- EDF ---------- */
void EDF(Process p[], int n) {
    Process temp[MAX];
    for(int i=0;i<n;i++) temp[i] = p[i];

    sortByDeadline(temp, n);

    float util = 0;
    for(int i=0;i<n;i++)
        util += (float)temp[i].burst / temp[i].deadline;

    printf("\n===== Earliest Deadline First (EDF) Scheduling =====\n");
    printf("CPU Utilization: %.2f\n", util);

    if(util <= 1.0)
        printf("Schedulable (Utilization <= 1)\n");
    else
        printf("Not Schedulable\n");

    int time = 0;
    printf("ID  BF  Deadline  CT  WT  TAT\n");

    for(int i=0;i<n;i++) {
        time += temp[i].burst;
        temp[i].ct = time;
        temp[i].tat = temp[i].ct;
        temp[i].wt = temp[i].tat - temp[i].burst;

        printf("%d   %d     %d      %d   %d   %d\n",
               temp[i].id, temp[i].burst, temp[i].deadline,
               temp[i].ct, temp[i].wt, temp[i].tat);
    }
}

/* ---------- RMS ---------- */
void RMS(Process p[], int n) {
    Process temp[MAX];
    for(int i=0;i<n;i++) temp[i] = p[i];

    sortByPeriod(temp, n);

    float util = 0;
    for(int i=0;i<n;i++)
        util += (float)temp[i].burst / temp[i].period;

    float rmBound = n * (pow(2.0, 1.0/n) - 1);

    printf("\n===== Rate Monotonic Scheduling (RMS) =====\n");
    printf("CPU Utilization: %.2f\n", util);
    printf("RM Bound: %.4f\n", rmBound);

    if(util <= rmBound)
        printf("Schedulable (Utilization <= RM Bound)\n");
    else
        printf("May Not Be Schedulable\n");

    int time = 0;
    printf("ID  BF  Period  CT  WT  TAT\n");

    for(int i=0;i<n;i++) {
        time += temp[i].burst;
        temp[i].ct = time;
        temp[i].tat = temp[i].ct;
        temp[i].wt = temp[i].tat - temp[i].burst;

        printf("%d   %d    %d     %d   %d   %d\n",
               temp[i].id, temp[i].burst, temp[i].period,
               temp[i].ct, temp[i].wt, temp[i].tat);
    }
}

/* ---------- Proportional Scheduling ---------- */
void Proportional(Process p[], int n) {
    int totalWeight = 0;

    for(int i=0;i<n;i++)
        totalWeight += p[i].weight;

    printf("\n===== Proportional Scheduling =====\n");
    printf("ID  Weight  CPU Share(%%)\n");

    for(int i=0;i<n;i++) {
        float share = ((float)p[i].weight / totalWeight) * 100;

        printf("%d    %d      %.2f%%\n",
               p[i].id, p[i].weight, share);
    }
}

/* ---------- Main ---------- */
int main() {
    Process p[MAX];
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter process details:\n");

    for(int i=0;i<n;i++) {
        p[i].id = i;

        printf("\nProcess %d:\n", i);

        printf("Burst Time: ");
        scanf("%d", &p[i].burst);

        printf("Deadline (for EDF): ");
        scanf("%d", &p[i].deadline);

        printf("Period (for RMS): ");
        scanf("%d", &p[i].period);

        printf("Weight (for Proportional): ");
        scanf("%d", &p[i].weight);
    }

    EDF(p, n);
    RMS(p, n);
    Proportional(p, n);

    return 0;
}
