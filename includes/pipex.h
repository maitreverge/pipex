/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:41:08 by flverge           #+#    #+#             */
/*   Updated: 2023/12/24 21:57:41 by flverge          ###   ########.fr       */
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

typedef struct s_arg_split
{
	size_t	i;
	size_t	j;
	size_t	start;
	size_t	len;
	int		inside_quotes;
}				t_arg_split;

// pipex.c
void	check_args_mandatory(char **av, int *fd, t_vars *vars);

void	pipex_mandatory(char **av, t_vars *vars);
t_vars	init_struct(int ac, char **av, char **envp, t_vars *vars);
void	print_arg(t_vars *vars, int ac);
void	free_vars(t_vars *vars);





// pipex_bonus.c
void	pipex_bonus(int ac, char **av, char **env);

// utils.c
int		ft_strcmp(char *s1, char *s2);
void	error_quit(char *str);

// parsing_1.c
char	***args_parsing(int ac, char **av);
char	**path_parsing(char **av, char **envp);


// parsing_2.c
char	*ft_strncpy(char *dest, char const *src, size_t n);
void	arg_sub_check(char const *s, char c, t_arg_split *vars);
void	arg_allocation(char **buffer, char const *s, char c, size_t len_s);

size_t	ft_arg_ctw(char const *str, char space);
char	**ft_arg_split(char const *s, char space);

// custom_split.c
static char	*pipex_ft_strncpy(char *dest, char const *src, size_t n);
static void	pipex_sub_check(char const *s, char c, size_t *i, size_t *start);
static void	pipex_allocation(char **buffer, char const *s, char c, size_t len_s);
static size_t	ft_pipex_countwords(char const *str, char c);

char	**ft_pipex_split(char const *s, char c);


#endif