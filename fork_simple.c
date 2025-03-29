/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:55:43 by apesic            #+#    #+#             */
/*   Updated: 2025/03/29 15:18:50 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	fprintf(stderr, "cmd_execve |%s| bin |%s|\n\n", cmd_spl[0], bin);
	if (!bin || !bin[0])
		bin = "/bin";
	fprintf(stderr, "cmd_execve |%s| bin |%s|\n\n", cmd_spl[0], bin);
	execve(bin, cmd_spl, env);
	return (127);
}

static char	*un_bb(char **env, t_pipexelement *head, int fd[2],
		t_pipexelement *headd)
{
	char	**pathhh;
	char	*bin;
	char	**cmd_spl;

	cmd_spl = ft_split(head->cmd, ' ');
	if (!cmd_spl[0] && head->cmd)
		(free(cmd_spl[0]), cmd_spl[0] = ft_strdup(head->cmd), cmd_spl[1] = NULL);
	printf("cmd_split |%s| cmd_raw |%s|\n\n", cmd_spl[0], head->cmd);
	multi_dup(head, fd, cmd_spl, headd);
	if (cmd_spl[0][0] && ft_strchr(cmd_spl[0], '/') == NULL)
	{
		pathhh = spl_path(env);
		if (pathhh != NULL)
		{
			bin = find_binary(cmd_spl[0], pathhh);
			free_double_table(pathhh);
			if (bin != 0)
				excec_final(headd, bin, cmd_spl, env);
			else
				(error_case1(ft_strjoin(CNF, cmd_spl[0]), cmd_spl, headd), exit(127));
		}
		else if (env == NULL)
			(error_case(ft_strjoin(CNF, cmd_spl[0]), headd), exit(127));
	}
	bin = cmd_spl[0];
	cmd_spl[0] = get_cmd(cmd_spl[0]);
	exit(excec_final(headd, bin, cmd_spl, env));
}

int	make_process(t_pipexelement *head, t_pipexelement *headd, char **env)
{
	int	fd[3];

	fd[2] = 0;
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
