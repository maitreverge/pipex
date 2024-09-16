/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:27:16 by flverge           #+#    #+#             */
/*   Updated: 2024/09/16 08:35:46 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    init_checks(int ac, char** av, char **envp, t_paths *paths)
{
    char *file1;
    char *file2;

    if (ac != 5)
        exit_and_message("Error\nPipex require 5 arguments", 1);
    file1 = av[1];
    file2 = av[4];
    // ! to do
    if (file_rights(file1) != 1) 
        exit_and_message("Error\nFile1 has not read authorizations", 1);
    // ! to do
    else if (file_rights(file2) != 2)
        exit_and_message("Error\nFile1 has not read AND write authorizations", 1);
    if (parse_paths(envp, paths) == 1) // if there is errors
        exit_and_message("PATH env variable not found", 1);
}

// main does need to be 5 arguments
int main(int ac, char **av, char **envp)
{
    t_paths s_paths;
    t_vars vars;
    
    init_checks(ac, av, envp, &s_paths);
    
}
