ANUSREE KJ
S4DS - ROLL NO:13
                        EXPERIMENT : MEMORY ALLOCATION
                                     ( FIRSTFIT , BESTFIT , WORSTFIT )
#include <stdio.h>

int main() 
{
    int m, n;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);

    int blockSize[m];

    printf("Enter the size of each block:\n");
    for (int i = 0; i < m; i++) 
    {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processSize[n];

    printf("Enter the size of each process:\n");
    for (int i = 0; i < n; i++) 
    {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }
    int firstFitBlockSize[m], bestFitBlockSize[m], worstFitBlockSize[m];

    for (int i = 0; i < m; i++) 
    {
        firstFitBlockSize[i] = blockSize[i];
        bestFitBlockSize[i] = blockSize[i];
        worstFitBlockSize[i] = blockSize[i];
    }

    firstFit(firstFitBlockSize, m, processSize, n);
    bestFit(bestFitBlockSize, m, processSize, n);
    worstFit(worstFitBlockSize, m, processSize, n);

    return 0;
}

void firstFit(int blockSize[], int m, int processSize[], int n) 
{
    int allocation[n];
    for (int i = 0; i < n; i++) 
    {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++) 
        {
            if (blockSize[j] >= processSize[i]) 
            {
                allocation[i] = j; 
                blockSize[j] = blockSize[j] - processSize[i]; 
                break;
            }
        }
    }

    printf("\nFirst Fit Algorithm:\n");
    for (int i = 0; i < n; i++) 
    {
        if (allocation[i] != -1) 
        {
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        } else 
        {
            printf("Process %d not allocated\n", i + 1);
        }
    }
}

void bestFit(int blockSize[], int m, int processSize[], int n) 
{
    int allocation[n];

    for (int i = 0; i < n; i++)  
    {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) 
    {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) 
        {
            if (blockSize[j] >= processSize[i]) 
            {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) 
                {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) 
        {
            allocation[i] = bestIdx;
            blockSize[bestIdx] = blockSize[bestIdx] - processSize[i];
        }
    }

    printf("\nBest Fit Algorithm:\n");
    for (int i = 0; i < n; i++) 
    {
        if (allocation[i] != -1) 
        {
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        } else {
            printf("Process %d not allocated\n", i + 1);
        }
    }
}

void worstFit(int blockSize[], int m, int processSize[], int n) 
{
    int allocation[n];
    for (int i = 0; i < n; i++) 
    {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) 
    {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) 
        {
            if (blockSize[j] >= processSize[i]) 
            {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) 
                {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) 
        {
            allocation[i] = worstIdx;
            blockSize[worstIdx] =  blockSize[worstIdx] - processSize[i];
        }
    }

    printf("\nWorst Fit Algorithm:\n");
    for (int i = 0; i < n; i++) 
    {
        if (allocation[i] != -1) 
        {
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        } 
        else 
        {
            printf("Process %d not allocated\n", i + 1);
        }
    }
}
