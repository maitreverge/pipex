/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:12:36 by flverge           #+#    #+#             */
/*   Updated: 2023/12/14 09:42:04 by flverge          ###   ########.fr       */
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

void	pipex_mandatory(char **av, t_vars *vars)
{
	// ! 1 - parsing
	check_args_mandatory(av, vars->fd);
	if (pipe(vars->pipe_fd) == -1) // 0 = ok, -1 = error
	{
		perror("Piping failure");
		exit(EXIT_FAILURE);
	}
	
	// ! 2 - fork
	vars->pid = fork();
	if (vars->pid == -1)
	{
		perror("Forking failure");
		exit(EXIT_FAILURE);
	}
	
	// ! 3 - piping
	else if (vars->pid == 0) // child process, aka cmd 1
	{
		// ! ADD PROTECTION FOR DUP2
		dup2(vars->fd[0], STDIN_FILENO); // stdin == infile
		dup2(vars->pipe_fd[1], STDOUT_FILENO); // stdout of cmd 1 == stdin of pipe
		close(vars->pipe_fd[0]);
		close(vars->fd[0]);
		char *args1[] = {"grep", "img", NULL};
		execve("/bin/grep", args1, 0);
		exit(EXIT_SUCCESS);
	}
	else // parent process, aka cmd 2
	{
		waitpid(-1, &status, 0);
		// ! ADD PROTECTION FOR DUP2
		dup2(vars->pipe_fd[0], vars->fd[0]); // stdin cmd2 == stdout of pipe
		dup2(vars->fd[1], vars->pipe_fd[1]); // stdout cmd2 == outfile
		close(vars->pipe_fd[1]);
		close(vars->fd[1]);
		// ? close
		char *args[] = {"ls", "-l", "-s", NULL};
		execve("/bin/ls", args, 0);
		exit(EXIT_SUCCESS);
	}		
}

t_vars	init_struct(t_vars *vars)
{
	fd[0] = 0;
	fd[1] = 0;
	pipe_fd[0] = 0;
	pipe_fd[1] = 0;
	pid = 0;
	status = 0;
}

int	main(int ac, char **av, char **envp)
{
	char **path;
	char **args;
	t_vars vars;
	if (ac >= 5)
	{
		vars = init_struct(&vars);	
		pipex_mandatory(av, &vars);
		
	}
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
