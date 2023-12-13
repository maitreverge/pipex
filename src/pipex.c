/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:12:36 by flverge           #+#    #+#             */
/*   Updated: 2023/12/13 12:33:49 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	check_args_mandatory(char **av, int *fd)
{
	if (!(access(av[1], F_OK | R_OK))) // checks if infile exists and readable
		fd[0] = open(av[1], O_RDONLY);
	else
		access_denied();
	
	// ! check for outfile
	if (!(access(av[4], F_OK))) // checks if outfile exists
	{
		if (!(access(av[4], W_OK)))
			fd[1] = open(av[4], O_WRONLY);
		else
			access_denied();
	}
	else // needs to create outfile
		fd[1] = open(av[4], O_CREAT | O_TRUNC | O_WRONLY); // ? right syntax

	if (fd[0] < 0 || fd[1] < 0)
		access_denied();
}

void	pipex_mandatory(int ac, char **av, char **env)
{
	int fd[2]; // files descriptors for infile and outfile

	int pipe_fd[2]; // fd for pipe
	
	pid_t pid;
	int	tmp_fd; // tmp fd for switching things up
	int status; // status int for waitpid function

	tmp_fd = 42;
	
	// ! 1 - parsing
	check_args_mandatory(av, fd);
	if (pipe(pipe_fd) == -1) // 0 = ok, -1 = error
	{
		perror("Piping failure");
		exit(EXIT_FAILURE);
	}
	
	// ! 2 - fork
	pid = fork();
	if (pid == -1)
	{
		perror("Forking failure");
		exit(EXIT_FAILURE);
	}
	
	// ! 3 - piping
	else if (pid == 0) // child process, aka cmd 1
	{
		dup2(stdin, fd[0]); // stdin == infile
		dup2(stdout, pipe_fd[1]); // stdout of cmd 1 == stdin of pipe
		// close ??
		execve("/bin/cat", "-e", 0);
	}
	else // parent process, aka cmd 2
	{
		dup2(fd[0], pipe_fd[0]); // stdin cmd2 == stdout of pipe
		dup2(pipe_fd[1], fd[1]) // stdout cmd2 == outfile
		
	}		

		
		
		
}

int	main(int ac, char **av, char **envp)
{
	if (ac >= 5)
		pipex_mandatory(ac, av, envp);
	else
	{
		ft_printf("Not enough arguments.\nUsage : ./pipex  <file1>  <command_1>  <command_2>  ...  <file2>"); // needs better cases handling
		return (1);
	}
}

/*

each cmd needs a stdin (input) and returns an output (to stdout)
   
    infile                                             outfile
as stdin for cmd1                                 as stdout for cmd2            
       |                        PIPE                        ↑
       |           |---------------------------|            |
       ↓             |                       |              |
      cmd1   -->    end[1]       ↔       end[0]   -->     cmd2           
                     |                       |
            cmd1   |---------------------------|  end[0]
           output                             reads end[1]
         is written                          and sends cmd1
          to end[1]                          output to cmd2
       (end[1] becomes                      (end[0] becomes 
        cmd1 stdout)                           cmd2 stdin)

*/

/*
Reminder fd

Read from stdin => read from fd 0:
Whenever we write any character from the keyboard, it reads from stdin through fd 0 and saves to a file named /dev/tty.

Write to stdout => write to fd 1:
Whenever we see any output to the video screen, it’s from the file named /dev/tty and written to stdout in screen through fd 1.

Write to stderr => write to fd 2:
We see any error to the video screen, it is also from that file write to stderr in screen through fd 2.

*/
