
#include "pipex.h"

static t_pipexelement	*init_fork_1(t_pipexelement *pipexobj, char **v)
{
	pipexobj->fd_file1 = open(v[1], O_RDONLY);
	if (pipexobj->fd_file1 == -1)
	{
		pipexobj->error = "open";
		return (pipexobj);
	}
	if (pipe(pipexobj->pip_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pipexobj->pid_fork1 = fork();
	if (pipexobj->pid_fork1 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pipexobj);
}


static char *childs(FdSet fds, char *cmd, char **env) {
    if (dup2(fds.fd_in, STDIN_FILENO) == -1) {
        perror("dup2");
        close(fds.fd_in);
        exit(EXIT_FAILURE);
    }
    if (dup2(fds.fd_out, STDOUT_FILENO) == -1) {
        perror("dup2");
        close(fds.fd_out);
        exit(EXIT_FAILURE);
    }
    close(fds.fd_extra);
    if (execve(find_binary(cmd, env), ft_split(cmd, ' '), NULL) == -1) {
        perror("execve");
        exit(EXIT_FAILURE);
    }
    return "ok";
}


static t_pipexelement	*childrens(t_pipexelement *pipexobj, char **v,
		char **env)
{
	int    status;

	pipexobj->pid_fork2 = fork();
	if (pipexobj->pid_fork2 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pipexobj->pid_fork2 == 0)
	{
        pipexobj->fd_file2 = open(v[4], O_WRONLY | O_CREAT, 0644);
       	if (pipexobj->fd_file2 == -1)
       	{
      		pipexobj->error = "open";
      		return (pipexobj);
       	}
        FdSet fds1 = {pipexobj->pip_fd[0], pipexobj->fd_file2, pipexobj->pip_fd[1]};
        if (ft_strncmp(childs(fds1, v[3], env), "ok", 2) != 0) {
            return (pipexobj);
        }
	}
	else
	{
	    waitpid(pipexobj->pid_fork1, &status, 0);
		waitpid(pipexobj->pid_fork2, &status, 0);
		close(pipexobj->fd_file2);
		close(pipexobj->fd_file1);
		close(pipexobj->pip_fd[0]);
		close(pipexobj->pip_fd[1]);
	}
	return (pipexobj);
}


int	main(int c, char **v, char **env)
{
	t_pipexelement	*pipexobj;

	if (c != 5)
		return (clean_exit(pipexobj));
	pipexobj = (t_pipexelement *)ft_calloc(sizeof(t_pipexelement), 1);
	if (!pipexobj)
	   return (0);
	pipexobj = init_fork_1(pipexobj, v);
	if (pipexobj->error != NULL)
		return (error_case(pipexobj->error));
	if (pipexobj->pid_fork1 == 0)
	{
		FdSet fds2 = {pipexobj->fd_file1, pipexobj->pip_fd[1], pipexobj->pip_fd[0]};
        if (ft_strncmp(childs(fds2, v[3], env), "ok", 2) != 0) {
            return error_case(pipexobj->error);
        }
	}
	else
	{
		pipexobj = childrens(pipexobj, v, env);
		if (pipexobj->error != NULL)
			return (error_case(pipexobj->error));
	}
	return (clean_exit(pipexobj));
}
