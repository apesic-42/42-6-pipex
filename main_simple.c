/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:55:51 by apesic            #+#    #+#             */
/*   Updated: 2025/03/27 15:11:39 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/ucontext.h>
#include <unistd.h>

static int	filesfds(t_pipex *pipex, char **v, int c)
{
	int	re;

	re = 0;
	if (ft_strncmp(v[1], "here_doc", 8) == 0)
	{
		pipex->fd_in = -128;
		pipex->fd_out = open(v[c - 1], O_APPEND | O_WRONLY | O_CREAT, 0644);
		re++;
	}
	else
	{
		pipex->fd_in = open(v[1], O_RDONLY);
		pipex->fd_out = open(v[c - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (pipex->fd_in == -1 || pipex->fd_out == -1)
	{
		perror("open");
	}
	return (re);
}

static t_pipexelement	*placee(t_pipexelement *nexte, t_pipexelement *pipexobj,
		t_pipexelement *first, char *vi)
{
	nexte = (t_pipexelement *)ft_calloc(sizeof(t_pipexelement), 1);
	if (nexte == NULL)
		first->error = 1;
	pipexobj->next = nexte;
	pipexobj->error = 0;
	nexte->cmd = vi;
	return (nexte);
}

static int	placee2(t_pipex *pipex)
{
	if (pipex->start->error == 1)
		return (error_case(pipex, "malloc", 0));
	if (pipex->limiter)
	{
		pipex->fd_in = here_doc(pipex);
		if (pipex->fd_in == -1)
			return (error_case(pipex, "here doc", 0));
	}
	pipex->fd[2] = pipex->fd_in;
	return (make_process(pipex));
}

int	main(int c, char **v, char **env)
{
	t_pipex			pipex;
	t_pipexelement	*pipexobj;
	t_pipexelement	*nexte;
	int				i;

	if (c < 5)
		return (0);
	if (env[0] == NULL)
		env = NULL;
	i = 1;
	i += filesfds(&pipex, v, c);
	pipexobj = NULL;
	nexte = NULL;
	pipex.limiter = 0;
	pipexobj = init_chain(&pipex, pipexobj, v, ++i);
	pipex.env = env;
	pipex.start = pipexobj;
	while (i < c - 2)
		pipexobj = placee(nexte, pipexobj, pipex.start, v[++i]);
	return (placee2(&pipex));
}
