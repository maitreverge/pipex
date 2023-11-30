/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:12:36 by flverge           #+#    #+#             */
/*   Updated: 2023/11/30 11:09:29 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	pipex_madatory(void)
{
	if (!ft_strcmp(av[2], "here_doc")) // gestion bonus 2
	{
		
	}
	else // mandatory part
	{
		// gerer l'ouverture des fd
		// gerer les droits
		// gerer les pipes
		// gerer les forks
		// gerer les execve
		// gerer les waitpid
		// gerer les close
		// gerer les free
	}
}

int	main(int ac, char **av, char **envp)
{
	if (ac >= 4)
	{
		if (ac == 4)
			pipex_mandatory(ac, av, envp);
		else
			pipex_bonus(ac, av, envp);
		return (0);
	}
	else
	{
		ft_printf("Not enough arguments.\nUsage : ./pipex  <file1>  <command_1>  <command_2>  ...  <file2>");
		return (1);
	}
}
