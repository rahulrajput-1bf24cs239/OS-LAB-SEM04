#include<stdio.h>

int main()
{
    int n,i,time=0,count=0,smallest;
    float avgwt=0,avgtat=0,avgrt=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    int at[n],bt[n],rt[n],start[n];
    int wt[n],tat[n],resp[n];

    for(i=0;i<n;i++)
    {
        printf("\nProcess %d\n",i+1);
        printf("Arrival Time: ");
        scanf("%d",&at[i]);

        printf("Burst Time: ");
        scanf("%d",&bt[i]);

        rt[i]=bt[i];
        start[i]=-1;
    }

    while(count!=n)
    {
        smallest=-1;

        for(i=0;i<n;i++)
        {
            if(at[i]<=time && rt[i]>0)
            {
                if(smallest==-1 || rt[i]<rt[smallest])
                smallest=i;
            }
        }

        if(smallest!=-1)
        {
            if(start[smallest]==-1)
            start[smallest]=time;

            rt[smallest]--;
            time++;

            if(rt[smallest]==0)
            {
                count++;

                tat[smallest]=time-at[smallest];
                wt[smallest]=tat[smallest]-bt[smallest];
                resp[smallest]=start[smallest]-at[smallest];

                avgwt+=wt[smallest];
                avgtat+=tat[smallest];
                avgrt+=resp[smallest];
            }
        }
        else
        time++;
    }

    printf("\nP\tWT\tTAT\tRT\n");

    for(i=0;i<n;i++)
    printf("P%d\t%d\t%d\t%d\n",i+1,wt[i],tat[i],resp[i]);

    printf("\nAverage WT = %.2f",avgwt/n);
    printf("\nAverage TAT = %.2f",avgtat/n);
    printf("\nAverage RT = %.2f",avgrt/n);

    return 0;
}
