/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:40:04 by flverge           #+#    #+#             */
/*   Updated: 2024/09/25 10:14:53 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	path_lstsize(t_paths *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_paths	*path_lstnew(char *content)
{
	t_paths	*new_element;

	new_element = (t_paths *)malloc(sizeof(t_paths));
	if (!new_element)
		return (NULL);
	new_element->path = content;
	new_element->next = NULL;
	return (new_element);
}

t_paths	*path_lstlast(t_paths *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	path_add_back(t_paths **lst, t_paths *new)
{
	t_paths	*last;

	if (!lst || !new)
		return ;
	last = path_lstlast(*lst);
	if (!last)
		*lst = new;
	else
		last->next = new;
}
