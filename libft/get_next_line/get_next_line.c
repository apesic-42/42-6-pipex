/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:47:53 by apesic            #+#    #+#             */
/*   Updated: 2024/12/16 19:34:33 by apesic           ###   ########.fr       */
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

#include <fcntl.h> // Pour open() et O_RDONLY
#include <unistd.h> // Pour close() et d'autres fonctions d'E/S comme read()

//int	main(void)
//{
//	int		fd;
//	char	*a;
	//char	*b;
	// char	*c;
	// char	*d;
	// char	*e;
	// char	*f;
	// char	*g;
	// char	*h;

//	fd = open("empty.txt", O_RDONLY);
//	a = get_next_line(fd);
//	printf("%s", a);
//	free(a);
//	b = get_next_line(fd);
//	printf("%s", b);
	//free(b);
	// c = get_next_line(fd);
	// printf("%s", c);
	// free(c);
	// d = get_next_line(fd);
	// printf("%s", d);
	// free(d);
	// e = get_next_line(fd);
	// printf("%s", e);
	// free(e);
	// f = get_next_line(fd);
	// printf("%s", f);
	// free(f);
	// g = get_next_line(fd);
	// printf("%s", g);
	// free(g);
	// h = get_next_line(fd);
	// printf("%s", h);
	// free(h);
//}
// cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -g
