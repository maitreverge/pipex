/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:00:02 by flverge           #+#    #+#             */
/*   Updated: 2023/12/17 12:09:50 by flverge          ###   ########.fr       */
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
	buffer = (char ***)malloc(sizeof(char **) * (ac - 3) + 1);
	if (!buffer)
		error_quit("Malloc failed");
	while ((i + j) <= (ac - 2))
	{
		buffer[j] = malloc(sizeof(char *) * (ft_arg_ctw(av[i + j], 32)) + 1);
		if (!buffer[j])
			error_quit("Malloc failed");
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
	result = ft_split(path, ':');
	if (!result)
		error_quit("Split function failed");
	free(path);
	return (result);
}
