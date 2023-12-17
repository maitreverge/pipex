/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:00:02 by flverge           #+#    #+#             */
/*   Updated: 2023/12/16 10:28:54 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int		nb_args(char *av)
{
	char	space;
	char	quote;
	int		i;

	i = 0;
	space = 32; // space ascii
	quote = 39; // simple quote ' ascii
	
	while ()


	
}

char	***args_parsing(int ac, char **av)
{
	// ! IMPORTANT : each av == 1 command
	char	***result;
	int 	index_current;
	int 	index_last_arg;
	int		i;

	index_current = 2;
	index_last_arg = ac - 2;
	i = 0;
	result = (char ***)malloc(sizeof(char **) * (ac - 3) + 1); // extra spot for NULL
	if (!result)
		error_quit("Malloc failed");
	while (index_current <= index_last_arg)
	{
		// counting the correct number or argument, including the simple quotes
		result[i] = (char **)malloc(sizeof(char **) * (nb_args(av[i]) + 1))
		
		// ! TO DO : add null at the end of char**
		i++;
		index_current++;
	}

	// ! TO DO : add null and the end of char***
	
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
