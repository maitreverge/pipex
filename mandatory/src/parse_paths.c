/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:09:52 by flverge           #+#    #+#             */
/*   Updated: 2024/09/16 14:12:57 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void parse_paths(char *buf, t_paths *paths)
{
    printf("DEBUG3 = %p\n", &paths);

    char *rm_path = ft_strtrim(buf, "PATH=");

    char **splited_paths = ft_split(rm_path, ':');
    
    // need to append a '/' at the end of each paths
    while (*splited_paths != 0)
    {
        char *to_insert = ft_strjoin(*splited_paths, "/");
        
        if (!paths)
            paths = path_lstnew(to_insert);
        else
            path_add_back(&paths, path_lstnew(to_insert));
        // printf("CURRENT = %s\n", to_insert);
        splited_paths++;
        free(to_insert);
    }

    // displays paths struct
    // for (t_paths *temp = paths; temp != 0; temp = temp->next)
    // {
    //     printf("Current node adress = %p\n", temp);
    //     printf("Current node path = %s\n", temp->path);
    //     printf("Current node next adress = %p\n", temp->next);
    //     printf("========\n");
    // }
    
    free(rm_path);
    free_split(splited_paths);
}

bool check_paths(char **envp, t_paths *paths)
{
    printf("DEBUG2 = %p\n", paths);
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
