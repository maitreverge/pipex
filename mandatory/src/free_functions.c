/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:50:09 by flverge           #+#    #+#             */
/*   Updated: 2024/09/16 14:09:02 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void    free_split(char **to_free)
{
    // char **original = to_free;
    
    while (*to_free != 0)
    {
        free(*to_free);
        to_free++;
    }
    // free(original);
}

void    free_paths(t_paths *paths)
{
    printf("DEBUG4 = %p\n", &paths);

    t_paths *current = paths;

    t_paths *next_path;

    for (t_paths *temp = paths; temp != 0; temp = temp->next)
    {
        printf("Current node adress = %p\n", temp);
        printf("Current node path = %s\n", temp->path);
        printf("Current node next adress = %p\n", temp->next);
        printf("========\n");
    }
    
    while ( current != NULL )
    {
        next_path = current->next;
        free(current->path);
        // free(current);
        current = next_path;
    }
}