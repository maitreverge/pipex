/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:41:08 by flverge           #+#    #+#             */
/*   Updated: 2023/12/24 23:08:37 by flverge          ###   ########.fr       */
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

# define EX execve

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
	char	quote;
	size_t	result;
}				t_arg_split;


// arg_parser_1
char			*ft_strncpy(char *dest, char const *src, size_t n);
void			arg_alloc(char **buffer, char const *s, char c, size_t len_s);
size_t			ft_arg_ctw(char const *str, char space);
char			**ft_arg_split(char const *s, char space);

// arg_parser_2
void			arg_sub_check(char const *s, char c, t_arg_split *vars);
void			arg_sub_check2(t_arg_split *vars, char const *s);
void			sub_ctw1(t_arg_split *vars, char const *str);
void			sub_ctw2(t_arg_split *vars, char const *str, char space);

// custom_split
static char		*pipex_ft_strncpy(char *dest, char const *src, size_t n);
static void		p_sub_check(char const *s, char c, size_t *i, size_t *start);
static void		p_alloc(char **buffer, char const *s, char c, size_t len_s);
static size_t	ft_pipex_countwords(char const *str, char c);
char			**ft_pipex_split(char const *s, char c);

// parsing4struct
char			***args_parsing(int ac, char **av);
char			**path_parsing(char **av, char **envp);
void			check_args_mandatory(char **av, int *fd, t_vars *vars);

// utils
int				ft_strcmp(char *s1, char *s2);
void			error_quit(char *str);
void			free_vars(t_vars *vars);
t_vars			init_struct(int ac, char **av, char **envp, t_vars *vars);

// pipex
void			pipex_mandatory(char **av, t_vars *vars);

#endif