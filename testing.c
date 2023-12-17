#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "libft/libft/libft.h"
#include "libft/ft_printf/ft_printf.h"
#include "libft/get_next_line/get_next_line_bonus.h"

char	*ft_strncpy(char *dest, char const *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

void	arg_sub_check(char const *s, char c, size_t *i, size_t *start)
{
	char quote = 39;
	int inside_quotes = 0;

	while (s[*i] == c)
		(*i)++;
	*start = *i;
	while (s[*i] && (inside_quotes || s[*i] != c))
	{
		if (s[*i] == quote)
			inside_quotes = !inside_quotes;
		(*i)++;
	}
}

void	arg_allocation(char **buffer, char const *s, char c, size_t len_s)
{
	size_t	i;
	size_t	j;
	size_t	start;
	size_t	len;
	int		inside_quotes;

	i = 0;
	j = 0;
	start = 0;
	inside_quotes = 0;
	if (!s)
		return ;
	while (s[i])
	{
		arg_sub_check(s, c, &i, &start);
		if (j < len_s)
		{
			len = i - start;
			if (s[start] == 39) // if the word starts with a quote
			{
				start++; // skip the first quote
				len--; // decrease the length to skip the quote
				inside_quotes = 1;
			}
			if (inside_quotes && s[i - 1] == 39) // if the word ends with a quote
			{
				len--; // decrease the length to skip the quote
				inside_quotes = 0;
			}
			buffer[j] = ft_calloc(sizeof(char), (len + 1));
			if (!buffer[j])
				return ;
			ft_strncpy(buffer[j], &s[start], len);
			j++;
		}
		i++;
	}
}

size_t	ft_arg_countwords(char const *str, char space)
{
	size_t	result;
	int		i;
	char	quote;

	result = 0;
	quote = 39;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] == space && str[i])
			i++;
		if (str[i] == quote)
		{
			i++;
			while (str[i] != quote && str[i])
				i++;
			if (str[i] == quote)
			{
				result++;
				i++;
			}
			else
				exit (-1);
		}
		else if (str[i] != space && str[i])
		{
			while (str[i])
			{
				if (str[i] == space)
					break;
				else if (str[i] == quote)
				{
					i++;
					while (str[i] != quote && str[i])
						i++;
					i++;
					break;
				}
				i++;
			}
			result++;
		}
	}
	return (result);
}

char	**ft_arg_split(char const *s, char space)
{
	char	**buffer;
	size_t	len_s;

	len_s = ft_arg_countwords(s, space);
	buffer = (char **)ft_calloc(sizeof(char *), (len_s + 1));
	if (!buffer)
		return (NULL);
	arg_allocation(buffer, s, space, len_s);
	return (buffer);
}

int main(int ac, char **av)
{
	char **result;
	char space = 32;

	int nb_args = ft_arg_countwords(av[1], space);

	printf("Nb of args = %i\n\n", nb_args);

	result = ft_arg_split(av[1], space);

	for (int i = 0; i <= nb_args; i++)
		printf("Token %i = %s\n", i + 1, result[i]);

}


/*
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


