/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:55:43 by apesic            #+#    #+#             */
/*   Updated: 2025/03/27 15:13:33 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

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

static int	excec_final(t_pipex *pipex, char *bin, char **cmd_spl)
{
	clean_exit(pipex);
	execve(bin, cmd_spl, pipex->env);
	return (127);
}

static char	*un_bb(t_pipex *pipex, t_pipexelement *head)
{
	char	**pathhh;
	char	*bin;
	char	**cmd_spl;

	cmd_spl = ft_split(head->cmd, ' ');
	if (du(pipex, head, cmd_spl) && ch(pipex, cmd_spl[0], cmd_spl) == NULL)
	{
		pathhh = spl_path(pipex->env);
		if (pathhh != NULL)
		{
			bin = find_binary(cmd_spl[0], pathhh);
			free_double_table(pathhh);
			if (bin != 0)
				excec_final(pipex, bin, cmd_spl);
			else
				(error_case(pipex, ft_strjoin(CNF, cmd_spl[0]), cmd_spl),
					exit(127));
		}
		else if (pipex->env == NULL)
			(error_case(pipex, ft_strjoin(CNF, cmd_spl[0]), cmd_spl),
				exit(127));
	}
	bin = cmd_spl[0];
	cmd_spl[0] = get_cmd(cmd_spl[0]);
	exit(excec_final(pipex, bin, cmd_spl));
}

int	make_process(t_pipex *pipex)
{
	t_pipexelement	*head;

	head = pipex->start;
	while (head != NULL)
	{
		if (pipe(pipex->fd) == -1)
			return (error_case(pipex, "pipe", 0));
		head->pid = fork();
		if (head->pid == 0)
		{
			un_bb(pipex, head);
		}
		if (head->next == NULL)
		{
			ft_closem1(pipex->fd_out);
			close(pipex->fd[0]);
		}
		ft_closem1(pipex->fd[2]);
		ft_closem1(pipex->fd[1]);
		pipex->fd[2] = pipex->fd[0];
		head = head->next;
	}
	return (clean_exit(pipex));
}
