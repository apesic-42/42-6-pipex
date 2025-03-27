
#include "pipex.h"

static char	**spl_path(char **env)
{
	const char	*path;
	char		**spl;

	spl = NULL;
	if (env != NULL)
	{
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
	}
	return (spl);
}

static int	excec_final(t_pipexelement *headd, char *bin, char **cmd_spl,
		char **env)
{
	clean_exit(headd);
	execve(bin, cmd_spl, env);
	return (1);
}

static char	*un_bb(char **env, t_pipexelement *head, int fd[2],
		t_pipexelement *headd)
{
	char	**pathhh;
	char	*bin;
	char	**cmd_spl;

	cmd_spl = ft_split(head->cmd, ' ');
	multi_dup(head, fd, fd[2]);
	if (ft_strchr(cmd_spl[0], '/') == NULL)
	{
		pathhh = spl_path(env);
		if (pathhh != NULL)
		{
			bin = find_binary(cmd_spl[0], pathhh);
			free_double_table(pathhh);
			if (bin != 0)
				excec_final(headd, bin, cmd_spl, env);
			else
				exit(error_case(ft_strjoin("command not found : ", cmd_spl[0]),
						headd));
		}
		else if (env == NULL)
			exit(error_case(ft_strjoin("command not found : ", cmd_spl[0]),
					headd));
	}
	bin = cmd_spl[0];
	cmd_spl[0] = get_cmd(cmd_spl[0]);
	exit(excec_final(headd, bin, cmd_spl, env));
}

int	make_process(t_pipexelement *head, char **env)
{
	int				fd[3];
	t_pipexelement	*headd;

	headd = head;
	while (head != NULL)
	{
		if (pipe(fd) == -1)
			return (error_case("pipe", headd));
		if (head->fd_in == -128)
		{
			fd[2] = here_doc(head->limiter);
			if (fd[2] == -1)
				return (error_case("here doc", headd));
		}
		head->pid = fork();
		if (head->pid == 0)
			un_bb(env, head, fd, headd);
		close(fd[1]);
		if (fd[2] != 0)
			close(fd[2]);
		fd[2] = fd[0];
		head = head->next;
	}
	if (fd[2] != 0)
		close(fd[2]);
	return (clean_exit(headd));
}
