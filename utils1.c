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

int	close_fds(t_pipexelement *first)
{
	while (first != NULL)
	{
		if (first->fd_in >= 0)
		{
			if (close(first->fd_in) == -1)
				return (-1);
		}
		if (first->fd_out >= 0)
		{
			if (close(first->fd_out) == -1)
				return (-1);
		}
		first = first->next;
	}
	return (0);
}

int	clean_exit(t_pipexelement *pipexx)
{
	t_pipexelement	*current;
	int				k;
	int				rn;

	current = pipexx;
	close_fds(pipexx);
	k = 0;
	rn = 0;
	while (current)
	{
		waitpid(current->pid, &k, 0);
		current = current->next;
	}
	rn = k >> 8;
	free_chained_list(pipexx);
	return (rn);
}

int	error_case(char *str, t_pipexelement *pipexx)
{
	close_fds(pipexx);
	free_chained_list(pipexx);
	if (str != NULL)
		perror(str);
	free(str);
	return (1);
}

int	error_case_arg2(char *str, t_pipexelement *pipexx, char **cmd_spl)
{
	close_fds(pipexx);
	free_chained_list(pipexx);
	if (str != NULL)
		perror(str);
	free(str);
	free_double_table(cmd_spl);
	return (1);
}
