/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <flverge@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:23:55 by flverge           #+#    #+#             */
/*   Updated: 2024/09/24 21:17:55 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    ft_exec(char *command, char **envp, t_paths **paths)
{
    t_paths *temp_paths;

    temp_paths = *paths;

    char *join_buff = 0;

    char **splitted_command = ft_split(command, ' ');

    while(temp_paths->next != 0)
    {
        if (join_buff)
            free(join_buff);
        join_buff = ft_strjoin(temp_paths->path, splitted_command[0]);  // tester cm1 = "" for segfault
        // success access == 0
        if (access(join_buff, F_OK) == 0)
        {
            if (execve(join_buff, splitted_command, envp) == -1)
                printf("%s Failed To Execute\n", join_buff);
            free(join_buff);
            break;
        }
        temp_paths = temp_paths->next;
    }
    
    if (!temp_paths->next && join_buff) // last node AND still not found because of the join_buff still up
    {
        execve(join_buff, splitted_command, envp);
        printf("Pipex could not found the path to execute %s\n", join_buff);
        perror(strerror(errno));
        free(join_buff);
    }
    free_split(splitted_command);
}

/* ! EXECVE

    char *program_path = "/bin/ls";
    char *const arguments[] = { "ls", "-l", NULL };
    char *const environment[] = { "HOME=/usr/home", "PATH=/usr/bin", NULL };

    ! Execute the "ls" command with the specified arguments and environment variables

    execve(program_path, arguments, environment);


*/

void    child_process(char **av, char **envp, t_paths **paths, int* fd)
{
    char *file1;

    file1 = av[0];

    int fd_file = open(file1, F_OK);

    dup2(fd_file, STDIN_FILENO); // met le fichier1 sur stdin
    dup2(fd[1], STDOUT_FILENO); // met la sortie standart sur fd[1]
    close(fd[0]); // => lock le pipe sinon il "fuit"
    ft_exec(av[1], envp, paths);
}
void    parent_process(char **av, char**envp, t_paths **paths, int* fd)
{
    char *file2;
    
    file2 = av[3];

    int fd_file = open(file2, F_OK);
    
    dup2(fd_file, STDOUT_FILENO);
    dup2(fd[0], STDIN_FILENO);
    close(fd[1]);
    ft_exec(av[2], envp, paths);
}

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
    int fd[2]; // pipes fd
    int fork_pid;

    if (pipe(fd) == -1)
        exit_and_message("Pipe Failed", 1); // needs to free struct
    
    fork_pid = fork();
    if (fork_pid == -1)
        exit_and_message("Fork failed", 1); // needs to free struct
    
    if (fork_pid == 0) // child process
    {
        child_process(av, envp, paths, fd);
    }
    waitpid(fork_pid, 0, 0);
    parent_process(av, envp, paths, fd);
}
