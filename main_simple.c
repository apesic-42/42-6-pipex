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

static int	filesfds(int *fd_files, char **v, int c)
{
	int	re;

	re = 0;
	if (ft_strncmp(v[1], "here_doc", 8) == 0)
	{
		fd_files[0] = -128;
		fd_files[1] = open(v[c - 1], O_APPEND | O_WRONLY | O_CREAT, 0644);
		re++;
	}
	else
	{
		fd_files[0] = open(v[1], O_RDONLY);
		fd_files[1] = open(v[c - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (fd_files[0] == -1 || fd_files[1] == -1)
	{
		perror("open");
	}
	return (re);
}

int	put_fds(t_pipexelement *first, int *fd_files)
{
	first->fd_in = fd_files[0];
	first->fd_out = -228;
	first = first->next;
	while (first->next != NULL)
	{
		first->fd_in = -228;
		first->fd_out = -228;
		first = first->next;
	}
	first->fd_in = -228;
	first->fd_out = fd_files[1];
	return (0);
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

static int	placee2(t_pipexelement *first, int *fd_files, char **env)
{
	if (first->error == 1)
		return (error_case("malloc", first));
	if (put_fds(first, fd_files) == 1)
		return (-1);
	return (make_process(first, first, env));
}

int	main(int c, char **v, char **env)
{
	t_pipexelement	*pipexobj;
	t_pipexelement	*first;
	t_pipexelement	*nexte;
	int				i;
	int				fd_files[2];

	if (c < 5)
		return (0);
	if (env[0] == NULL)
		env = NULL;
	i = 1;
	i += filesfds(fd_files, v, c);
	pipexobj = NULL;
	nexte = NULL;
	pipexobj = init_chain(pipexobj, v, ++i);
	first = pipexobj;
	while (i < c - 2)
		pipexobj = placee(nexte, pipexobj, first, v[++i]);
	return (placee2(first, fd_files, env));
}
