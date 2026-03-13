#include<stdio.h>

int main()
{
    int n,i,time=0,completed=0,highest;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    int at[n],bt[n],rt[n],pr[n];
    int wt[n],tat[n],rtm[n],start[n];

    float avgwt=0,avgtat=0,avgrt=0;

    for(i=0;i<n;i++)
    {
        printf("\nProcess %d\n",i+1);

        printf("Arrival Time: ");
        scanf("%d",&at[i]);

        printf("Burst Time: ");
        scanf("%d",&bt[i]);

        printf("Priority: ");
        scanf("%d",&pr[i]);

        rt[i]=bt[i];
        start[i]=-1;
    }

    while(completed<n)
    {
        highest=-1;

        for(i=0;i<n;i++)
        {
            if(at[i]<=time && rt[i]>0)
            {
                if(highest==-1 || pr[i]<pr[highest])
                    highest=i;
            }
        }

        if(highest!=-1)
        {
            if(start[highest]==-1)
                start[highest]=time;

            rt[highest]--;
            time++;

            if(rt[highest]==0)
            {
                completed++;

                tat[highest]=time-at[highest];
                wt[highest]=tat[highest]-bt[highest];
                rtm[highest]=start[highest]-at[highest];

                avgwt+=wt[highest];
                avgtat+=tat[highest];
                avgrt+=rtm[highest];
            }
        }
        else
        {
            time++;
        }
    }

    printf("\nP\tAT\tBT\tPR\tWT\tTAT\tRT\n");

    for(i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,at[i],bt[i],pr[i],wt[i],tat[i],rtm[i]);
    }

    printf("\nAverage Waiting Time = %.2f",avgwt/n);
    printf("\nAverage Turnaround Time = %.2f",avgtat/n);
    printf("\nAverage Response Time = %.2f",avgrt/n);

    return 0;
}
