/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:08:15 by flverge           #+#    #+#             */
/*   Updated: 2024/09/27 08:20:34 by flverge          ###   ########.fr       */
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
	// (void)(envp);
	int fd_here_doc;
	char *here_doc_file_name;
	char *buffer;
	ssize_t bytes_read;
	int fd[2];

	if (pipe(fd) == -1)
		exit_and_message("Pipe failed", 1);
	
	
	// int is_heredoc_exists;

	char *eof = ft_strjoin(av[1], "\n\0");
	
	// ! gestion erreur malloc
	buffer = malloc(sizeof(char) * 1024);

	// a file random of size 10 is 35^10 possibilities
	here_doc_file_name = generate_random_string(10);

	int fork_pid = fork();
	
	if (fork_pid == 0)
	{

		
		fd_here_doc = open(here_doc_file_name, O_RDWR | O_CREAT, 0664);
		if (fd_here_doc == -1)
		{
			free_paths(*paths);
			exit_and_message("Input file can't be openned\nAborting pipex", 1);
		}


		// reading and writting in the file
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

		dup2(fd_here_doc, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd_here_doc);
		ft_exec(av[2], envp, paths);
		// unlink(here_doc_file_name);
		
	} // end child process

	waitpid(fork_pid, 0, 0);
	
	/*
	! ./pipex_bonus  here_doc LIMITER cmd cmd1 file
	*/
	// remove file_in
		
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
}