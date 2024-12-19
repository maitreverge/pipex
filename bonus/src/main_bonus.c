/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@123.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:27:16 by flverge           #+#    #+#             */
/*   Updated: 2024/12/17 15:42:40 by flverge      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*init_checks(int ac, char **av, char **envp, t_paths **paths)
{
	if (ac < 5)
		exit_and_message("Error\nPipex Bonus requires at least 5 arguments", 1);
	else if (!check_paths(envp, paths))
		exit_and_message("PATH env variable not found", 1);
	if (ac == 6 && !ft_strcmp("here_doc", av[1]))
		return ("here_doc");
	else if (ac >= 5)
		return ("multi_pipes");
	return (NULL);
}

int	main(int ac, char **av, char **envp)
{
	t_paths	*paths;
	char	*which_bonus;

	which_bonus = NULL;
	paths = NULL;
	which_bonus = init_checks(ac, av, envp, &paths);
	++av;
	if (!ft_strcmp("here_doc", which_bonus))
		ft_here_doc(av, envp, &paths);
	else if (!ft_strcmp("multi_pipes", which_bonus))
		ft_multi_pipes(av, ac, envp, &paths);
	else
		ft_printf("Error:\nWrong arguments");
	free_paths(paths);
}
