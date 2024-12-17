/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TryHardTeam <TryHardTeam@123.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:13:26 by TryHardTeam       #+#    #+#             */
/*   Updated: 2024/12/17 16:14:54 by TryHardTeam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	child_process_mp(int *fd, int is_last)
{
	if (!is_last)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}

static void	closing_fds(int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

static void	loop_children(int ac, char **av, char **envp, t_paths **paths)
{
	int	fd[2];
	int	i;
	int	fork_pid;

	i = 1;
	while (i < ac - 3)
	{
		if (pipe(fd) == -1)
			exit_and_message("Pipe Failed", 1);
		fork_pid = fork();
		if (fork_pid == -1)
			exit_and_message("Fork failed", 1);
		if (fork_pid == 0)
		{
			child_process_mp(fd, i == ac - 3);
			av += i;
			ft_exec(av[0], envp, paths);
		}
		else
		{
			closing_fds(fd);
			waitpid(fork_pid, NULL, 0);
		}
		i++;
	}
}

void	ft_multi_pipes(char **av, int ac, char **envp, t_paths **paths)
{
	int		fd_file_in;
	int		fd_file_out;

	fd_file_in = open(av[0], O_RDONLY);
	fd_file_out = open(av[ac - 2], O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (fd_file_in == -1 || fd_file_out == -1)
	{
		free_paths(*paths);
		exit_and_message("Input file can't be opened\nAborting pipex", 1);
	}
	dup2(fd_file_in, STDIN_FILENO);
	close(fd_file_in);
	loop_children(ac, av, envp, paths);
	dup2(fd_file_out, STDOUT_FILENO);
	close(fd_file_out);
	ft_exec(av[ac - 3], envp, paths);
}
