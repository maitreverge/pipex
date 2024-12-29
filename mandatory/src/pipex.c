/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:23:55 by flverge           #+#    #+#             */
/*   Updated: 2024/12/29 21:29:09 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	voluntary_failing(char *join_buff, char **splitted_command, char **envp)
{
	execve(join_buff, splitted_command, envp);
	perror("execve");
	free(join_buff);
}

static void	ft_exec(char *command, char **envp, t_paths **paths)
{
	t_paths	*temp_paths;
	char	**splitted_command;
	char	*join_buff;

	temp_paths = *paths;
	join_buff = 0;
	splitted_command = ft_split(command, ' ');
	while (temp_paths->next != 0)
	{
		if (join_buff)
			free(join_buff);
		join_buff = ft_strjoin(temp_paths->path, splitted_command[0]);
		if (access(join_buff, F_OK) == 0)
		{
			if (execve(join_buff, splitted_command, envp) == -1)
				perror("execve");
			free(join_buff);
			break ;
		}
		temp_paths = temp_paths->next;
	}
	if (!temp_paths->next && join_buff)
		voluntary_failing(join_buff, splitted_command, envp);
	free_split(splitted_command);
}

static void	child_process(char **av, char **envp, t_paths **paths, int *fd)
{
	char	*input_file;
	int		fd_file;

	input_file = av[0];
	fd_file = open(input_file, O_RDONLY);
	if (fd_file == -1)
	{
		free_paths(*paths);
		exit_and_message("Input file can't be openned\nAborting pipex", 1);
	}
	dup2(fd_file, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	ft_exec(av[1], envp, paths);
}

static void	parent_process(char **av, char**envp, t_paths **paths, int *fd)
{
	char	*output_file;
	int		fd_file;

	output_file = av[3];
	fd_file = open(output_file, O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (fd_file == -1)
	{
		free_paths(*paths);
		exit_and_message("Output file can't be openned\nAborting pipex", 1);
	}
	dup2(fd_file, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	ft_exec(av[2], envp, paths);
}

void	pipex(char **av, char **envp, t_paths **paths)
{
	int	fd[2];
	int	fork_pid;

	if (pipe(fd) == -1)
		exit_and_message("Pipe Failed", 1);
	fork_pid = fork();
	if (fork_pid == -1)
		exit_and_message("Fork failed", 1);
	if (fork_pid == 0)
		child_process(av, envp, paths, fd);
	waitpid(fork_pid, 0, 0);
	parent_process(av, envp, paths, fd);
}
