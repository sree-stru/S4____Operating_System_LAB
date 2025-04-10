#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10

int fifo(int pages[], int n, int frame_count) 
{
    int frames[MAX_FRAMES];
    int page_faults = 0;
    int i, j, flag;
    int oldest_page = 0;

    for (i = 0; i < frame_count; i++) 
        frames[i] = -1;

    printf("FIFO Page Replacement:\n");
    printf("Page Reference   Frames\n");
    printf("------------------------\n");

    for (i = 0; i < n; i++) 
    {
        flag = 0;
        for (j = 0; j < frame_count; j++) 
        {
            if (frames[j] == pages[i]) 
            {
                flag = 1;
                break;
            }
        }

        if (flag == 0) 
        {
            page_faults++;
            frames[oldest_page] = pages[i];
            oldest_page = (oldest_page + 1) % frame_count;
        }

        printf("    %2d           ", pages[i]);
        for (j = 0; j < frame_count; j++) 
        {
            if (frames[j] != -1) 
                printf("| %2d ", frames[j]);
            else 
                printf("|    ");
        }
        printf("|\n");
    }

    return page_faults;
}

int lru(int pages[], int n, int frame_count) 
{
    int frames[MAX_FRAMES];
    int time[MAX_FRAMES];
    int page_faults = 0;
    int i, j, flag, min_time, lru_index;

    for (i = 0; i < frame_count; i++) 
    {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("LRU Page Replacement:\n");
    printf("Page Reference   Frames\n");
    printf("------------------------\n");

    for (i = 0; i < n; i++) 
    {
        flag = 0;
        for (j = 0; j < frame_count; j++) 
        {
            if (frames[j] == pages[i]) 
            {
                flag = 1;
                time[j] = i + 1;
                break;
            }
        }

        if (flag == 0) 
        {
            page_faults++;
            min_time = i + 1;
            lru_index = 0;
            for (j = 0; j < frame_count; j++) 
            {
                if (frames[j] == -1) 
                {
                    frames[j] = pages[i];
                    time[j] = i + 1;
                    flag = 1;
                    break;
                }
                if (time[j] < min_time) 
                {
                    min_time = time[j];
                    lru_index = j;
                }
            }
            if (flag == 0)
            {
                frames[lru_index] = pages[i];
                time[lru_index] = i + 1;
            }
        }

        printf("    %2d           ", pages[i]);
        for (j = 0; j < frame_count; j++) 
        {
            if (frames[j] != -1)
                printf("| %2d ", frames[j]);
            else
                printf("|    ");
        }
        printf("|\n");
    }

    return page_faults;
}

int optimal(int pages[], int n, int frame_count) 
{
    int frames[MAX_FRAMES];
    int page_faults = 0;
    int i, j, k, flag, farthest, replace_index;

    for (i = 0; i < frame_count; i++) 
        frames[i] = -1;

    printf("Optimal Page Replacement:\n");
    printf("Page Reference   Frames\n");
    printf("------------------------\n");

    for (i = 0; i < n; i++) 
    {
        flag = 0;
        for (j = 0; j < frame_count; j++) 
        {
            if (frames[j] == pages[i]) 
            {
                flag = 1;
                break;
            }
        }

        if (flag == 0) 
        {
            page_faults++;
            flag = 0;
            for (j = 0; j < frame_count; j++)
            {
                if (frames[j] == -1)
                {
                    frames[j] = pages[i];
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                farthest = i;
                replace_index = 0;
                for (j = 0; j < frame_count; j++)
                {
                    int found_next = 0;
                    for (k = i + 1; k < n; k++)
                    {
                        if (frames[j] == pages[k])
                        {
                            found_next = 1;
                            if (k > farthest)
                            {
                                farthest = k;
                                replace_index = j;
                            }
                            break;
                        }
                    }
                    if (found_next == 0)
                    {
                        replace_index = j;
                        break;
                    }
                }
                frames[replace_index] = pages[i];
            }
        }

        printf("    %2d           ", pages[i]);
        for (j = 0; j < frame_count; j++) 
        {
            if (frames[j] != -1)
                printf("| %2d ", frames[j]);
            else
                printf("|    ");
        }
        printf("|\n");
    }

    return page_faults;
}

int main() 
{
    int n, frame_count, choice;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];

    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &pages[i]);
    }

    do {
        printf("\nMenu:\n");
        printf("1. FIFO Page Replacement\n");
        printf("2. LRU Page Replacement\n");
        printf("3. Optimal Page Replacement\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                printf("Enter the number of frames: ");
                scanf("%d", &frame_count);
                printf("Total Page Faults in FIFO: %d\n", fifo(pages, n, frame_count));
                break;
            case 2:
                printf("Enter the number of frames: ");
                scanf("%d", &frame_count);
                printf("Total Page Faults in LRU: %d\n", lru(pages, n, frame_count));
                break;
            case 3:
                printf("Enter the number of frames: ");
                scanf("%d", &frame_count);
                printf("Total Page Faults in Optimal: %d\n", optimal(pages, n, frame_count));
                break;
            case 4:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
