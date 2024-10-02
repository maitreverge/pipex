/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_gnl_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:30:20 by flverge           #+#    #+#             */
/*   Updated: 2024/10/02 11:52:24 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// int	custom_get_next_line(char **line)
// {
// 	char	*buffer;
// 	int		i;
// 	int		read_buff;
// 	char	c;

// 	i = 0;
// 	read_buff = 0;
// 	buffer = (char *)malloc(10000);
// 	if (!buffer)
// 		return (-1);
// 	read_buff = read(0, &c, 1);
// 	while (read_buff && c != '\n' && c != '\0')
// 	{
// 		if (c != '\n' && c != '\0')
// 			buffer[i] = c;
// 		i++;
// 		read_buff = read(0, &c, 1);
// 	}
// 	buffer[i] = '\n';
// 	buffer[++i] = '\0';
// 	*line = buffer;
// 	// free(buffer);
// 	return (read_buff);
// }
