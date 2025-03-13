
#include "pipex.h"

static void duppp(t_pipexelement *head, int *fd, int in_fd)
{
    if (head->fd_in == -228)
        dup2(in_fd, STDIN_FILENO);
    else
        dup2(head->fd_in, STDIN_FILENO);
    if (head->fd_out == -228)
        dup2(fd[1], STDOUT_FILENO);
    else
        dup2(head->fd_out, STDOUT_FILENO);
    close(fd[0]);
}

int make_process(t_pipexelement *head, char **v, char **env)
{
    int fd[2];
    int in_fd;
    char *st;
    char **stt;

    in_fd = 0;
    while (head != NULL) {
        pipe(fd);
        if ((head->pid_fork = fork()) == 0) {
            duppp(head, fd, in_fd);
            st = find_binary(head->cmd, env);
            stt = ft_split(head->cmd, ' ');
            execve(st, stt, env);
        }
        close(fd[1]);
        if (in_fd != 0)
            close(in_fd);
        in_fd = fd[0];
        head = head->next;
    }
    if (in_fd != 0)
        close(in_fd);
    return (0);
}
