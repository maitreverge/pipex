/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:00:02 by flverge           #+#    #+#             */
/*   Updated: 2023/12/19 13:09:04 by flverge          ###   ########.fr       */
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
		// ! create a char ** buffer ready to welcome splitted args
		// buffer[j] = malloc(sizeof(char *) * (ft_arg_ctw(av[i + j], space)) + 1);
		// if (!buffer[j])
		// 	error_quit("Malloc failed");
		buffer[j] = ft_arg_split(av[i + j], space);
		j++;
	}
	buffer[j] = NULL;
	return (buffer);
}

// ! UNSUSED FT because custom split implemented
char	**joined_path(char **path)
{
	int len_path;
	char **result;
	int i = 0;
	int k = 0;
	// lenght total char ** for rellallocating path + /
	while (path[i] != NULL)
		i++;
	
	result = malloc(sizeof(char *) * (i + 1)); // another space
	if (!result)
		error_quit("Failled malloc");
	i = 0;
	
	while (path[i] != NULL)
	{
		// result[k] = malloc(ft_strlen(path[i]) + 2); // +1 for '\0' and + 1 for '/' char
		// if (!result[k])
		// 	error_quit("malloc Failed");
		result[k] = ft_strjoin(path[i], "/");
		i++;
		k++;
	}
	result[i] = NULL;

	i = 0;
	while (path[i] != NULL)
	{
		free(path[i]);
		i++;
	}
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
		
	// ! custom split that adds a ending / char	
	result = ft_pipex_split(path, ':');
	if (!result)
		error_quit("Split function failed");

	free(path);
	return (result);
}
