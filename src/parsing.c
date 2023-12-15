/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:00:02 by flverge           #+#    #+#             */
/*   Updated: 2023/12/15 12:15:04 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**args_parsing(int ac, char **av)
{
	// ! IMPORTANT : each av == 1 command
	
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
