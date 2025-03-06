
#include "pipex.h"


int main(int c, char **v, char **env)
{
    t_pipexelement *pipexobj;

    pipexobj = (t_pipexelement *)ft_calloc(sizeof(t_pipexelement), 1);

    if (c != 5)
        return 0;

    // open file1
    pipexobj->fd_file1 = open(v[1], O_RDONLY);
    if (pipexobj->fd_file1 == -1)
        return (error_case("open"));


    // create a pipe
    if (pipe(pipexobj->pip_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // create fork 1
    pipexobj->pid_fork1 = fork();
    if (pipexobj->pid_fork1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pipexobj->pid_fork1 == 0)
    {
        // child 1

        // Redirigez l'entrée standard (stdin) vers le descripteur de fichier de file1 à l'aide de dup2.
        if (dup2(pipexobj->fd_file1, STDIN_FILENO) == -1)
        {
            perror("dup2");
            close( pipexobj->fd_file1);
            exit(EXIT_FAILURE);
        }


        // Redirigez la sortie standard (stdout) vers l'extrémité d'écriture du pipe (fd_write) à l'aide de dup2.
        if (dup2(pipexobj->pip_fd[1], STDOUT_FILENO) == -1)
        {
            perror("dup2");
            close(pipexobj->pip_fd[1]);
            exit(EXIT_FAILURE);
        }

        // Fermez les extrémités inutilisées du pipe.
        close(pipexobj->pip_fd[0]);


        // Utiliser execve pour exécuter /bin/ls avec l'option -l
        if (execve(find_binary(v[2], env), ft_split(v[2], ' '), NULL) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        // create fork 2
        pipexobj->pid_fork2 = fork();
        if (pipexobj->pid_fork2 == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pipexobj->pid_fork2 == 0)
        {
            // child 2

            // Redirigez l'entrée standard (stdin) vers l'extrémité de lecture du pipe (fd_read) à l'aide de dup2.
            if (dup2(pipexobj->pip_fd[0], STDIN_FILENO) == -1)
            {
                perror("dup2");
                close(pipexobj->pip_fd[0]);
                exit(EXIT_FAILURE);
            }

            // Ouvrez file2 en mode écriture et obtenez son descripteur de fichier.
            pipexobj->fd_file2 = open(v[4], O_WRONLY | O_CREAT, 0644);
            if (pipexobj->fd_file2 == -1)
                return (error_case("open"));

            // Redirigez la sortie standard (stdout) vers le descripteur de fichier de file2 à l'aide de dup2.
            if (dup2(pipexobj->fd_file2, STDOUT_FILENO) == -1)
            {
                perror("dup2");
                close(pipexobj->fd_file2);
                exit(EXIT_FAILURE);
            }

            close(pipexobj->pip_fd[1]);

            // Utiliser execve
            if (execve(find_binary(v[3], env), ft_split(v[3], ' '), NULL) == -1)
            {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            close(pipexobj->fd_file2);
            close(pipexobj->fd_file1);
        }
    }

    close(pipexobj->fd_file1);
    free(pipexobj);
    return 0;
}
