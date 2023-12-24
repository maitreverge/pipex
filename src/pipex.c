/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:12:36 by flverge           #+#    #+#             */
/*   Updated: 2023/12/24 23:15:07 by flverge          ###   ########.fr       */
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

void	pipex_mandatory(char **av, t_vars *vars)
{
	int		return_execve;
	// char	*joined_path;
	// int		i;

	if (pipe(vars->pipe_fd) == -1)
		error_quit("Piping failure");
	vars->pid = fork();
	if (vars->pid == -1)
		error_quit("Forking failure");
	else if (vars->pid == 0)
		child_process(vars);
	else // parent process, aka cmd 2
	{
		waitpid(vars->pid, &vars->status, 0);
		// ! ADD PROTECTION FOR DUP2
		dup2(vars->pipe_fd[0], STDIN_FILENO); // stdin cmd2 == stdout of pipe
		close(vars->pipe_fd[0]);
		close(vars->pipe_fd[1]);
		dup2(vars->fd[1], STDOUT_FILENO); // stdout cmd2 == outfile
		close(vars->fd[1]);

		i = 0;
		while(vars->parsing.path[i] != NULL)
		{
			joined_path = ft_strjoin(vars->parsing.path[i], *vars->parsing.args[1]);
			// printf("Joined path = %s\n", joined_path);
			if (access(joined_path, F_OK) == 0) // access == 0 == success
			{
				if (execve(joined_path, vars->parsing.args[1], 0) == -1)
				{
					free_vars(vars);
					free(joined_path);
					joined_path = NULL;
					// break;
					 error_quit("execve failed");
					// vars->parsing.path++;
				}
				else // if exexve executed proprely
				{
					free(joined_path);
					joined_path = NULL;
					// exit(EXIT_SUCCESS);			
				}
			}
			else // if correct path hasn't been found
			{
				free(joined_path);
				i++;
			}
		}
		
		free_vars(vars);
		error_quit("Command not found");
	}		
}

int	main(int ac, char **av, char **envp)
{
	t_vars	vars;

	if (ac >= 5)
	{
		vars = init_struct(ac, av, envp, &vars);
		check_args_mandatory(av, vars.fd, &vars);
		pipex_mandatory(av, &vars);
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
