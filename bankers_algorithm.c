#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int max_demand[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
bool finished[MAX_PROCESSES];

int num_processes, num_resources;

bool is_safe() 
{
    int work[num_resources];
    bool finish[num_processes];
    
    for (int i = 0; i < num_resources; ++i)
        work[i] = available[i];
    for (int i = 0; i < num_processes; ++i)
        finish[i] = false;

    int count = 0;
    while (count < num_processes) 
    {
        bool found = false;
        for (int i = 0; i < num_processes; ++i) 
        {
            if (!finish[i]) 
            {
                int j;
                for (j = 0; j < num_resources; ++j) 
                {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == num_resources) 
                {
                    for (int k = 0; k < num_resources; ++k)
                    {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found)
            return false;
    }
    return true;
}

void print_safe_sequence(int safe_sequence[]) 
{
    printf("Safe sequence: ");
    for (int i = 0; i < num_processes; ++i)
    {
        printf("%d ", safe_sequence[i]);
    }
    printf("\n");
}

void input_data() 
{
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter available resources:\n");
    for (int i = 0; i < num_resources; ++i)
    {
        scanf("%d", &available[i]);
    }

    printf("Enter allocation matrix:\n");
    for (int i = 0; i < num_processes; ++i)
    {
        for (int j = 0; j < num_resources; ++j)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter maximum demand matrix:\n");
    for (int i = 0; i < num_processes; ++i)
        for (int j = 0; j < num_resources; ++j) 
        {
            scanf("%d", &max_demand[i][j]);
            need[i][j] = max_demand[i][j] - allocation[i][j];
        }
}

void print_need_matrix() 
{
    printf("Need matrix:\n");
    for (int i = 0; i < num_processes; ++i) 
    {
        for (int j = 0; j < num_resources; ++j)
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

void check_safety() 
{
    if (is_safe()) 
    {
        printf("The system is safe.\n");
    } else 
    {
        printf("The system is unsafe.\n");
    }
}

void find_safe_sequence() 
{
    int safe_sequence[MAX_PROCESSES];
    int seq_count = 0;

    for (int i = 0; i < num_processes; ++i)
    {
    finished[i] = false;
    }
    while (seq_count < num_processes) 
    {
        for (int i = 0; i < num_processes; ++i) 
        {
            if (!finished[i]) 
            {
                bool can_run = true;
                for (int j = 0; j < num_resources; ++j) 
                {
                    if (need[i][j] > available[j]) 
                    {
                        can_run = false;
                        break;
                    }
                }
                if (can_run) 
                {
                    for (int j = 0; j < num_resources; ++j)
                    {
                        available[j] += allocation[i][j];
                    }
                    finished[i] = true;
                    safe_sequence[seq_count++] = i;
                }
            }
        }
    }
    print_safe_sequence(safe_sequence);
}

bool request_resources(int process_id, int request[]) 
{
    for (int i = 0; i < num_resources; ++i) 
    {
        if (request[i] > need[process_id][i]) 
        {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
    }

    
    for (int i = 0; i < num_resources; ++i) 
    {
        if (request[i] > available[i]) 
        {
            printf("Error: Not enough resources available.\n");
            return false;
        }
    }

    
    for (int i = 0; i < num_resources; ++i) 
    {
        available[i] -= request[i];
        allocation[process_id][i] += request[i];
        need[process_id][i] -= request[i];
    }

  
    if (is_safe()) 
    {
        printf("Request granted.\n");
        return true;
    } else 
    {
       
        for (int i = 0; i < num_resources; ++i) 
        {
            available[i] += request[i];
            allocation[process_id][i] -= request[i];
            need[process_id][i] += request[i];
        }
        printf("Request denied: System would be in an unsafe state.\n");
        return false;
    }
}

void handle_request() 
{
    int process_id, request[MAX_RESOURCES];

    printf("Enter process ID for resource request: ");
    scanf("%d", &process_id);
    printf("Enter the requested resources for each resource type:\n");
    for (int i = 0; i < num_resources; ++i)
    {
        scanf("%d", &request[i]);
    }
    if (process_id < 0 || process_id >= num_processes) 
    {
        printf("Invalid process ID.\n");
        return;
    }

    if (!request_resources(process_id, request)) 
    {
        printf("Request denied.\n");
    }
}

int main() 
{
    int choice;
    do
    {
        printf("\nMenu:\n");
        printf("1. Input data\n");
        printf("2. Check system safety\n");
        printf("3. Find safe sequence\n");
        printf("4. Handle resource request\n");
        printf("5. Re-enter resource allocation\n");
        printf("6. Print Need matrix\n");  
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                input_data();
                break;
            case 2:
                check_safety();
                break;
            case 3:
                find_safe_sequence();
                break;
            case 4:
                handle_request();
                break;
            case 5:
                printf("Re-enter resource allocation and data.\n");
                input_data();  
                break;
            case 6: 
                print_need_matrix();  // Calling the function to print the Need matrix
                break;
            case 7:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }while(choice!=7);
    }

    return 0;
}
