/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:41:08 by flverge           #+#    #+#             */
/*   Updated: 2023/12/15 17:43:41 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H 

# include "../libft/libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/get_next_line/get_next_line_bonus.h"
# include <unistd.h> // write, close, access, dup, dup2, execve
# include <fcntl.h> // open and options
# include <stdlib.h> // malloc and free and EXIT_SUCCESS / EXIT_FAILURE
# include <stdio.h> // perror
# include <errno.h> // makes errno a global variable usable with strerror(errno)
# include <string.h>
# include <sys/wait.h>

typedef struct s_parsing
{
	char	**path;
	char	***args;
}			t_parsing;

typedef struct s_vars
{
	t_parsing	parsing;
	int			fd[2];
	int			pipe_fd[2];
	int			status;
	pid_t		pid;
}				t_vars;

// pipex.c
void	pipex_mandatory(char **av, t_vars *vars);

// pipex_bonus.c
void	pipex_bonus(int ac, char **av, char **env);

// utils.c
int		ft_strcmp(char *s1, char *s2);
void	error_quit(char *str);

// parsing.c
char	**path_parsing(char **av, char **envp);

#endif