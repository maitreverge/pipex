/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TryHardTeam <TryHardTeam@123.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:23:55 by flverge           #+#    #+#             */
/*   Updated: 2024/12/17 16:46:17 by TryHardTeam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void voluntary_failing(char *join_buff, char **splitted_command, char **envp)
{
    execve(join_buff, splitted_command, envp);
    perror("execve");
    free(join_buff);
    free_split(splitted_command);
    exit(EXIT_FAILURE);
}

static void	ft_exec(char *command, char **envp, t_paths **paths)
{
	t_paths	*temp_paths;
	char	**splitted_command;
	char	*join_buff;

	temp_paths = *paths;
	join_buff = 0;
	splitted_command = ft_split(command, ' ');
	while (temp_paths->next != 0)
	{
		if (join_buff)
			free(join_buff);
		join_buff = ft_strjoin(temp_paths->path, splitted_command[0]);
		if (access(join_buff, F_OK) == 0)
		{
			if (execve(join_buff, splitted_command, envp) == -1)
				return (perror("execve"), exit_and_message("", 127));
			free(join_buff);
			break ;
		}
		temp_paths = temp_paths->next;
	}
	if (!temp_paths->next && join_buff)
		voluntary_failing(join_buff, splitted_command, envp);
	free_split(splitted_command);
}
