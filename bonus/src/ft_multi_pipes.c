/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TryHardTeam <TryHardTeam@123.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:08:28 by flverge           #+#    #+#             */
/*   Updated: 2024/12/17 14:43:00 by TryHardTeam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	child_process_mp(char **av, char **envp, t_paths **paths, int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	// ft_exec(av[0], envp, paths);
}

void	ft_multi_pipes(char **av, int ac, char **envp, t_paths **paths)
{
    int	fd[2];
    int	fork_pid;
    char	*input_file;
    int		fd_file_in;
    int		fd_file_out;
    int		i = 0;

	// Open in file
    input_file = av[0];
    fd_file_in = open(input_file, O_RDONLY);
    if (fd_file_in == -1)
    {
        free_paths(*paths);
        exit_and_message("Input file can't be opened\nAborting pipex", 1);
    }
	 // open outfile
	char	*output_file;
	int		fd_file;

	output_file = av[1]; //  ! LAST ARGUMENT
	fd_file = open(output_file, O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (fd_file == -1)
	{
	    free_paths(*paths);
	    exit_and_message("Output file can't be opened\nAborting pipex", 1);
	}
    dup2(fd_file_in, STDIN_FILENO);
    // close(fd_file);

    while (i++ < ac - 4)
    {
        av++;
        if (pipe(fd) == -1)
            exit_and_message("Pipe Failed", 1);
        fork_pid = fork();
        if (fork_pid == -1)
            exit_and_message("Fork failed", 1);
        if (fork_pid == 0)
        {
            child_process_mp(av, envp, paths, fd);
        }
        else
        {
            close(fd[1]); // Close the write end of the pipe in the parent
            dup2(fd[0], STDIN_FILENO); // Redirect stdin to the read end of the pipe for the next command
            waitpid(fork_pid, 0, 0);
            // close(fd[0]); // Close the read end of the pipe after duplicating
        }
    }
	dup2(fd_file_out, STDOUT_FILENO);
	ft_exec(av[ac - 2], envp, paths);

    // parent_process_mp(++av, envp, paths, fd);
}