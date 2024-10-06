/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:08:28 by flverge           #+#    #+#             */
/*   Updated: 2024/10/06 10:56:49 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	child_process_mp(char **av, char **envp, t_paths **paths, int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	// dup2(fd[0], STDIN_FILENO);
	ft_exec(av[0], envp, paths);
}

static void	parent_process_mp(char **av, char**envp, t_paths **paths, int *fd)
{
	perror("Hello parent process");
	perror("Current av[0] ==");
	perror(av[0]);
	char	*output_file;
	int		fd_file;

	output_file = av[1]; //  ! LAST ARGUMENT
	fd_file = open(output_file, O_RDWR | O_CREAT, 0664);
	if (fd_file == -1)
	{
		free_paths(*paths);
		exit_and_message("Output file can't be openned\nAborting pipex", 1);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[1]);
	dup2(fd_file, STDOUT_FILENO);
	ft_exec(av[0], envp, paths); // ! FIRST ARGUMENT AFTER LOOPING
}

// 			av[0]
// ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
void	ft_multi_pipes(char **av, int ac, char **envp, t_paths **paths)
{
	int	fd[2];
	int	fork_pid;
	char	*input_file;
	int		fd_file;
	int i = 0;

	input_file = av[0];
	
	/////////////////////
	fd_file = open(input_file, O_RDONLY);
	if (fd_file == -1)
	{
		free_paths(*paths);
		exit_and_message("Input file can't be openned\nAborting pipex", 1);
	}


	// dup2(fd[1], STDOUT_FILENO);

	/////////////////////
		
	if (pipe(fd) == -1)
		exit_and_message("Pipe Failed", 1);
	fork_pid = fork();
	if (fork_pid == -1)
		exit_and_message("Fork failed", 1);
		
	dup2(fd_file, STDIN_FILENO);
	if (fork_pid == 0)
	{
		while ( i++ < ac - 4 ){
			av++;
			child_process_mp(av, envp, paths, fd);
		}
	}
	waitpid(fork_pid, 0, 0);
	av += 3;
	parent_process_mp(av, envp, paths, fd);
}
