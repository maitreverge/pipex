/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:00:02 by flverge           #+#    #+#             */
/*   Updated: 2023/12/24 21:38:19 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	***args_parsing(int ac, char **av)
{
	char	***buffer;
	int		i;
	int		j;
	char	space;

	i = 2;
	j = 0;
	space = 32;
	buffer = (char ***)malloc(sizeof(char **) * (ac - 3 + 1));
	if (!buffer)
		error_quit("Malloc failed");
	while ((i + j) <= (ac - 2))
	{
		buffer[j] = ft_arg_split(av[i + j], space);
		j++;
	}
	buffer[j] = NULL;
	return (buffer);
}

char	**path_parsing(char **av, char **envp)
{
	char	**env;
	char	**result;
	char	*path;

	env = envp;
	while (*env != NULL)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			break ;
		env++;
	}
	if (*env)
	{
		path = ft_strtrim(*env, "PATH=");
		if (!path)
			error_quit("Strtrim function failed");
	}
	else
		error_quit("PATH envp couldn't be found");
	result = ft_pipex_split(path, ':');
	if (!result)
		error_quit("Split function failed");

	free(path);
	return (result);
}

void	check_args_mandatory(char **av, int *fd, t_vars *vars)
{
	fd[0] = open(av[1], O_RDONLY);
	if (fd[0] == -1)
	{
		free_vars(vars);
		error_quit("Opening infile failed");
	}
	if (access(av[4], F_OK) == 0)
	{
		if (access(av[4], W_OK) == -1)
		{
			free_vars(vars);
			error_quit("Outfile is not writable");
		}
		else
			fd[1] = open(av[4], O_WRONLY | O_TRUNC);
	}
	else
		fd[1] = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[1] == -1)
	{
		free_vars(vars);
		error_quit("Opening outfile failed");
	}
}
