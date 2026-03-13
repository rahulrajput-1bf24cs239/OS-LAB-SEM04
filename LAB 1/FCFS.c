#include<stdio.h>

int main()
{
    int n,i;
    float avgwt=0,avgtat=0,avgrt=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    int at[n],bt[n],wt[n],tat[n],rt[n];

    for(i=0;i<n;i++)
    {
        printf("\nProcess %d\n",i+1);
        printf("Arrival Time: ");
        scanf("%d",&at[i]);
        printf("Burst Time: ");
        scanf("%d",&bt[i]);
    }

    wt[0]=0;
    rt[0]=0;

    for(i=1;i<n;i++)
    {
        wt[i]=wt[i-1]+bt[i-1];
        rt[i]=wt[i];
    }

    for(i=0;i<n;i++)
    {
        tat[i]=wt[i]+bt[i];
        avgwt+=wt[i];
        avgtat+=tat[i];
        avgrt+=rt[i];
    }

    printf("\nP\tAT\tBT\tWT\tTAT\tRT\n");

    for(i=0;i<n;i++)
    printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],wt[i],tat[i],rt[i]);

    printf("\nAverage WT = %.2f",avgwt/n);
    printf("\nAverage TAT = %.2f",avgtat/n);
    printf("\nAverage RT = %.2f",avgrt/n);

    return 0;
}
