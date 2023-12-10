/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:12:36 by flverge           #+#    #+#             */
/*   Updated: 2023/12/10 09:22:44 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	check_args_mandatory(char **av, int *fd)
{
	if (!(access(av[1], F_OK | R_OK))) // checks if infile exists and readable
		*fd[0] = open(av[1], O_RDONLY);
	else
		access_denied();
	
	// ! check for outfile
	if (!(access(av[4], F_OK))) // checks if outfile exists
	{
		if (!(access(av[4], W_OK)))
			*fd[1] = open(av[4], O_WRONLY);
		else
			access_denied();
	}
	else // needs to create outfile
		*fd[1] = open(av[4], O_CREAT | O_TRUNC | O_WRONLY); // ? right syntax ?

	if (*fd[0] < 0 || *fd[1] < 0)
		access_denied();
}

void	pipex_mandatory(int ac, char **av, char **env)
{
	int fd[2];

	if (!ft_strcmp(av[2], "here_doc")) // gestion bonus 2
	{
		
	}
	else // mandatory part
	{
		check_args_mandatory(av, &fd);
		
		
		
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
	if (ac >= 5)
	{
		if (ac == 5)
			pipex_mandatory(ac, av, envp);
		else
			pipex_bonus(ac, av, envp);
		return (0);
	}
	else
	{
		ft_printf("Not enough arguments.\nUsage : ./pipex  <file1>  <command_1>  <command_2>  ...  <file2>"); // needs better cases handling
		return (1);
	}
}

/*
Reminder fd

Read from stdin => read from fd 0:
Whenever we write any character from the keyboard, it reads from stdin through fd 0 and saves to a file named /dev/tty.

Write to stdout => write to fd 1:
Whenever we see any output to the video screen, it’s from the file named /dev/tty and written to stdout in screen through fd 1.

Write to stderr => write to fd 2:
We see any error to the video screen, it is also from that file write to stderr in screen through fd 2.

*/
