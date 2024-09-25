/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:08:15 by flverge           #+#    #+#             */
/*   Updated: 2024/09/25 18:30:20 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	failed_io_here_doc(char *buffer, int fd_here_doc, char *message)
{
	perror(message);
	free(buffer);
	
}
// ./pipex here_doc LIMITER cmd cmd1 file 
// 					==
// 		cmd << LIMITER | cmd1 >> file
void	ft_here_doc(char **av, char **envp, t_paths **paths)
{
	int fd_here_doc;
	char *eof;
	char *buffer;
	ssize_t bytes_read;

	eof = av[1];
	// ! gestion erreur malloc
	buffer = malloc(sizeof(char) * 1024);

	// ! gestion erreur open
	fd_here_doc = open("here_doc", O_WRONLY | O_CREAT | O_APPEND, 0644);

	while(true)
	{
		// ! gestion erreur read
		bytes_read = read(STDIN_FILENO, buffer, 1024);
		if (bytes_read == -1)
			failed_io_here_doc(buffer, fd_here_doc, "Error reading from STDIN");
		buffer[bytes_read] = '\0'; // append terminating char
		
		if (ft_strcmp(buffer, eof) == 0)
			break;
		
		if (write(fd_here_doc, buffer, bytes_read) == -1)
		{
			
		}
	}
	
}
