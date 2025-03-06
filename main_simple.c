
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

static t_pipexelement	*child_1(t_pipexelement *pipexobj, char **v, char **env)
{
	if (dup2(pipexobj->fd_file1, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(pipexobj->fd_file1);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipexobj->pip_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(pipexobj->pip_fd[1]);
		exit(EXIT_FAILURE);
	}
	close(pipexobj->pip_fd[0]);
	if (execve(find_binary(v[2], env), ft_split(v[2], ' '), NULL) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return (pipexobj);
}

static t_pipexelement	*child_2(t_pipexelement *pipexobj, char **v, char **env)
{
	if (dup2(pipexobj->pip_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(pipexobj->pip_fd[0]);
		exit(EXIT_FAILURE);
	}
	pipexobj->fd_file2 = open(v[4], O_WRONLY | O_CREAT, 0644);
	if (pipexobj->fd_file2 == -1)
	{
		pipexobj->error = "open";
		return (pipexobj);
	}
	if (dup2(pipexobj->fd_file2, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(pipexobj->fd_file2);
		exit(EXIT_FAILURE);
	}
	close(pipexobj->pip_fd[1]);
	if (execve(find_binary(v[3], env), ft_split(v[3], ' '), NULL) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return (pipexobj);
}

static t_pipexelement	*childrens(t_pipexelement *pipexobj, char **v,
		char **env)
{
	pipexobj->pid_fork2 = fork();
	if (pipexobj->pid_fork2 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pipexobj->pid_fork2 == 0)
	{
		pipexobj = child_2(pipexobj, v, env);
		if (pipexobj->error != NULL)
			return (pipexobj);
	}
	else
	{
		close(pipexobj->fd_file2);
		close(pipexobj->fd_file1);
	}
	return (pipexobj);
}

int	main(int c, char **v, char **env)
{
	t_pipexelement	*pipexobj;

	pipexobj = (t_pipexelement *)ft_calloc(sizeof(t_pipexelement), 1);
	if (c != 5)
		return (clean_exit(pipexobj));
	pipexobj = init_fork_1(pipexobj, v);
	if (pipexobj->error != NULL)
		return (error_case(pipexobj->error));
	if (pipexobj->pid_fork1 == 0)
	{
		pipexobj = child_1(pipexobj, v, env);
		if (pipexobj->error != NULL)
			return (error_case(pipexobj->error));
	}
	else
	{
		pipexobj = childrens(pipexobj, v, env);
		if (pipexobj->error != NULL)
			return (error_case(pipexobj->error));
	}
	close(pipexobj->fd_file1);
	return (clean_exit(pipexobj));
}
