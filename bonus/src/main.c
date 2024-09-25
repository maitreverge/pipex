/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:27:16 by flverge           #+#    #+#             */
/*   Updated: 2024/09/25 11:41:41 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	init_checks(int ac, char **envp, t_paths **paths)
{
	if (ac != 5)
		exit_and_message("Error\nPipex require 5 arguments", 1);
	if (!check_paths(envp, paths))
		exit_and_message("PATH env variable not found", 1);
}

int	main(int ac, char **av, char **envp)
{
	t_paths	*paths;

	paths = NULL;
	init_checks(ac, envp, &paths);
	++av;
	pipex(av, envp, &paths);
	free_paths(paths);
}
