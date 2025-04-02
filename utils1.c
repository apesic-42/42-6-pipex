/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:55:55 by apesic            #+#    #+#             */
/*   Updated: 2025/03/27 14:55:56 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft/libft.h"
#include "pipex.h"

static void	free_chained_list(t_pipexelement *pipexx)
{
	t_pipexelement	*current;
	t_pipexelement	*next;

	current = pipexx;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

int	clean_exit(t_pipex *pipex)
{
	t_pipexelement	*current;
	int				k;
	int				rn;

	current = pipex->start;
	k = 0;
	rn = 0;
	while (current)
	{
		waitpid(current->pid, &k, 0);
		current = current->next;
	}
	rn = k >> 8;
	free_chained_list(pipex->start);
	return (rn);
}

int	error_case(t_pipex *pipex, char *str, char **cmd_spl)
{
	free_chained_list(pipex->start);
	if (str != NULL)
		perror(str);
	free(str);
	if (cmd_spl)
		free_double_table(cmd_spl);
	return (1);
}

void	ft_closem1(int fd)
{
	if (fd != -1)
		close(fd);
}
