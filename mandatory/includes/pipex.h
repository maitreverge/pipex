/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:41:08 by flverge           #+#    #+#             */
/*   Updated: 2024/09/24 21:23:27 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H 

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

typedef struct s_paths 
{
    char    *path;
    struct s_paths *next;
    
}   t_paths;

// ! For variables declarations
typedef struct s_vars 
{
    char *temp_buf;
    size_t i;
    size_t j;
    size_t k;
    size_t l;
    long l_i;
    long l_j;
    long l_k;
    long l_l;
    
}   t_vars;


void    exit_and_message(const char *message, const int exit_code);

bool check_paths(char **envp, t_paths **paths);

t_paths	*path_lstnew(char *content);
t_paths	*path_lstlast(t_paths *lst);
void	path_add_back(t_paths **lst, t_paths *new);
int	path_lstsize(t_paths *lst);


void    free_split(char **to_free);

void    free_paths(t_paths *paths);

void print_paths(t_paths *paths, const char* str);

void    pipex(char **av, char **envp, t_paths **paths);




#endif