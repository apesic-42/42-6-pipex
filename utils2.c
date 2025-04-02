/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:55:58 by apesic            #+#    #+#             */
/*   Updated: 2025/03/27 14:55:59 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

t_pipexelement	*init_chain(t_pipex *pipex, t_pipexelement *pipexobj, char **v,
		int i)
{
	pipexobj = (t_pipexelement *)ft_calloc(sizeof(t_pipexelement), 1);
	if (!pipexobj)
	{
		error_case(pipex, "malloc", 0);
		return (pipexobj);
	}
	pipexobj->error = 0;
	pipexobj->cmd = v[i];
	if (strcmp(v[1], "here_doc") == 0)
		pipex->limiter = v[2];
	return (pipexobj);
}

char	*get_cmd(const char *path)
{
	char	*last_slash;

	last_slash = ft_strrchr(path, '/');
	if (last_slash != NULL)
		return (last_slash + 1);
	else
		return ((char *)path);
}

int	du(t_pipex *pipex, t_pipexelement *head, char **cmd_spl)
{
    (void)cmd_spl;
	if (pipex->fd[2] == -1 || (head->next == NULL && pipex->fd_out == -1) || (head->next != NULL && pipex->fd[1] == -1))
	{
		ft_closem1(pipex->fd[0]);
		ft_closem1(pipex->fd_out);
		ft_closem1(pipex->fd[1]);
		ft_closem1(pipex->fd[2]);
		exit(error_case(pipex, NULL, cmd_spl));
	}
	dup2(pipex->fd[2], STDIN_FILENO);
	if (head->next != NULL)
		dup2(pipex->fd[1], STDOUT_FILENO);
	else
	{
		dup2(pipex->fd_out, STDOUT_FILENO);
	}
	close(pipex->fd[0]);
	close(pipex->fd_out);
	close(pipex->fd[1]);
	close(pipex->fd[2]);
	return (1);
}

char	*find_binary(char *str, char **path)
{
	char	*bin;
	char	*tp;

	while (*path)
	{
		tp = ft_strjoin(*path, "/");
		bin = ft_strjoin(tp, str);
		free(tp);
		if (access(bin, F_OK) == 0)
		{
			if (access(bin, X_OK) == 0)
			{
				return (bin);
			}
			else
			{
				free(bin);
				return (NULL);
			}
		}
		path++;
		free(bin);
	}
	return (NULL);
}

char	*ch(t_pipex *pipex, char *s, char **cmd_spl)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i] != '/')
		{
			if (s[i] == '\0' && i != 0)
				return ((char *)0);
			i++;
		}
	}
	(error_case(pipex, ft_strjoin(CNF, cmd_spl[0]), cmd_spl), exit(127));
}
