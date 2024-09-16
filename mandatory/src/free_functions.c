/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:50:09 by flverge           #+#    #+#             */
/*   Updated: 2024/09/16 10:56:25 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void    free_split(char **to_free)
{
    char **original = to_free;
    
    while (*to_free != 0)
    {
        free(*to_free);
        to_free++;
    }
    free(original);
}

void    free_paths(t_paths *paths)
{
    int size = path_lstsize(paths);

    int i = 0;

    t_paths *current = paths;

    t_paths *next_path = paths;

    while ( i < size )
    {
        current = next_path;
        next_path = current->next;
        free(current->path);
        free(current);
        ++i;
    }
}