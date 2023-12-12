#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>



// parent process always comes first
void	writestr(int fd, const char *str)
{
	write(fd, str, strlen(str));
}

int main(void)
{
	int fd[2]; // pipe fds

	pid_t pid; // fork return value
	char buf; // stock char value by value

	// creating a pipe
	if (pipe(fd) == -1)
	{
		perror("Piping failure");
		exit(EXIT_FAILURE);
	}

	// ! creating child process
	pid = fork();
	if (pid == -1)
	{
		perror("Fork failure");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) // child process
	{
		close(fd[1]); // closing the write end
		writestr(STDOUT_FILENO, "Child : What is the secret in this pipe ?\n");
		writestr(STDOUT_FILENO, "Child : \"");

		// read from the pipe one char by one
		while (read(fd[0], &buf, 1) > 0)
			write(STDOUT_FILENO, &buf, 1);
		
		writestr(STDOUT_FILENO, "\"\n");
		writestr(STDOUT_FILENO, "Child : wow ! I must go see my father.\n");

		close(fd[0]); // closing read end
		exit(EXIT_SUCCESS);
	}
	else // parent process
	{
		close(fd[0]);
		writestr(STDOUT_FILENO, "Parent : I'm writting a secret in this pipe...\n");

		// write into the pipe
		writestr(fd[1], "\e[33mI am your father mwahahaha!\e[0m");

		// closing writting end
		close(fd[1]);

		// wait for child
		wait(NULL);
		writestr(STDOUT_FILENO, "Parent, Hello child!\n");
		exit(EXIT_SUCCESS);
	}
}

/*
int main(void) // understanding dup and dup2
{
	int fd;
	int fd_copy;
	int nb_read;
	char buf[15];

printf("MY PID is %d\n", getpid());

// open the file and get his file descriptor in fd variable
fd = open("alpha.txt", O_RDONLY);
if (fd == -1)
	return 1;

fd_copy = dup(fd);
// Duplicate the original fd
if (!fd_copy)
	return 1;

// Read the original fd
nb_read = read(fd, buf, 10);
if (nb_read == -1)
	return 1;
buf[nb_read] = '\0';
printf("fd %d contains : %s\n", fd, buf);

// read duplicate fd
nb_read = read(fd_copy, buf, 10);
if (nb_read == -1)
	return 0;
buf[nb_read] = '\0';
printf("fd %d contains : %s\n", fd_copy, buf);

// Duplicate fd on standard input
dup2(fd, STDIN_FILENO);

// Infinite loop to go check open fds in this process with ls -la /proc/PID/fd

while (1)
	;




}

int main()
{
    pid_t child_pid = fork();
	int status;

    if (child_pid > 0)
	{
        // Parent process
        sleep(1); // Allow child to terminate
        printf("Parent process with PID: %d and PPID %d\n", getpid(), getppid());
		wait(&status);
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



int main() // implementing wait
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


