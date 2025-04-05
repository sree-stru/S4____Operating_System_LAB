ANUSREE KJ
S4DS - ROLL NO:13
                           EXPERIMENT : SYSTEM CALLS
    
#include <stdio.h>       // printf(), scanf(), perror()
#include <unistd.h>      // fork(), getpid(), getppid(), execl()
#include <sys/types.h>   // pid_t
#include <sys/wait.h>    // wait()
#include <sys/stat.h>    // stat(), struct stat
#include <dirent.h>      // opendir(), readdir(), closedir(), struct dirent
#include <stdlib.h>      // exit()
#include <string.h>      // strlen()

void create_process();
void file_status_info();
void list_files_and_dirs();

int main() 
{
    int choice;

    do 
    {
        printf("\n==== MENU ====\n");
        printf("1. Create a new process\n");
        printf("2. Get file status info using stat()\n");
        printf("3. List files and directories (using readdir)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_process();
                break;
            case 2:
                file_status_info();
                break;
            case 3:
                list_files_and_dirs();
                break;
            case 4:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }

    } while (choice != 4);

    return 0;
}

void create_process() 
{
    pid_t pid = fork();

    if (pid == 0) 
    {
        // Child process
        printf("\n[Child] PID: %d | PPID: %d\n", getpid(), getppid());
        printf("[Child] Executing 'ls -l':\n");
        execl("/bin/ls", "ls", "-l", (char *)NULL);
        perror("execl failed");
        exit(1);
    } else if (pid > 0) 
    {
        // Parent process
        wait(NULL);  // Wait for child to finish
        printf("\n[Parent] PID: %d | Child PID: %d\n", getpid(), pid);
        printf("[Parent] Child process has finished.\n");
    } else 
    {
        perror("fork failed");
    }
}

void file_status_info() 
{
    char filename[100];
    struct stat fileStat;

    printf("Enter the filename or path: ");
    scanf("%s", filename);

    if (stat(filename, &fileStat) == -1) 
    {
        perror("stat failed");
        return;
    }

    printf("\n--- File Status Info ---\n");
    printf("Device ID: %ld\n", fileStat.st_dev);
    printf("Inode Number: %ld\n", fileStat.st_ino);
    printf("Size: %ld bytes\n", fileStat.st_size);
    printf("Blocks Allocated: %ld\n", fileStat.st_blocks);
    printf("Last Access Time: %ld\n", fileStat.st_atime);
    printf("Last Modification Time: %ld\n", fileStat.st_mtime);
    printf("Last Status Change Time: %ld\n", fileStat.st_ctime);
}

void list_files_and_dirs() 
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (dir == NULL) 
    {
        perror("opendir failed");
        return;
    }

    printf("\n--- Files and Directories in Current Directory ---\n");
    while ((entry = readdir(dir)) != NULL) 
    {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}
