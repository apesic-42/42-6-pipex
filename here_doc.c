/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:55:48 by apesic            #+#    #+#             */
/*   Updated: 2025/03/27 15:14:20 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	pipee(int *fds)
{
	if (pipe(fds) == -1)
		return (-1);
	return (0);
}

static char	*place(char *str)
{
	free(str);
	return (NULL);
}

static int	finish(char *f1, char *f2, int c1, int r1)
{
	if (f1 != NULL)
		free(f1);
	if (f2 != NULL)
		free(f2);
	close(c1);
	return (r1);
}

int	here_doc(char *limiter)
{
	char	*line;
	char	*wbn;
	int		fds[2];

	line = "okok";
	wbn = ft_strjoin(limiter, "\n");
	if (!wbn || pipee(fds) == -1)
		return (-1);
	while (line != NULL)
	{
		ft_printf("> ");
		line = get_next_line(STDIN_FILENO);
		if (ft_strcmp(wbn, line) == 0)
			line = place(line);
		if (line != NULL)
			write(fds[1], line, ft_strlen(line));
		free(line);
	}
	return (finish(wbn, line, fds[1], fds[0]));
}
