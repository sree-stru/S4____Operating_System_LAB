#include<stdio.h>
#include <fcntl.h>      // for open() and file flags like O_WRONLY, O_CREAT, etc.
#include <unistd.h>     // for read(), write(), close()
#include <string.h>     // for strlen()

#define FILE_NAME "text.txt"
#define BUFFER_SIZE 1024

int main()
{
    char user_input[BUFFER_SIZE];
    
    printf("Enter text to write to the file :\n");

    if(fgets(user_input,sizeof(user_input),stdin) == NULL)
    {
        perror("Error reading input \n");
        return 1;
    }
    
    int fd = fopen( FILE_NAME , O_WRONLY | O_CREAT | O_TRUNC , S_TRUSR | S_TWUSR ))
    if(fd==-1)
    { 
        perror("Error in opening the file for writing \n");
        return 1;
    }
    ssize_t bytes_written = write(fd ,user_input ,strlen(user_input));
    if(bytes_written == -1)
    {
       perror("Error writing to a file");
       close(fd);
       return 1;
    }
    printf("Successfully %ld written into the file. ",bytes_written);

    if(fclose(fd)== -1)
    {
       perror("Error in closing file\n");
       return 1;
    }

    fd = fopen(FILE_NAME ,O_RDONLY)
    {
        if(fd = -1)
        {
            perror("Error in opening file \n");
            return 1;
        }
    }
    
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = read(fd, buffer , sizeof(buffer)-1);
    if(bytes_read == -1)
    {
          perror("Error reading from the file");
          close(fd);
          return 1;
    }
       
    buffer[bytes_read] = '\0';    // Null-terminate the buffer to make it a valid C-string
    printf("\nSuccessfully read.\n");

    if(fclose(fd)== -1)
    {
       perror("Error in closing the file after reading\n");
       return 1;
    }

    return 0;
}
