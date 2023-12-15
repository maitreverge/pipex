/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:00:02 by flverge           #+#    #+#             */
/*   Updated: 2023/12/15 11:39:20 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**path_parsing(char **av, char **envp)
{
	char **env;
	char **result;
	char *path;

	env = envp;
	while (*env != NULL) // Loop through envp array
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0) // Check if the string starts with "PATH="
			break;
		env++;
	}
	// printf("Untrimed string = %s\n\n", *env);
	if (*env) // Check if PATH has been found, if not exit
	{
		path = ft_strtrim(*env, "PATH=");
		if (!path)
			error_quit("Strtrim path failed");
	}
	else
		error_quit("PATH envp couldn't be found");
	// ! checked trimed string
	// printf("Strimmed string = %s\n\n", path);
	
	result = ft_split(path, ':');
	if (!result)
		error_quit("Split path failed");

	// Testing the path splitting
	// for (int i = 0; result[i] != NULL; i++)
	// 	printf("Path number %i = %s\n", i + 1, result[i]);
	// ft_printf("\n\n-------\n\nend parsing path");	
	
	free(path);
	return (result); // Needs freeing
}
// ! parser 
/*

String a parser :

PATH=/nfs/homes/flverge/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin

parser les variables d'env pour :

1 - retrouver PATH 

2 - Spliter cette string de l'enfer avec le char :

3 - et plus tard, join le string du path avec celui de l'argument (mdr anvi 2 crever)

*/