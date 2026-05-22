#include <stdio.h>

void fifo(int pages[], int n, int frames)
{
    int frame[10], i, j, k = 0, fault = 0, found;

    for(i = 0; i < frames; i++)
        frame[i] = -1;

    printf("\nFIFO Page Replacement\n");

    for(i = 0; i < n; i++)
    {
        found = 0;

        for(j = 0; j < frames; j++)
        {
            if(frame[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if(found == 0)
        {
            frame[k] = pages[i];
            k = (k + 1) % frames;
            fault++;
        }

        printf("\n%d -> ", pages[i]);

        for(j = 0; j < frames; j++)
        {
            if(frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
    }

    printf("\nTotal Page Faults = %d\n", fault);
}

void lru(int pages[], int n, int frames)
{
    int frame[10], time[10];
    int i, j, pos, fault = 0, found, min, counter = 0;

    for(i = 0; i < frames; i++)
    {
        frame[i] = -1;
        time[i] = 0;
    }

    printf("\nLRU Page Replacement\n");

    for(i = 0; i < n; i++)
    {
        found = 0;

        for(j = 0; j < frames; j++)
        {
            if(frame[j] == pages[i])
            {
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }

        if(found == 0)
        {
            min = time[0];
            pos = 0;

            for(j = 1; j < frames; j++)
            {
                if(time[j] < min)
                {
                    min = time[j];
                    pos = j;
                }
            }

            counter++;
            frame[pos] = pages[i];
            time[pos] = counter;
            fault++;
        }

        printf("\n%d -> ", pages[i]);

        for(j = 0; j < frames; j++)
        {
            if(frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
    }

    printf("\nTotal Page Faults = %d\n", fault);
}

void optimal(int pages[], int n, int frames)
{
    int frame[10];
    int i, j, k, pos, fault = 0, found;
    int farthest, index;

    for(i = 0; i < frames; i++)
        frame[i] = -1;

    printf("\nOptimal Page Replacement\n");

    for(i = 0; i < n; i++)
    {
        found = 0;

        for(j = 0; j < frames; j++)
        {
            if(frame[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if(found == 0)
        {
            pos = -1;
            farthest = i + 1;

            for(j = 0; j < frames; j++)
            {
                index = -1;

                for(k = i + 1; k < n; k++)
                {
                    if(frame[j] == pages[k])
                    {
                        index = k;
                        break;
                    }
                }

                if(index == -1)
                {
                    pos = j;
                    break;
                }

                if(index > farthest)
                {
                    farthest = index;
                    pos = j;
                }
            }

            if(pos == -1)
                pos = 0;

            frame[pos] = pages[i];
            fault++;
        }

        printf("\n%d -> ", pages[i]);

        for(j = 0; j < frames; j++)
        {
            if(frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
    }

    printf("\nTotal Page Faults = %d\n", fault);
}

int main()
{
    int pages[50], n, frames, choice, i;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("\n1. FIFO");
    printf("\n2. LRU");
    printf("\n3. Optimal");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            fifo(pages, n, frames);
            break;

        case 2:
            lru(pages, n, frames);
            break;

        case 3:
            optimal(pages, n, frames);
            break;

        default:
            printf("Invalid choice");
    }

    return 0;
}
