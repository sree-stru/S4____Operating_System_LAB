#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

void printRequestString(int req[], int n) {
    printf("\nRequest Queue: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", req[i]);
    }
    printf("\n");
}

void printSeekOrder(int seekOrder[], int seekCount) {
    printf("Seek Order: ");
    for (int i = 0; i < seekCount; i++) {
        printf("%d ", seekOrder[i]);
    }
    printf("\n");
}

void FCFS(int req[], int n, int head) 
{
    int seek = 0;
    int seekOrder[MAX], count = 0;
    printf("\n--- FCFS (First Come First Serve) ---\n");
    printf("Head movements:\n");
    for (int i = 0; i < n; i++) 
    {
        seekOrder[count++] = req[i];
        printf("Move from %d to %d --> Seek: %d\n", head, req[i], abs(req[i] - head));
        seek += abs(req[i] - head);
        head = req[i];
    }
    printf("Total Seek Time: %d\n", seek);
    printSeekOrder(seekOrder, count);
}

void SSTF(int req[], int n, int head) {
    int seek = 0, done[MAX] = {0}, count = 0;
    int seekOrder[MAX], seekCount = 0;
    printf("\n--- SSTF (Shortest Seek Time First) ---\n");
    printf("Head movements:\n");
    while (count < n) 
    {
        int min = 9999, index = -1;
        // Loop through all disk requests to find the closest one
     for (int i = 0; i < n; i++) 
     {
    // Check if this request has not been processed yet
       if (!done[i] && abs(req[i] - head) < min)
       {
        // If the distance from current head to this request is smaller than the current minimum
        // Update minimum distance
        min = abs(req[i] - head);

        // Store the index of the closest request found so far
        index = i;
        }
     }
        seekOrder[seekCount++] = req[index];
        printf("Move from %d to %d --> Seek: %d\n", head, req[index], min);
        seek += min;
        head = req[index];
        done[index] = 1;
        count++;
    }
    printf("Total Seek Time: %d\n", seek);
    printSeekOrder(seekOrder, seekCount);
}

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                int t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
        }
    }
}

void SCAN(int req[], int n, int head, int disk_size) 
{
    int left[MAX], right[MAX], l = 0, r = 0, seek = 0;
    int seekOrder[MAX], seekCount = 0;

    for (int i = 0; i < n; i++) 
    {
        if (req[i] < head)
            left[l++] = req[i];
        else
            right[r++] = req[i];
    }

    sort(left, l);
    sort(right, r);

    printf("\n--- SCAN (Elevator) ---\n");
    printf("Head movements:\n");

    for (int i = l - 1; i >= 0; i--) 
    {
        seekOrder[seekCount++] = left[i];
        printf("Move from %d to %d --> Seek: %d\n", head, left[i], abs(left[i] - head));
        seek += abs(left[i] - head);
        head = left[i];
    }

    if (head != 0) 
    {
        seekOrder[seekCount++] = 0;
        printf("Move from %d to 0 --> Seek: %d\n", head, head);
        seek += head;
        head = 0;
    }

    for (int i = 0; i < r; i++) 
    {
        seekOrder[seekCount++] = right[i];
        printf("Move from %d to %d --> Seek: %d\n", head, right[i], abs(right[i] - head));
        seek += abs(right[i] - head);
        head = right[i];
    }

    printf("Total Seek Time: %d\n", seek);
    printSeekOrder(seekOrder, seekCount);
}

