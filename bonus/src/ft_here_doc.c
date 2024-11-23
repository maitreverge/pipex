/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:08:15 by flverge           #+#    #+#             */
/*   Updated: 2024/10/05 17:02:59 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	failed_io(char *buffer, int fd_here_doc, char *eof, char *message)
{
	free(buffer);
	free(eof);
	close(fd_here_doc);
	exit_and_message(message, 1);
}

void	read_here_doc(char *eof)
{
	char	*buffer;
	int		bytes_read;
	int		fd_here_doc;

	eof = ft_strjoin(eof, "\n\0");
	buffer = malloc(sizeof(char) * 1024);
	fd_here_doc = open(HERE_DOC_NAME, O_RDWR | O_CREAT | O_TRUNC, 0664);
	while (true)
	{
		write(STDOUT_FILENO, "here_doc$ ", 10); // Print the prompt
		bytes_read = read(STDIN_FILENO, buffer, 1024 -1);
		if (bytes_read == -1)
			failed_io(buffer, fd_here_doc, eof, "Error reading STDIN");
		buffer[bytes_read] = '\0';
		if (!ft_strcmp(buffer, eof))
			break ;
		if (write(fd_here_doc, buffer, bytes_read) == -1)
			failed_io(buffer, fd_here_doc, eof, "Can't write to here_doc file");
	}
	free(eof);
	free(buffer);
	close(fd_here_doc);
}

static void	child_process_hd(char **av, char **envp, t_paths **paths, int *fd)
{
	int		fd_here_doc;

	fd_here_doc = open(HERE_DOC_NAME, O_RDONLY);
	if (fd_here_doc == -1)
	{
		free_paths(*paths);
		exit_and_message("Input file can't be openned\nAborting pipex", 1);
	}
	dup2(fd_here_doc, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	ft_exec(av[2], envp, paths);
	close(fd_here_doc);
}

static void	parent_process_hd(char **av, char**envp, t_paths **paths, int *fd)
{
	char	*output_file;
	int		fd_file;

	output_file = av[4];
	fd_file = open(output_file, O_RDWR | O_CREAT | O_APPEND, 0664);
	if (fd_file == -1)
	{
		free_paths(*paths);
		exit_and_message("Output file can't be openned\nAborting pipex", 1);
	}
	dup2(fd_file, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	ft_exec(av[3], envp, paths);
}

void	ft_here_doc(char **av, char **envp, t_paths **paths)
{
	int	fd[2];
	int	fork_pid;

	if (pipe(fd) == -1)
		exit_and_message("Pipe failed", 1);
	if (!access(HERE_DOC_NAME, F_OK))
		unlink(HERE_DOC_NAME);
	read_here_doc(av[1]);
	fork_pid = fork();
	if (fork_pid == -1)
		exit_and_message("Fork failed", 1);
	if (fork_pid == 0)
	{
		child_process_hd(av, envp, paths, fd);
	}
	waitpid(fork_pid, 0, 0);
	unlink(HERE_DOC_NAME);
	parent_process_hd(av, envp, paths, fd);
}
