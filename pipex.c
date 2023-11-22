/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:12:36 by flverge           #+#    #+#             */
/*   Updated: 2023/11/22 21:38:13 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	pipex_madatory(void)
{
	// mdr je met quoi ici ?
}

void	pipex_bonus(void)
{
	// Ok Google, code pipex stp c tro dur :(
}

int	main(int ac, char **av, char **envp) // ! travailler sur les variables d'environement
{
	if (ac >= 4)
	{
		if (ac == 4)
			pipex_mandatory();
		else
			pipex_bonus(); 
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
