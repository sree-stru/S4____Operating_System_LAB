#include <stdio.h>

#define MAX 100

struct Process {
    int id, at, bt, bt_remaining, priority;
    int ct, wt, tat, completed;
};

void printTable(struct Process p[], int n) {
    int total_wt = 0, total_tat = 0;
    printf("\nProcess Table:\n");
    printf("| PID | Arrival Time | Burst Time | Priority | Completion | Turnaround | Waiting |\n");

    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        total_tat += p[i].tat;
        total_wt += p[i].wt;

        printf("| %3d | %12d | %10d | %8d | %10d | %10d | %7d |\n",
               p[i].id, p[i].at, p[i].bt, p[i].priority, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
}

void sortByArrival(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void FCFS(struct Process p[], int n) {
    int time = 0;
    printf("\nGantt Chart (FCFS): ");
    for (int i = 0; i < n; i++) {
        if (time < p[i].at) {
            time = p[i].at;
        }
        printf("| P%d ", p[i].id);
        time += p[i].bt;
        p[i].ct = time;
    }
    printf("|\n");
    printTable(p, n);
}

void SJF_NonPreemptive(struct Process p[], int n) {
    int completed = 0, time = 0;
    printf("\nGantt Chart (SJF Non-Preemptive): ");
    while (completed < n) {
        int min_bt = 9999, idx = -1;
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= time && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        printf("| P%d ", p[idx].id);
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].completed = 1;
        completed++;
    }
    printf("|\n");
    printTable(p, n);
}

void SRTF(struct Process p[], int n) {
    int completed = 0, time = 0;
    printf("\nGantt Chart (SRTF): ");
    while (completed < n) {
        int min_bt = 9999, idx = -1;
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= time && p[i].bt_remaining > 0 && p[i].bt_remaining < min_bt) {
                min_bt = p[i].bt_remaining;
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        printf("| P%d ", p[idx].id);
        p[idx].bt_remaining--;
        time++;
        if (p[idx].bt_remaining == 0) {
            p[idx].ct = time;
            p[idx].completed = 1;
            completed++;
        }
    }
    printf("|\n");
    printTable(p, n);
}

void RoundRobin(struct Process p[], int n, int quantum) {
    int time = 0, completed = 0;
    printf("\nGantt Chart (Round Robin, Q=%d): ", quantum);
    while (completed < n) {
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].bt_remaining > 0 && p[i].at <= time) {
                printf("| P%d ", p[i].id);
                if (p[i].bt_remaining <= quantum) {
                    time += p[i].bt_remaining;
                    p[i].bt_remaining = 0;
                    p[i].ct = time;
                    p[i].completed = 1;
                    completed++;
                } else {
                    time += quantum;
                    p[i].bt_remaining -= quantum;
                }
                executed = 1;
            }
        }
        if (!executed) time++;
    }
    printf("|\n");
    printTable(p, n);
}

void Priority_NonPreemptive(struct Process p[], int n) {
    int completed = 0, time = 0;
    printf("\nGantt Chart (Priority Non-Preemptive): ");
    while (completed < n) {
        int highest_priority = 9999, idx = -1;
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= time && p[i].priority < highest_priority) {
                highest_priority = p[i].priority;
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        printf("| P%d ", p[idx].id);
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].completed = 1;
        completed++;
    }
    printf("|\n");
    printTable(p, n);
}

void Priority_Preemptive(struct Process p[], int n) {
    int completed = 0, time = 0;
    printf("\nGantt Chart (Priority Preemptive): ");
    while (completed < n) {
        int highest_priority = 9999, idx = -1;
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= time && p[i].priority < highest_priority && p[i].bt_remaining > 0) {
                highest_priority = p[i].priority;
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        printf("| P%d ", p[idx].id);
        p[idx].bt_remaining--;
        time++;
        if (p[idx].bt_remaining == 0) {
            p[idx].ct = time;
            p[idx].completed = 1;
            completed++;
        }
    }
    printf("|\n");
    printTable(p, n);
}

int main() {
    int n, quantum, choice;
    struct Process p[MAX];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Priority: ");
        scanf("%d", &p[i].priority);

        p[i].id = i + 1;
        p[i].bt_remaining = p[i].bt;
        p[i].completed = 0;
    }

    printf("\nEnter time quantum for Round Robin: ");
    scanf("%d", &quantum);

    sortByArrival(p, n);

    do {
        printf("\nCPU Scheduling Algorithms:\n");
        printf("1. FCFS\n2. SJF (Non-Preemptive)\n3. SRTF\n4. Round Robin\n5. Priority (Non-Preemptive)\n6. Priority (Preemptive)\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        for (int i = 0; i < n; i++) {
            p[i].bt_remaining = p[i].bt;
            p[i].completed = 0;
            p[i].ct = p[i].wt = p[i].tat = 0;
        }

        switch (choice) {
            case 1: FCFS(p, n); break;
            case 2: SJF_NonPreemptive(p, n); break;
            case 3: SRTF(p, n); break;
            case 4: RoundRobin(p, n, quantum); break;
            case 5: Priority_NonPreemptive(p, n); break;
            case 6: Priority_Preemptive(p, n); break;
            case 7: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }

    } while (choice != 7);

    return 0;
}
