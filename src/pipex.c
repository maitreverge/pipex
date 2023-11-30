/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:12:36 by flverge           #+#    #+#             */
/*   Updated: 2023/11/30 10:34:35 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	pipex_madatory(void)
{
	
	
}

void	pipex_bonus(void)
{
	if (!ft_strcmp(av[2], "here_doc"))
	{
		// gerer le here_doc
	}
	else // multiple pipes handeling
	{
		
	}
	
	
}

int	main(int ac, char **av, char **envp) // ! travailler sur les variables d'environement
{
	if (ac >= 4)
	{
		if (ac == 4)
			pipex_mandatory(ac, av, envp);
		else
			pipex_bonus(ac, av, envp); 
	}
	else
	{
		ft_printf("Not enough arguments.\nUsage : ./pipex  <file1>  <command_1>  <command_2>  ...  <file2>");
		return (-1);
	}
}

// Chat GPT le sang
#include <stdio.h>

int main(int argc, char **argv, char **envp) {
    // Print environment variables
    while (*envp != NULL) {
        printf("envp: %s\n", *envp);
        envp++;
    }

    return 0;
}
