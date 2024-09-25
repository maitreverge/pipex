/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:09:52 by flverge           #+#    #+#             */
/*   Updated: 2024/09/25 11:41:43 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	parse_paths(char *buf, t_paths **paths)
{
	char	**splited_paths;
	char	**copy_split;
	char	*trimmed;

	trimmed = ft_strtrim(buf, "PATH=");
	splited_paths = ft_split(trimmed, ':');
	copy_split = splited_paths;
	*paths = path_lstnew(ft_strjoin(*(splited_paths)++, "/"));
	while (*splited_paths != 0)
	{
		path_add_back(paths, path_lstnew(ft_strjoin(*splited_paths, "/")));
		splited_paths++;
	}
	free(trimmed);
	free_split(copy_split);
}

bool	check_paths(char **envp, t_paths **paths)
{
	char	**temp_envp;
	char	*target;

	temp_envp = envp;
	target = "PATH=";
	while (*temp_envp != 0)
	{
		if (ft_strncmp(*temp_envp, target, ft_strlen(target)) == 0)
			break ;
		temp_envp++;
	}
	if (*temp_envp == 0)
		return (false);
	parse_paths(*temp_envp, paths);
	return (true);
}
