#include <stdio.h>

int main() {
    int n, m, i, j, k;

    printf("Processes: ");
    scanf("%d", &n);

    printf("Resources: ");
    scanf("%d", &m);

    int alloc[n][m], req[n][m], avail[m];
    int finish[n], work[m];

    printf("Enter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Request Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &req[i][j]);

    printf("Enter Available Resources:\n");
    for(i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
        work[i] = avail[i];
    }

    for(i = 0; i < n; i++)
        finish[i] = 0;

    for(k = 0; k < n; k++) {
        for(i = 0; i < n; i++) {

            if(finish[i] == 0) {

                for(j = 0; j < m; j++)
                    if(req[i][j] > work[j])
                        break;

                if(j == m) {
                    for(j = 0; j < m; j++)
                        work[j] += alloc[i][j];

                    finish[i] = 1;
                }
            }
        }
    }

    printf("Deadlocked Processes: ");
    int c=0;

    for(i = 0; i < n; i++)
        if(finish[i] == 0)
            printf("P%d ", i);
            c+=1;

    printf("\n");
if(c=0){
        printf("No deadlock detected. All processes can finish");
}
 return 0;
}

