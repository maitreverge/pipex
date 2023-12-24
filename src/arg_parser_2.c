/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 22:19:52 by flverge           #+#    #+#             */
/*   Updated: 2023/12/24 22:21:40 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

void	arg_sub_check2(t_arg_split *vars, char const *s)
{
	vars->len = vars->i - vars->start;
	if (s[vars->start] == 39)
	{
		vars->start++;
		vars->len--;
		vars->inside_quotes = 1;
	}
	if (vars->inside_quotes && s[vars->i - 1] == 39)
	{
		vars->len--;
		vars->inside_quotes = 0;
	}
}

void	sub_ctw1(t_arg_split *vars, char const *str)
{
	vars->i++;
	while (str[vars->i] != vars->quote && str[vars->i])
		vars->i++;
	if (str[vars->i] == vars->quote)
	{
		vars->result++;
		vars->i++;
	}
	else
		exit (-1);
}

void	sub_ctw2(t_arg_split *vars, char const *str, char space)
{
	while (str[vars->i])
	{
		if (str[vars->i] == space)
			break ;
		else if (str[vars->i] == vars->quote)
		{
			vars->i++;
			while (str[vars->i] != vars->quote && str[vars->i])
				vars->i++;
			vars->i++;
			break ;
		}
		vars->i++;
	}
	vars->result++;
}
