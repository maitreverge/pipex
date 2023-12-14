/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:00:02 by flverge           #+#    #+#             */
/*   Updated: 2023/12/14 14:35:01 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**path_parsing(char **av, char **envp)
{
	char **env;
	char **result;
	char *path;

	env = envp;
	// * TO DO = Maybe not the right function, maybe other evnp are named PATH=
	while (ft_strncmp(*env, "PATH=", 5) && *env) // ! STEP 1 : looping through env for looking path
		env++;
	if (*env) // check if PATH has been found, if not exit
		path = ft_strtrim(*env, "PATH="); // trim path 5 char from the left,
	else
		error_quit("PATH envp couldn't be found");
	result = ft_split(path, ':');
	if (!result)
		error_quit("Split path failed");
		
	// testing the path spliting
	for (int i = 0; result[i]; i++)
		ft_printf("Path number %i = %s", i+1, result[i]);
	ft_printf("\n\n-------\n\nend parsing path");	
	
	free(path);
	return (result); // needs freeing
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