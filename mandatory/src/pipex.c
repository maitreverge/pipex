/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:23:55 by flverge           #+#    #+#             */
/*   Updated: 2024/09/16 20:57:15 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    pipex(char **av, char **envp, t_paths **paths)
{
    // FD 0 = stdin
    // FD 1 = stdout

    // pipe fd : fd[0] => read end
    // fd[1] => write end
    /*          
        WRITE   =====================  READ
        fd[1]            -->          fd[0]
                =====================
    */
    int fd[2];

    if (pipe(fd) == -1)
        exit_and_message("Pipe Failed", 1); // needs to free struct
    
    

    
}
