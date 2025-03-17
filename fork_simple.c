
#include "pipex.h"

static int multi_dup(t_pipexelement *head, int *fd, int in_fd)
{
    if (head->fd_in == -228 || head->fd_in == -128)
        dup2(in_fd, STDIN_FILENO);
    else
        dup2(head->fd_in, STDIN_FILENO);
    if (head->fd_out == -228)
        dup2(fd[1], STDOUT_FILENO);
    else
        dup2(head->fd_out, STDOUT_FILENO);
    close(fd[0]);
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
        if (head->fd_in == -128)
        {
            in_fd = here_doc(head->limiter);
            if (in_fd == -1)
                return (-1);
        }
        if ((head->pid_fork = fork()) == 0)
        {
            multi_dup(head, fd, in_fd);
            cmd_spl = ft_split(head->cmd, ' ');
            bin = find_binary(cmd_spl[0], path);
            clean_exit(headd, path);
            close(fd[1]);
            //close(in_fd); //(cat dont work with that but it's an valgrind error)
            execve(bin, cmd_spl, env);
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
