/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:12:36 by flverge           #+#    #+#             */
/*   Updated: 2023/12/24 21:38:06 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	pipex_mandatory(char **av, t_vars *vars)
{
	int return_execve;
	char *joined_path;
	int i;

	
	// ! 1 - parsing 
	if (pipe(vars->pipe_fd) == -1) // 0 = ok, -1 = error
		error_quit("Piping failure");
	
	// ! 2 - fork
	vars->pid = fork();
	if (vars->pid == -1)
		error_quit("Forking failure");
	
	// ! 3 - piping
	else if (!vars->pid) // child process, aka cmd 1
	{
		// ! ADD PROTECTION FOR DUP2
		dup2(vars->fd[0], STDIN_FILENO); // stdin == infile
		dup2(vars->pipe_fd[1], STDOUT_FILENO); // stdout of cmd 1 == stdin of pipe
		close(vars->fd[0]);
		close(vars->pipe_fd[0]);
		
		i = 0;
		while(vars->parsing.path[i] != NULL)
		{
			joined_path = ft_strjoin(vars->parsing.path[i], *vars->parsing.args[0]);
			// printf("Joined path = %s\n", joined_path);
			if (access(joined_path, F_OK) == 0) // access == 0 == success
			{
				if (execve(joined_path, vars->parsing.args[0], 0) == -1)
				{
					free_vars(vars);
					free(joined_path);
					joined_path = NULL;
					// break;
					error_quit("Execve failed");
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

t_vars	init_struct(int ac, char **av, char **envp, t_vars *vars)
{
	t_vars	init;

	init.fd[0] = 0;
	init.fd[1] = 0;
	init.pipe_fd[0] = 0;
	init.pipe_fd[1] = 0;
	init.pid = 0;
	init.status = 0;
	init.parsing.path = path_parsing(av, envp);
	init.parsing.args = args_parsing(ac, av);
	return (init);
}

void	free_vars(t_vars *vars)
{
	int	i;
	int	k;

	i = 0;
	while (vars->parsing.path[i] != NULL)
	{
		free(vars->parsing.path[i]);
		i++;
	}
	free(vars->parsing.path);
	i = 0;
	k = 0;
	while (vars->parsing.args[i] != NULL)
	{
		k = 0;
		while (vars->parsing.args[i][k] != NULL)
		{
			free(vars->parsing.args[i][k]);
			k++;
		}
		free(vars->parsing.args[i]);
		i++;
	}
	free(vars->parsing.args);
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
