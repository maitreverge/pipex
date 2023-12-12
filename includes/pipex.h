/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:41:08 by flverge           #+#    #+#             */
/*   Updated: 2023/12/12 12:17:12 by flverge          ###   ########.fr       */
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
# include <sys/wait.h>



// pipex.c
void	pipex_mandatory(int ac, char **av, char **env);

// pipex_bonus.c
void	pipex_bonus(int ac, char **av, char **env);

// utils.c
int		ft_strcmp(char *s1, char *s2);
void	access_denied(void);





#endif