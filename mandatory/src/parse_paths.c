/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:09:52 by flverge           #+#    #+#             */
/*   Updated: 2024/09/16 09:52:45 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void parse_paths(char *buf, t_paths *paths)
{
    char *rm_path = ft_strtrim(buf, "PATH=");

    char **splited_paths = ft_split(rm_path, ':');

    
    // need to append a '/' at the end of each paths
    while (*splited_paths != 0)
    {
        path_add_back(&paths, path_lstnew(ft_strjoin(*splited_paths, "/")));
        splited_paths++;
    }
    
    free(rm_path);
    free_split(splited_paths);
}

bool check_paths(char **envp, t_paths *paths)
{
    char    *target = "PATH=";
    char    **temp_envp = envp;
    
    // Check if there is a PATH env varable
    while (*temp_envp != 0)
    {
        if (ft_strncmp(*temp_envp, target, ft_strlen(target)) == 0)
            break;
        temp_envp++;
    }
    if (*temp_envp == 0) // if PATH not found
        return false;
    
    parse_paths(*temp_envp, paths);

    return true;
}
