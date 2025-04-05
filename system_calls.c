#include <stdio.h>       // printf(), fprintf(), perror(), scanf(), sprintf()
#include <unistd.h>      // fork(), getpid(), getppid(), execl()
#include <sys/types.h>   // pid_t
#include <sys/wait.h>    // wait()
#include <sys/stat.h>    // stat(), struct stat
#include <dirent.h>      // (Not directly used in final code, but would be needed for manual directory listing)
#include <string.h>      // (Not directly used in final code, but useful for strcmp(), strcpy(), etc.)
#include <stdlib.h>      // exit(), malloc(), free()

pid_t pid = -1;       // indicate no process has been created

void process_create();
void get_processid();
void list_directories();

int main() 
{
    int choice;
    do 
    {
        printf("\nMENU\n");
        printf("1. Create process\n");
        printf("2. Get process ID and info\n");
        printf("3. List directories\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) 
        {
            case 1:
                process_create();
                break;
            case 2:
                get_processid();
                break;
            case 3:
                list_directories();
                break;
            case 4:
                printf("Exiting......\n");
                break;
            default:
                printf("Invalid choice. Try again........\n");
        }
    } while (choice != 4);
    return 0;
}

void process_create() {
    pid = fork();// Create a new process. fork() returns:
    // 0 in the child process,
    // > 0 (child's PID) in the parent process,
    // -1 if fork fails.   

    if (pid == 0) {
        printf("Child process created\n");
        printf("Child process ID: %d\nParent process ID: %d\n", getpid(), getppid());
        exit(0);
    } else if (pid > 0) {
        printf("Parent process: PID %d\nChild process: PID %d\n", getpid(), pid);
        wait(NULL);
        printf("Parent process: Child has finished executing\n");
    } else {
        fprintf(stderr, "Fork failed\n");
    }
}

void get_processid() {
    if (pid != -1) {
        struct stat fileStat;   // Structure to store information about the file
        char pid_str[20];       // Buffer to store the path string to the process directory
        sprintf(pid_str, "/proc/%d", pid);

        if (stat(pid_str, &fileStat) == -1) {
            printf("Failed to get status of the process %d\n", pid);
        } else {
            printf("Process %d status\n", pid);
            printf("Device ID: %ld\n", fileStat.st_dev);
            printf("Inode ID: %ld\n", fileStat.st_ino);
            printf("Size: %ld bytes\n", fileStat.st_size);
            printf("Last access time: %ld\n", fileStat.st_atime);
            printf("Last modification time: %ld\n", fileStat.st_mtime);
        }
    } else {
        printf("No process created yet.\n");
    }
}

void list_directories() 
{
    pid_t ls_pid = fork();
    if (ls_pid == 0) 
    {
        execl("/bin/ls", "ls", "-l", (char *)NULL);
        perror("Exec failed");
        exit(1);
    } else 
    {
        // Parent process
        wait(NULL);  // Wait for the child (ls command) to complete   
    }
}

