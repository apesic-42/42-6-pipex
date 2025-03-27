/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:56:13 by apesic            #+#    #+#             */
/*   Updated: 2025/03/27 15:15:05 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_caract	*treat_buf(char *buf, t_caract *first)
{
	t_caract	*current;
	t_caract	*nouveau;

	current = first;
	if (current == NULL)
	{
		current = (t_caract *)ft_calloc(sizeof(t_caract), 1);
		if (!current)
			return (NULL);
		current->data = *buf++;
		first = new_t_caract(current);
	}
	while (current->next != NULL)
		current = current->next;
	while (*buf)
	{
		nouveau = (t_caract *)ft_calloc(sizeof(t_caract), 1);
		if (!nouveau)
			return (free(nouveau), NULL);
		nouveau->data = *buf++;
		current->next = new_t_caract(nouveau);
		current = nouveau;
	}
	current->is_nl = true;
	return (first);
}

static t_caract	*get_new_first(t_caract *first)
{
	t_caract	*courant;
	t_caract	*tmp;

	courant = first;
	while (courant != NULL && !courant->is_nl)
	{
		tmp = courant;
		courant = courant->next;
		free(tmp);
	}
	if (courant && courant->is_nl)
	{
		tmp = courant;
		courant = courant->next;
		free(tmp);
	}
	return (courant);
}

static char	*out(t_caract *first)
{
	char		*out_line;
	int			i;
	int			len;
	t_caract	*courant;

	i = 0;
	if (!first->data)
		return (NULL);
	len = len_before_nl(first);
	out_line = (char *)ft_calloc(sizeof(char), len + 1);
	if (!out_line)
		return (NULL);
	courant = first;
	while (i < len)
	{
		out_line[i] = courant->data;
		courant = courant->next;
		i++;
	}
	out_line[i] = '\0';
	return (out_line);
}

char	*get_next_line(int fd)
{
	static t_caract	*first;
	char			*buf;
	char			*out_line;
	int				state;

	state = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	while (len_before_nl(first) == -1 && state > 0)
	{
		buf = (char *)ft_calloc(sizeof(char), BUFFER_SIZE);
		if (!buf)
			return (NULL);
		if (state > 0)
			state = read(fd, buf, BUFFER_SIZE);
		first = treat_buf(buf, first);
		free(buf);
	}
	out_line = out(first);
	first = get_new_first(first);
	return (out_line);
}
