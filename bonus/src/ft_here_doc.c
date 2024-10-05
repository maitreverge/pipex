/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:08:15 by flverge           #+#    #+#             */
/*   Updated: 2024/10/05 15:26:20 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	failed_io(char *buffer, int fd_here_doc, char *message)
{
	free(buffer);
	close(fd_here_doc);
	exit_and_message(message, 1);
}

void read_here_doc(char *eof, int *fd)
{
	(void)(fd);
	int bytes_read;
	char *buffer;
	int fd_here_doc;

	eof = ft_strjoin(eof, "\n\0"); // TODO : to free

	buffer = malloc(sizeof(char) * 1024); // TODO : to free

	// bytes_read == NULL;

	// open and erase it with O_TRUNC if it does exists
	fd_here_doc = open(HERE_DOC_NAME, O_RDWR | O_CREAT | O_TRUNC, 0664); // TODO : delete the file
	
	while(true)
	{
		bytes_read = read(STDIN_FILENO, buffer, 1024 -1); // exclude last for '\0'
		if (bytes_read == -1)
			failed_io(buffer, fd_here_doc, "Error reading from STDIN");
		
		buffer[bytes_read] = '\0'; // append terminating char
		
		if (!ft_strcmp(buffer, eof)) // match from the EOF
			break;
		
		if (write(fd_here_doc, buffer, bytes_read) == -1)
			failed_io(buffer, fd_here_doc, "Error writing to here_doc file");
	}
}

void	ft_here_doc(char **av, char **envp, t_paths **paths)
{
	(void)(envp);
	(void)(paths);
    int fd[2];
    int fork_pid;
    
    if (pipe(fd) == -1)
        exit_and_message("Pipe failed", 1);
    fork_pid = fork();
    
    if (fork_pid == 0) // child
	{
		read_here_doc(av[1], fd); // file created
		// child_process(av, envp, paths, fd);
	}
    waitpid(fork_pid, 0, 0);
	printf("File created");
    // parent_process_here_doc(av, paths, fd, envp);
}
