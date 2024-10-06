/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:41:08 by flverge           #+#    #+#             */
/*   Updated: 2024/10/06 10:02:36 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H 

# define HERE_DOC_NAME "here_doc"

# include "../../libft/libft/libft.h"
# include "../../libft/ft_printf/ft_printf.h"
# include "../../libft/get_next_line/get_next_line_bonus.h"
# include <unistd.h> // write, close, access, dup, dup2, execve
# include <fcntl.h> // open and options
# include <stdlib.h> // malloc and free and EXIT_SUCCESS / EXIT_FAILURE
# include <stdio.h> // perror
# include <errno.h> // makes errno a global variable usable with strerror(errno)
# include <string.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <time.h>
# include <stdint.h> // for random char* generator

typedef struct s_paths
{
	char			*path;
	struct s_paths	*next;
}				t_paths;

// free_functions.c
void	free_split(char **to_free);
void	free_paths(t_paths *paths);

// linked_list_functions.c
int		path_lstsize(t_paths *lst);
t_paths	*path_lstnew(char *content);
t_paths	*path_lstlast(t_paths *lst);
void	path_add_back(t_paths **lst, t_paths *new);

// parse_paths.c
bool	check_paths(char **envp, t_paths **paths);

// pipex.c
// ! DEPRECIATED FUNCTION
// void	pipex(char **av, char **envp, t_paths **paths);

// sys_functions.c
void	exit_and_message(const char *message, const int exit_code);
int		ft_strcmp(const char *s1, const char *s2);

// ft_here_doc.c
void	ft_here_doc(char **av, char **envp, t_paths **paths);

// ft_multi_pipes.c
void	ft_multi_pipes(char **av, int ac, char **envp, t_paths **paths);

// char *generate_random_string(size_t length);

void	ft_exec(char *command, char **envp, t_paths **paths);

int	custom_get_next_line(char **line);



#endif