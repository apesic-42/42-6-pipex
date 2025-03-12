
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
    printf("okokle %d\n", pipexobj->fd_in);
    if (pipexobj->fd_in != STDIN_FILENO)
    {
        if (dup2(pipexobj->fd_in, STDIN_FILENO) == -1)
            return (error_case("dup2", pipexobj));
        close(pipexobj->fd_in);
    }
    printf("okoknw %d\n", pipexobj->fd_out);
    if (pipexobj->fd_out != STDOUT_FILENO)
    {
        if (dup2(pipexobj->fd_out, STDOUT_FILENO) == -1)
            return (error_case("dup2", pipexobj));
        close(pipexobj->fd_out);
    }
    // printf("okokle\n");
    execve(find_binary(pipexobj->cmd, env), ft_split(pipexobj->cmd, ' '), env);
    return (error_case("execve", pipexobj)); // Execve ne retourne que s'il y a une erreur
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
    int status;

    while (current != NULL)
    {
        current->pid_fork = fork();
        if (current->pid_fork == -1)
            return (error_case("fork", head));

        if (current->pid_fork == 0) // Enfant
        {
            childrens(current, v, env);
            exit(EXIT_FAILURE);  // En cas d'échec de `childrens`
        }
        else
        {
            if (current->fd_in != STDIN_FILENO)
                close(current->fd_in);
            if (current->next == NULL && current->fd_out != STDOUT_FILENO)
                close(current->fd_out);
        }

        current = current->next;
    }

    while (head != NULL) {  // Attendre chaque processus enfant
        waitpid(head->pid_fork, &status, 0);
        head = head->next;
    }

    return (0);
}
