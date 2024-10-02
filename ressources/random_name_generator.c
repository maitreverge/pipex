/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_name_generator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:39:29 by flverge           #+#    #+#             */
/*   Updated: 2024/09/26 12:21:13 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/**
 * @brief Returns a random alpha-numeric string of size
 * `length`.
 * 
 * The functions takes the adress of the given param `length`,
 * and use it as a seed for generating a random position of each
 * iteration of the result string.
 * 
 * @param length 
 * @return char* 
 */
char *generate_random_string(size_t length)
{
	long unsigned int	seed;
	size_t				len_ascii;
	size_t				i;
	char				*result;
	char				*ascii;

	i = -1;
	ascii = "123456789qwertyuiopasdfghjklzxcvbnm";
	len_ascii = ft_strlen(ascii);
	result = (char*)ft_calloc(sizeof(char), length);
	if (!result)
		exit_and_message("Failed malloc", 1);
	seed = (long unsigned int)&length;
	while (++i < length)
	{
		result[i] = ascii[(i + seed) % len_ascii];
	}
	return (result);
}
