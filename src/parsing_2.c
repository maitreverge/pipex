/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 11:15:17 by flverge           #+#    #+#             */
/*   Updated: 2023/12/24 21:55:55 by flverge          ###   ########.fr       */
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

void	arg_sub_check(char const *s, char c, t_arg_split *vars)
{
	char	quote;
	int		inside_quotes;

	quote = 39;
	inside_quotes = 0;
	while (s[vars->i] == c)
		vars->i++;
	vars->start = vars->i;
	while (s[vars->i] && (inside_quotes || s[vars->i] != c))
	{
		if (s[vars->i] == quote)
			inside_quotes = !inside_quotes;
		vars->i++;
	}
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
			vars.len = vars.i - vars.start;
			if (s[vars.start] == 39)
			{
				vars.start++;
				vars.len--;
				vars.inside_quotes = 1;
			}
			if (vars.inside_quotes && s[vars.i - 1] == 39)
			{
				vars.len--;
				vars.inside_quotes = 0;
			}
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
	size_t	result;
	int		i;
	char	quote;

	result = 0;
	quote = 39;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] == space && str[i])
			i++;
		if (str[i] == quote)
		{
			i++;
			while (str[i] != quote && str[i])
				i++;
			if (str[i] == quote)
			{
				result++;
				i++;
			}
			else
				exit (-1);
		}
		else if (str[i] != space && str[i])
		{
			while (str[i])
			{
				if (str[i] == space)
					break ;
				else if (str[i] == quote)
				{
					i++;
					while (str[i] != quote && str[i])
						i++;
					i++;
					break ;
				}
				i++;
			}
			result++;
		}
	}
	return (result);
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
