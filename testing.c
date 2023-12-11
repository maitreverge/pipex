#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>



int main()
{
    pid_t child_pid = fork();

    if (child_pid > 0)
	{
        // Parent process
        sleep(1); // Allow child to terminate
        printf("Parent process with PID: %d and PPID %d\n", getpid(), getppid());
		wait(&child_pid);
    }
	else if (child_pid == 0)
	{
        // Child process
        printf("Child process with PID: %d\n", getpid());
        sleep(4); // simulate work
        printf("CHILD done\n");
		exit(EXIT_SUCCESS);
    }
	else
	{
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}



// int main() // implementing wait
// {
//     pid_t child_pid = fork();

//     if (child_pid > 0)
// 	{
//         // Parent process
//         sleep(1); // Allow child to terminate
//         printf("Parent process with PID: %d and PPID %d\n", getpid(), getppid());
// 		wait(&child_pid);
//     }
// 	else if (child_pid == 0)
// 	{
//         // Child process
//         printf("Child process with PID: %d\n", getpid());
//         sleep(4); // simulate work
//         printf("CHILD done\n");
// 		exit(EXIT_SUCCESS);
//     }
// 	else
// 	{
//         perror("Fork failed");
//         exit(EXIT_FAILURE);
//     }

//     return 0;
// }



/*
int main(void) // understanding waiting child/parent
{
	pid_t pid;

	pid = fork();

	if (pid == -1)
	{
		printf("Error occured\n");
		return -1;
	}
	if (pid == 0) // child process
	{
		printf("Hello, it's me the CHILD process, my pid is %d\n", pid);
		sleep(5);
		printf("Child process done\n");

	}
	else if (pid > 0) // parent process
	{
		printf("Hello, it's me the PARENT process, my child's pid is %d\n", pid);
		// sleep(2);
		printf("parent process done\n");

	}
}




int main(void) // understanding child and parent process
{
	pid_t pid;
	int nb = 42;

	printf("Forking here\n");
	pid = fork();
	
	if (pid == -1)
	{
		printf("Error occured\n");
		return -1;
	}
	printf("Forking worked\n");
	if (pid == 0)
	{
		printf("This is the child process\n");
		nb++;
		printf("Number = %d\n", nb);
	}
	else if (pid >= 0)
	{
		printf("This is the parent process\n");
		nb++;
		printf("Number = %d\n", nb);
	}
}
*/