void CSCAN(int req[], int n, int head, int disk_size) {
    int left[MAX], right[MAX], l = 0, r = 0, seek = 0;
    int seekOrder[MAX], seekCount = 0;

    for (int i = 0; i < n; i++) {
        if (req[i] < head)
            left[l++] = req[i];
        else
            right[r++] = req[i];
    }
    sort(left, l);
    sort(right, r);

    printf("\n--- C-SCAN (Circular SCAN) ---\n");
    printf("Head movements:\n");

    for (int i = 0; i < r; i++) {
        seekOrder[seekCount++] = right[i];
        printf("Move from %d to %d --> Seek: %d\n", head, right[i], abs(right[i] - head));
        seek += abs(right[i] - head);
        head = right[i];
    }

    if (head != disk_size - 1) {
        seekOrder[seekCount++] = disk_size - 1;
        printf("Move from %d to %d (End) --> Seek: %d\n", head, disk_size - 1, abs(disk_size - 1 - head));
        seek += abs(disk_size - 1 - head);
        head = 0;
        printf("Jump from %d to 0 --> Seek: %d\n", disk_size - 1, disk_size - 1);
        seek += disk_size - 1;
    }

    for (int i = 0; i < l; i++) {
        seekOrder[seekCount++] = left[i];
        printf("Move from %d to %d --> Seek: %d\n", head, left[i], abs(head - left[i]));
        seek += abs(head - left[i]);
        head = left[i];
    }

    printf("Total Seek Time: %d\n", seek);
    printSeekOrder(seekOrder, seekCount);
}

void LOOK(int req[], int n, int head) {
    int left[MAX], right[MAX], l = 0, r = 0, seek = 0;
    int seekOrder[MAX], seekCount = 0;

    for (int i = 0; i < n; i++) {
        if (req[i] < head)
            left[l++] = req[i];
        else
            right[r++] = req[i];
    }
    sort(left, l);
    sort(right, r);

    printf("\n--- LOOK ---\n");
    printf("Head movements:\n");

    for (int i = 0; i < r; i++) {
        seekOrder[seekCount++] = right[i];
        printf("Move from %d to %d --> Seek: %d\n", head, right[i], abs(right[i] - head));
        seek += abs(right[i] - head);
        head = right[i];
    }

    for (int i = l - 1; i >= 0; i--) {
        seekOrder[seekCount++] = left[i];
        printf("Move from %d to %d --> Seek: %d\n", head, left[i], abs(head - left[i]));
        seek += abs(head - left[i]);
        head = left[i];
    }
    printf("Total Seek Time: %d\n", seek);
    printSeekOrder(seekOrder, seekCount);
}

void CLOOK(int req[], int n, int head) {
    int left[MAX], right[MAX], l = 0, r = 0, seek = 0;
    int seekOrder[MAX], seekCount = 0;

    for (int i = 0; i < n; i++) {
        if (req[i] < head)
            left[l++] = req[i];
        else
            right[r++] = req[i];
    }
    sort(left, l);
    sort(right, r);

    printf("\n--- C-LOOK ---\n");
    printf("Head movements:\n");

    for (int i = 0; i < r; i++) {
        seekOrder[seekCount++] = right[i];
        printf("Move from %d to %d --> Seek: %d\n", head, right[i], abs(right[i] - head));
        seek += abs(right[i] - head);
        head = right[i];
    }

    if (l > 0) {
        seekOrder[seekCount++] = left[0];
        printf("Jump from %d to %d --> Seek: %d\n", head, left[0], abs(head - left[0]));
        seek += abs(head - left[0]);
        head = left[0];
    }

    for (int i = 0; i < l; i++) {
        seekOrder[seekCount++] = left[i];
        printf("Move from %d to %d --> Seek: %d\n", head, left[i], abs(head - left[i]));
        seek += abs(head - left[i]);
        head = left[i];
    }

    printf("Total Seek Time: %d\n", seek);
    printSeekOrder(seekOrder, seekCount);
}

int main() 
{
    int req[MAX], n, head, disk_size;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    printf("Enter the request sequence: ");
    for (int i = 0; i < n; i++) 
    scanf("%d", &req[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter total disk size (number of cylinders): ");
    scanf("%d", &disk_size);

    printRequestString(req, n);
    FCFS(req, n, head);
    SSTF(req, n, head);
    SCAN(req, n, head, disk_size);
    CSCAN(req, n, head, disk_size);
    LOOK(req, n, head);
    CLOOK(req, n, head);

    return 0;
}
