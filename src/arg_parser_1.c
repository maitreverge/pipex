/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 11:15:17 by flverge           #+#    #+#             */
/*   Updated: 2023/12/24 22:21:30 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_strncpy(char *dest, char const *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

void	arg_allocation(char **buffer, char const *s, char c, size_t len_s)
{
	t_arg_split	vars;

	vars.i = 0;
	vars.j = 0;
	vars.start = 0;
	vars.inside_quotes = 0;
	if (!s)
		return ;
	while (s[vars.i])
	{
		arg_sub_check(s, c, &vars);
		if (vars.j < len_s)
		{
			arg_sub_check2(&vars, s);
			buffer[vars.j] = ft_calloc(sizeof(char), (vars.len + 1));
			if (!buffer[vars.j])
				return ;
			ft_strncpy(buffer[vars.j], &s[vars.start], vars.len);
			vars.j++;
		}
		vars.i++;
	}
}

size_t	ft_arg_ctw(char const *str, char space)
{
	t_arg_split	vars;

	vars.result = 0;
	vars.quote = 39;
	vars.i = 0;
	if (!str)
		return (0);
	while (str[vars.i])
	{
		while (str[vars.i] == space && str[vars.i])
			vars.i++;
		if (str[vars.i] == vars.quote)
			sub_ctw1(&vars, str);
		else if (str[vars.i] != space && str[vars.i])
			sub_ctw2(&vars, str, space);
	}
	return (vars.result);
}

char	**ft_arg_split(char const *s, char space)
{
	char	**buffer;
	size_t	len_s;

	len_s = ft_arg_ctw(s, space);
	buffer = (char **)ft_calloc(sizeof(char *), (len_s + 1));
	if (!buffer)
		return (NULL);
	arg_allocation(buffer, s, space, len_s);
	return (buffer);
}
