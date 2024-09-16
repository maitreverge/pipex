/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:27:16 by flverge           #+#    #+#             */
/*   Updated: 2024/09/16 09:08:35 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool file_rights(const char* file1, const char *file2)
{
    // if open fails == -1. IF success, return positive value
    int fd_file1;
    int fd_file2;

    fd_file1 = open(file1, O_RDONLY);

    fd_file2 = access(file2, F_OK); // f_OK == fileOK !
    
    if (fd_file1 == -1)
        return false;
    
    if (fd_file2 == 0) // if file exists, check rights
    {
        if (open(file2, O_RDWR) == -1)
            return false; //
    }
    else // if file2 does not exist, create file 2
    {
        if (open(file2, O_RDWR | O_CREAT | 0644) == -1)
            return false; // failed creating the file
    }
    return true;
}

void    init_checks(int ac, char** av, char **envp, t_paths *paths)
{
    const char *file1;
    const char *file2;

    if (ac != 5)
        exit_and_message("Error\nPipex require 5 arguments", 1);
    file1 = av[1];
    file2 = av[4];
    // ! to do
    if (not file_rights(file1, file2)) 
        exit_and_message("Error\nFile1 or File2 has not correct authorizations", 1);
    if (parse_paths(envp, paths) == 1) // if there is errors
        exit_and_message("PATH env variable not found", 1);
}

int main(int ac, char **av, char **envp)
{
    t_paths s_paths;
    t_vars vars;
    
    init_checks(ac, av, envp, &s_paths);
    
}
