#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int id;
    int at;   // arrival time
    int bt;   // burst time
    int rt;   // remaining time
    int type; // 0 = system, 1 = user
    int ct;   // completion time
    int wt;
    int tat;
} Process;

Process p[MAX];

// Queue structure
int sysQ[MAX], userQ[MAX];
int frontS = 0, rearS = 0;
int frontU = 0, rearU = 0;

void enqueueSys(int x) {
    sysQ[rearS++] = x;
}

int dequeueSys() {
    return sysQ[frontS++];
}

void enqueueUser(int x) {
    userQ[rearU++] = x;
}

int dequeueUser() {
    return userQ[frontU++];
}

int isSysEmpty() {
    return frontS == rearS;
}

int isUserEmpty() {
    return frontU == rearU;
}

// Sort by arrival time
void sort(Process p[], int n) {
    Process temp;
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(p[j].at > p[j+1].at) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i);
        p[i].id = i;

        printf("Enter arrival time: ");
        scanf("%d", &p[i].at);

        printf("Enter burst time: ");
        scanf("%d", &p[i].bt);

        printf("Enter type (0 = System, 1 = User): ");
        scanf("%d", &p[i].type);

        p[i].rt = p[i].bt;
    }

    sort(p, n);

    int time = 0, completed = 0, i = 0;
    int current = -1; // index of current process

    while(completed < n) {

        // Add arrived processes to queues
        while(i < n && p[i].at <= time) {
            if(p[i].type == 0)
                enqueueSys(i);
            else
                enqueueUser(i);
            i++;
        }

        // Preemption
        if(current != -1) {
            if(p[current].type == 1 && !isSysEmpty()) {
                enqueueUser(current);
                current = -1;
            }
        }

        // Select process
        if(current == -1) {
            if(!isSysEmpty())
                current = dequeueSys();
            else if(!isUserEmpty())
                current = dequeueUser();
            else {
                time++;
                continue;
            }
        }

        // Execute for 1 unit
        p[current].rt--;
        time++;

        // Completion check
        if(p[current].rt == 0) {
            p[current].ct = time;
            p[current].tat = p[current].ct - p[current].at;
            p[current].wt = p[current].tat - p[current].bt;

            completed++;
            current = -1;
        }
    }

    // Output
    float avgWT = 0, avgTAT = 0;

    printf("\nID\tType\tAT\tBT\tCT\tWT\tTAT\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
            p[i].id,
            (p[i].type == 0) ? "System" : "User",
            p[i].at,
            p[i].bt,
            p[i].ct,
            p[i].wt,
            p[i].tat);

        avgWT += p[i].wt;
        avgTAT += p[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f", avgWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgTAT / n);

    return 0;
}
