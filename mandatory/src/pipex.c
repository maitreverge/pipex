/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:23:55 by flverge           #+#    #+#             */
/*   Updated: 2024/09/24 11:21:18 by flverge          ###   ########.fr       */
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
   (void)envp;
   (void)paths;
   (void)av;
//    printf("First argument = %s\n", av[0]);

    
    int fd[2]; // pipes fd
    int fork_pid;

    if (pipe(fd) == -1)
        exit_and_message("Pipe Failed", 1); // needs to free struct
    
    fork_pid = fork();
    if (fork_pid == -1)
        exit_and_message("Fork failed", 1); // needs to free struct
    
    int hehehe = 0;
    if (fork_pid == 0) // child process
    {
        printf("pid fork child = %i\n", fork_pid);
        printf("This is the child process\n\n");
        sleep(3);
        printf("PRINT HEHE = %i\n", ++hehehe);
        // ++hehehe;
    }
    waitpid(fork_pid, 0, 0);
    printf("HEHEHpid fork parent = %i\n\n", fork_pid);
    printf("This is the parent process\n\n");
    printf("pid fork parent = %i\n", fork_pid);
    
    printf("blblbllblblblblblblblb\n\n");

    // ++hehehe;
    printf("PRINT HEHE = %i\n", ++hehehe);
    
    
    printf("pid fork parent = %i\n", fork_pid);
    
    
    

    
}
