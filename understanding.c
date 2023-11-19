/*

Authorized functions :

! open : open a file descriptor with a read / write function

! close : close the fd

! read : read(fd, original_buffer, BUFFER_SIZE);

! Write : => ft_putchar maggle

! Malloc : tu coco

! Free : pareil

! perror: void perror(const char *str);  


The perror function in C is used to print a description for the last error that occurred during a system call or library function. It's particularly helpful when you want to provide more informative error messages than just the error code. Here's a brief explanation:

Function: void perror(const char *s);

Description: Prints a description for the last error that occurred during a system call or library function.

Parameters:

s: A pointer to a string that will be printed before the error message. It's typically used to provide additional context to the error.



! strerror :

strerror is another function in C that serves a similar purpose to perror.
It's used to retrieve a pointer to the textual representation of the current errno value (error number).

Here's a breakdown:
Function: char *strerror(int errnum);

Description: Returns a pointer to the textual representation of the current errno value (errnum).

Parameters:

errnum: The error number for which you want the error message.

EXAMPLE :

*/

#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {
    FILE *file = fopen("nonexistent_file.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        // Or you can use perror directly: perror("Error opening file");
        // perror adds the error message automatically, while strerror requires explicit format
        // specifier in the printf function.
        
        exit(EXIT_FAILURE);
    }

    // Rest of the code...

    return 0;
}

/*


! access :

The access function in C is used to check the accessibility of a file or a path based on the permissions specified.
It can be used to check whether a file can be read, written, or executed by the current process. Here's an overview:

Function: int access(const char *path, int mode);

Description: Checks whether the calling process can access the file specified by the path.

Parameters:

path: The path to the file or directory you want to check.
mode: The mode of access you want to check (read, write, execute, or a combination).
Return Value:

Returns 0 if the access is granted according to the specified mode.
Returns -1 if an error occurs, and errno is set to indicate the specific error.

Examples :

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main() {
    const char *file_path = "example.txt";

    // Check if the file is readable
    if (access(file_path, R_OK) == 0) {
        printf("File is readable.\n");
    } else {
        perror("Error checking file accessibility");
        exit(EXIT_FAILURE);
    }

    // Check if the file is writable
    if (access(file_path, W_OK) == 0) {
        printf("File is writable.\n");
    } else {
        perror("Error checking file accessibility");
        exit(EXIT_FAILURE);
    }

    // Check if the file is executable
    if (access(file_path, X_OK) == 0) {
        printf("File is executable.\n");
    } else {
        perror("Error checking file accessibility");
        exit(EXIT_FAILURE);
    }

    return 0;
}

/*

dup :

dup2 :

execve :

exit :

fork :

pipe :

unlink :

wait : 

waitpid :

*/