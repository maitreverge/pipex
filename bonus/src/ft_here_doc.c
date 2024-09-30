/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:08:15 by flverge           #+#    #+#             */
/*   Updated: 2024/09/30 18:47:59 by flverge          ###   ########.fr       */
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
// ./pipex here_doc LIMITER cmd cmd1 file 
// 					==
// 		cmd << LIMITER | cmd1 >> file
void	ft_here_doc(char **av, char **envp, t_paths **paths)
{
    int fd[2];
    char *main_buf;
    int fork_pid;
    char* eof = av[1];
    
    if (pipe(fd) == -1)
        exit_and_message("Pipe failed", 1);
    fork_pid = fork();
    
    if (fork_pid == 0) // child
    {
        // child process
        close(fd[0]);
		while (custom_get_next_line(&main_buf))
		{
			if (ft_strncmp(main_buf, eof, ft_strlen(eof)) == 0)
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
    
    waitpid(fork_pid, 0, 0);

    // Parent process
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

    // Cleanup
}
