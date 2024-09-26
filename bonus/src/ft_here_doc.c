/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:08:15 by flverge           #+#    #+#             */
/*   Updated: 2024/09/26 12:27:14 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	(void)(envp);
	(void)(paths);
	int fd_here_doc;
	char *here_doc_file_name;
	char *buffer;
	ssize_t bytes_read;
	// int is_heredoc_exists;

	// eof = av[1];
	// ! gestion erreur malloc
	buffer = malloc(sizeof(char) * 1024);

	// a file random of size 10 is 35^10 possibilities
	here_doc_file_name = generate_random_string(10);
	
	fd_here_doc = open(here_doc_file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);

	// reading and writting in the file
	while(true)
	{
		bytes_read = read(STDIN_FILENO, buffer, 1024 -1); // exclude last for '\0'
		if (bytes_read == -1)
			failed_io(buffer, fd_here_doc, "Error reading from STDIN");
		
		buffer[bytes_read] = '\0'; // append terminating char
		
		if (ft_strcmp(buffer, av[1]) == 0) // match from the EOF
			break;
		
		if (write(fd_here_doc, buffer, bytes_read) == -1)
			failed_io(buffer, fd_here_doc, "Error writing to here_doc file");
	}

	lseek(fd_here_doc, 0, SEEK_SET); // Reset file pointer to the beginning
	while ((buffer = get_next_line(fd_here_doc)) != NULL)
	{
		printf("%s", buffer);
		free(buffer);
	}
	close(fd_here_doc);
	free(buffer);
}