/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:12:36 by flverge           #+#    #+#             */
/*   Updated: 2024/01/01 10:57:34 by flverge          ###   ########.fr       */
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
	dup2(vars->pipe_fd[1], STDOUT_FILENO);
	dup2(vars->fd[0], STDIN_FILENO);
	close(vars->pipe_fd[0]);
	ft_execve(vars, 0, 0);
}

void	parent_process(t_vars *vars)
{
	dup2(vars->pipe_fd[0], STDIN_FILENO);
	dup2(vars->fd[1], STDOUT_FILENO);
	close(vars->pipe_fd[1]);
	ft_execve(vars, 1, 0);
}

void	pipex(t_vars *vars)
{
	if (pipe(vars->pipe_fd) == -1)
		error_quit("Piping failure");
	vars->pid = fork();
	if (vars->pid == -1)
		error_quit("Forking failure");
	else if (vars->pid == 0)
		child_process(vars);
	waitpid(vars->pid, &vars->status, 0);
	parent_process(vars);
}

int	main(int ac, char **av, char **envp)
{
	t_vars	vars;

	if (ac >= 5)
	{
		vars = init_struct(ac, av, envp);
		check_args_mandatory(av, vars.fd, &vars);
		pipex(&vars);
		free_vars(&vars);
		return (0);
	}
	else
		error_quit("Not enough arguments");
}
