#include <stdio.h>
#include <stdlib.h>

void allocatePages(int memorySize, int pageSize, int numProcesses, int processSizes[]);

int main() 
{
    int memorySize, pageSize, numProcesses;
    
    printf("Enter the total memory size (in KB): ");
    scanf("%d", &memorySize);
    
    printf("Enter the page size (in KB): ");
    scanf("%d", &pageSize);
    
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);
    
    int processSizes[numProcesses];
    
    for(int i = 0; i < numProcesses; i++) 
    {
        printf("Enter the size of process %d (in KB): ", i + 1);
        scanf("%d", &processSizes[i]);
    }
    
    
    allocatePages(memorySize, pageSize, numProcesses, processSizes);
    
    return 0;
}

void allocatePages(int memorySize, int pageSize, int numProcesses, int processSizes[]) 
{
    int totalPages = memorySize / pageSize;  
    int pageCounter = 0;  
    
    printf("\nTotal pages available in memory: %d\n", totalPages);
    
    for(int i = 0; i < numProcesses; i++) 
    {
        int processSize = processSizes[i];
        int requiredPages = (processSize + pageSize - 1) / pageSize;  
        
        printf("\nProcess %d size: %d KB requires %d pages.\n", i + 1, processSize, requiredPages);
        
        if (requiredPages <= totalPages) 
        {
            printf("Process %d allocated to pages: ", i + 1);
            
            for(int j = 0; j < requiredPages; j++) 
            {
                printf("%d ", pageCounter);
                pageCounter++;
                totalPages--;  
            }
            printf("\nRemaining pages in memory: %d\n", totalPages);
        } 
        else 
        {
            printf("Process %d cannot be allocated due to insufficient memory. Needed: %d pages, Available: %d pages.\n", i + 1, requiredPages, totalPages);
        }
    }
}
