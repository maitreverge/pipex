/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:12:36 by flverge           #+#    #+#             */
/*   Updated: 2023/12/24 23:19:38 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_execve(t_vars *vars, int arg, int i)
{
	char	*join;

	while (vars->parsing.path[i] != NULL)
	{
		join = ft_strjoin(vars->parsing.path[i], *vars->parsing.args[arg]);
		if (!access(join, F_OK) && EX(join, vars->parsing.args[arg], 0) == -1)
		{
			free_vars(vars);
			free(join);
			error_quit("Execve failed");
		}
		// free(join);
		if (access(join, F_OK) != 0)
		{
			free(join);
			i++;
		}
	}
	free_vars(vars);
	error_quit("Command not found");
}

void	child_process(t_vars *vars)
{
	dup2(vars->fd[0], STDIN_FILENO);
	dup2(vars->pipe_fd[1], STDOUT_FILENO);
	close(vars->fd[0]);
	close(vars->pipe_fd[0]);
	ft_execve(vars, 0, 0);
}

void	parent_process(t_vars *vars)
{
	waitpid(vars->pid, &vars->status, 0);
	dup2(vars->pipe_fd[0], STDIN_FILENO);
	close(vars->pipe_fd[0]);
	close(vars->pipe_fd[1]);
	dup2(vars->fd[1], STDOUT_FILENO);
	close(vars->fd[1]);
	ft_execve(vars, 1, 0);
}

void	pipex(char **av, t_vars *vars)
{
	if (pipe(vars->pipe_fd) == -1)
		error_quit("Piping failure");
	vars->pid = fork();
	if (vars->pid == -1)
		error_quit("Forking failure");
	else if (vars->pid == 0)
		child_process(vars);
	else
		parent_process(vars);
}

int	main(int ac, char **av, char **envp)
{
	t_vars	vars;

	if (ac >= 5)
	{
		vars = init_struct(ac, av, envp, &vars);
		check_args_mandatory(av, vars.fd, &vars);
		pipex(av, &vars);
		free_vars(&vars);
	}
	else
		error_quit("Not enough arguments");
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
