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

t_pipexelement	*init_chain(t_pipexelement *pipexobj, char **v, int i)
{
	pipexobj = (t_pipexelement *)ft_calloc(sizeof(t_pipexelement), 1);
	if (!pipexobj)
	{
		error_case("malloc", pipexobj);
		return (pipexobj);
	}
	pipexobj->error = 0;
	pipexobj->cmd = v[i];
	pipexobj->limiter = v[2];
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

int	multi_dup(t_pipexelement *head, int *fd, int in_fd, t_pipexelement *headd)
{
	if (head->fd_in == -1 || head->fd_out == -1)
		exit(error_case(NULL, headd));
	if (head->fd_in == -228 || head->fd_in == -128)
		dup2(in_fd, STDIN_FILENO);
	else
		dup2(head->fd_in, STDIN_FILENO);
	if (head->fd_out == -228)
		dup2(fd[1], STDOUT_FILENO);
	else
		dup2(head->fd_out, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	return (0);
}
