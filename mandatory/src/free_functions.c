/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:50:09 by flverge           #+#    #+#             */
/*   Updated: 2024/09/25 10:14:34 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	free_split(char **to_free)
{
	char	**original;

	original = to_free;
	while (*to_free != 0)
	{
		free(*to_free);
		to_free++;
	}
	free(original);
}

void	free_paths(t_paths *paths)
{
	t_paths	*current;
	t_paths	*next_path;

	current = paths;
	while (current != NULL)
	{
		next_path = current->next;
		free(current->path);
		free(current);
		current = next_path;
	}
}
