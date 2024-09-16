/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 08:15:34 by flverge           #+#    #+#             */
/*   Updated: 2024/09/16 08:18:00 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    exit_and_message(const char *message, const int exit_code)
{
    ft_printf("%s\n");
    exit(exit_code);
}