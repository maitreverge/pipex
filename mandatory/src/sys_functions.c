/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 08:15:34 by flverge           #+#    #+#             */
/*   Updated: 2024/09/16 17:54:39 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    exit_and_message(const char *message, const int exit_code)
{
    ft_printf("%s\n", message);
    exit(exit_code);
}

void print_paths(t_paths *paths, const char* str)
{
    printf("%s\n=======\n\n", str);
    for (t_paths *temp = paths; temp != 0; temp = temp->next)
    {
        printf("Current node adress = %p\n", temp);
        printf("Current node path = %s\n", temp->path);
        printf("Current node next adress = %p\n", temp->next);
        printf("========\n");
    }
}