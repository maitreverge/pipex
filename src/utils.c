/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 10:31:16 by flverge           #+#    #+#             */
/*   Updated: 2023/12/24 22:34:34 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (-1);
	while ((s1[i] || s2[i]) && (s1[i] == s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	error_quit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
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

