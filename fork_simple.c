
#include "pipex.h"

static void multi_dup(t_pipexelement *head, int *fd, int in_fd)
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


static void closefds(t_pipexelement *head)
{
    int fds[2];

    printf("ici : 1 : %d 2 : %d\n", fds[0], fds[1] );
    fds[0] = head->fd_in;
    while (head->next != NULL)
        head = head->next;
    fds[1] = head->fd_out;

}

int close_fds(t_pipexelement *first)
{
    while (first != NULL)
    {
        if (first->fd_in >= 0)
        {
            if (close(first->fd_in) == -1)
                return (-1);
        }
        if (first->fd_out >= 0)
        {
            if (close(first->fd_out) == -1)
                return (-1);
        }
        first = first->next;
    }
    return (0);
}

static char **spl_path(char **env)
{
   	const char	*path;
    char		**spl;

   	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
		{
			path = ft_strchr(*env, '=') + 1;
			break ;
		}
		env++;
	}
	spl = ft_split(path, ':');

	return (spl);
}

int make_process(t_pipexelement *head, char **v, char **env)
{
    int fd[2];
    int in_fd;
    char *bin;
    char **cmd_spl;
    t_pipexelement *headd;
    char **path;

    headd = head;

    in_fd = 0;
    path = spl_path(env);
    while (head != NULL) {
        if (pipe(fd) == -1)
            return (error_case("pipe", headd));
        if ((head->pid_fork = fork()) == 0)
        {
            multi_dup(head, fd, in_fd);
            cmd_spl = ft_split(head->cmd, ' ');
            bin = find_binary(cmd_spl[0], path);
            clean_exit(headd, path);

            execve(bin, cmd_spl, env);
            // free(bin);
            // free(cmd_spl);
            //exit(0);
        }
        close(fd[1]);
        if (in_fd != 0)
            close(in_fd);
        in_fd = fd[0];
        head = head->next;
    }
    if (in_fd != 0)
    {
        close(in_fd);
    }
    return (clean_exit(headd, path));
}
