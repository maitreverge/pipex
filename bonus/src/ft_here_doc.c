/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:08:15 by flverge           #+#    #+#             */
/*   Updated: 2024/10/02 12:10:10 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	custom_get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		read_buff;
	char	c;

	i = 0;
	read_buff = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	read_buff = read(0, &c, 1);
	while (read_buff && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		read_buff = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	// free(buffer);
	return (read_buff);
}

void	failed_io(char *buffer, int fd_here_doc, char *message)
{
	free(buffer);
	close(fd_here_doc);
	exit_and_message(message, 1);
}

void	read_here_doc(char **av, int* fd)
{
	int fork_1;
    char *main_buf;

	fork_1 = fork();
	if (fork_1 == 0) // child
    {
        close(fd[0]);
		while (custom_get_next_line(&main_buf))
		{
			if (ft_strncmp(main_buf, av[1], ft_strlen(av[1])) == 0)
			{
				free(main_buf);
				exit(0);
			}
			write(fd[1], main_buf, ft_strlen(main_buf));
			free(main_buf);
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
	// ft_exec(av[2], envp, paths);
}

void	parent_process_here_doc(char **av, t_paths **paths, int* fd, char **envp)
{
	char	*output_file;
    int		fd_output_file;

    output_file = av[4]; // last arg for 
    fd_output_file = open(output_file, O_RDWR | O_CREAT | O_APPEND, 0664);
    if (fd_output_file == -1)
    {
        free_paths(*paths);
        exit_and_message("Output file can't be openned\nAborting pipex", 1);
    }
    dup2(fd_output_file, STDOUT_FILENO);
    dup2(fd[0], STDIN_FILENO);
    close(fd[1]);
    close(fd_output_file);
    ft_exec(av[3], envp, paths);
}

void	child_process(char **av, char **envp, t_paths **paths)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
        exit_and_message("Pipe failed", 1);
	pid = fork();
	if (pid == -1)
        exit_and_message("Fork failed", 1);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ft_exec(av[3], envp, paths);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	ft_here_doc(char **av, char **envp, t_paths **paths)
{
    int fd[2];
    int fork_pid;
    // char* eof = av[1];
    
    if (pipe(fd) == -1)
        exit_and_message("Pipe failed", 1);
    fork_pid = fork();
    
    if (fork_pid == 0) // child
	{
		read_here_doc(av, fd);
		child_process(av,envp, paths);
	}
    waitpid(fork_pid, 0, 0);
    parent_process_here_doc(av, paths, fd, envp);
}
