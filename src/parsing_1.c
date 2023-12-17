/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:00:02 by flverge           #+#    #+#             */
/*   Updated: 2023/12/17 11:48:54 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	***args_parsing(int ac, char **av)
{
	// ! IMPORTANT : each av == 1 command
	char	***result;
	int		i; // index de arg
	int		j; // index de result
	char	space;
	// int 	index_last_arg;

	i = 2;
	j = 0;
	space = 32;
	// index_last_arg = ac - 2;
	// i = 0;
	result = (char ***)malloc(sizeof(char **) * (ac - 3) + 1); // extra spot for NULL
	if (!result)
		error_quit("Malloc failed");
	while ((i + j) <= (ac - 2))
	{
		result[j] = (char **)malloc(sizeof(char *) * (ft_arg_countwords(av[i + j], 32)) + 1);
		if (!result[j])
			error_quit("Malloc failed");
		result[j] = ft_arg_split(av[i + j], space);
		j++;
	}
	// null terminating char ***
	result[j] = NULL;
	return (result);
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
