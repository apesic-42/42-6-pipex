
#include "pipex.h"


void printfd(int fd) {
    char buffer[1024];
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        // Écrire les données lues sur la sortie standard
        if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read) {
            perror("write");
            return;
        }
    }

    if (bytes_read == -1) {
        perror("read");
    }
}

static void get_fd_pipe(t_pipexelement *pipexobj, int *pipfds)
{
    pipfds[1] = pipexobj->fd_out;
    while (pipexobj->next != NULL)
        pipexobj = pipexobj->next;
    pipfds[0] = pipexobj->fd_in;
}

static int childrens(t_pipexelement *pipexobj, char **v, char **env)
{
    //int pipfds[2];

    //get_fd_pipe(pipexobj, pipfds);
    //gerer les fds, faire la commande
    printf("pipexobj->fd_in : %d\n", pipexobj->fd_in);
    printfd(pipexobj->fd_in);
    if (dup2(pipexobj->fd_in, STDIN_FILENO) == -1)
        return (error_case("dup2", pipexobj));
    if (dup2(pipexobj->fd_out, STDOUT_FILENO) == -1)
        return (error_case("dup2", pipexobj));
    if (execve(find_binary(pipexobj->cmd, env), ft_split(pipexobj->cmd, ' '), NULL) == -1)
        return (error_case("execvs", pipexobj));
    return (0);
}


static int parent(t_pipexelement *pipexobj)
{
    int status;
    pid_t terminated_pid = wait(&status);
    return (0);
}


int make_process(t_pipexelement *head, char **v, char **env)
{
    t_pipexelement *current = head;

    while (current != NULL)
    {

        current->pid_fork = fork();
        if (current->pid_fork == -1)
            return (error_case("fork", head));
        if (current->pid_fork == 0) //enfant
        {
            if (childrens(current, v, env) == 1)
                return (1);
        }
        else
        {
            if (parent(current) == 1)
                return (1);
        }
        current = current->next;
    }
    return (0);
}
