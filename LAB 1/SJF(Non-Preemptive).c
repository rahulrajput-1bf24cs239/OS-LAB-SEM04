#include<stdio.h>

int main()
{
    int n,i,j,temp;
    float avgwt=0,avgtat=0,avgrt=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    int bt[n],wt[n],tat[n],rt[n],p[n];

    for(i=0;i<n;i++)
    {
        p[i]=i+1;
        printf("Burst Time of P%d: ",i+1);
        scanf("%d",&bt[i]);
    }

    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(bt[i]>bt[j])
            {
                temp=bt[i]; bt[i]=bt[j]; bt[j]=temp;
                temp=p[i]; p[i]=p[j]; p[j]=temp;
            }
        }
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

    printf("\nP\tBT\tWT\tTAT\tRT\n");

    for(i=0;i<n;i++)
    printf("P%d\t%d\t%d\t%d\t%d\n",p[i],bt[i],wt[i],tat[i],rt[i]);

    printf("\nAverage WT = %.2f",avgwt/n);
    printf("\nAverage TAT = %.2f",avgtat/n);
    printf("\nAverage RT = %.2f",avgrt/n);

    return 0;
}
