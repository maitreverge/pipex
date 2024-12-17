#include "pipex_bonus.h"

static void	child_process_mp(char **av, char **envp, t_paths **paths, int *fd, int is_last)
{
    if (!is_last)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
    }
    // Execute the command
    ft_exec(av[0], envp, paths);
}

void	ft_multi_pipes(char **av, int ac, char **envp, t_paths **paths)
{
    int	fd[2];
    int	fork_pid;
    char	*input_file;
    int		fd_file_in;
    int		fd_file_out;
    int		i = 1; // Start from 1 since av[0] is the first file

    // Open input file
    input_file = av[0];
	printf("%s\n", input_file);
    fd_file_in = open(input_file, O_RDONLY);
    if (fd_file_in == -1)
    {
        free_paths(*paths);
        exit_and_message("Input file can't be opened\nAborting pipex", 1);
    }

    // Open output file
    char	*output_file;
    output_file = av[ac - 2]; // right file OKAY
	printf("%s\n", output_file);
    fd_file_out = open(output_file, O_RDWR | O_CREAT | O_TRUNC, 0664);
    if (fd_file_out == -1)
    {
        free_paths(*paths);
        exit_and_message("Output file can't be opened\nAborting pipex", 1);
    }

    // Redirect stdin to input file
    dup2(fd_file_in, STDIN_FILENO);
    close(fd_file_in);

    while (i < ac - 3)
    {
        if (pipe(fd) == -1)
            exit_and_message("Pipe Failed", 1);
        fork_pid = fork();
        if (fork_pid == -1)
            exit_and_message("Fork failed", 1);
        if (fork_pid == 0)
        {
            // Child process
            child_process_mp(av + i, envp, paths, fd, i == ac - 3);
        }
        else
        {
            // Parent process
            close(fd[1]); // Close the write end of the pipe in the parent
            dup2(fd[0], STDIN_FILENO); // Redirect stdin to the read end of the pipe for the next command
            close(fd[0]); // Close the read end of the pipe after duplicating
            waitpid(fork_pid, NULL, 0);
        }
        i++;
    }

    // Redirect stdout to output file

    dup2(fd_file_out, STDOUT_FILENO);
    close(fd_file_out);
    // Execute the last command
    ft_exec(av[ac - 3], envp, paths);
}